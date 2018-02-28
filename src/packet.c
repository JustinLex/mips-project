#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define MAGIC 0x8562 //"μb"

//functions for processing packet data, written mainly by Justin Lex

uint32_t packet_start_bits = 0; //holds interpacket bits while we search for a packet header

_Bool in_packet = 0; // =1 when we have found header and are in packet
uint8_t align_offset = 0; // holds the offset that the bytes are coming into the UART port

uint16_t packet_type = 0;
uint16_t payload_length = 0;

uint8_t header_bytes_read = 0;
uint16_t payload_bytes_read = 0;
uint8_t checksum_bytes_read = 0;

uint8_t payload[2048];
uint16_t checksum = 0;

void reset_state() {
  packet_start_bits = 0;
  in_packet = 0;
  header_bytes_read = 0;
  payload_bytes_read = 0;
  checksum_bytes_read = 0;
}

void scan_for_magic_bytes() {
  //add new byte to pile
  packet_start_bits <<= 8;
  packet_start_bits |= read_shifted_byte(0);

  //search through pile for magic bytes
  int possible_offset;
  for(possible_offset = 0; possible_offset < 16; possible_offset ++) {

    uint16_t possible_start = (uint16_t) (packet_start_bits >> possible_offset);

    if(possible_start == MAGIC) {
      in_packet = 1;
      align_offset = possible_offset;
    }

  }
}

calculate_checksum() {
  //Fletcher Algorithm, code modeled after pseudocode in "u-blox M8 Protocol Specification"
  uint8_t ck_a = 0; //checksum A
  uint8_t ck_b = 0; //checksum B

  //start checksumming with header bytes
  ck_a += (packet_type >> 8) & 0xff;
  ck_b += ck_a;

  ck_a += (packet_type) & 0xff;
  ck_b += ck_a;

  ck_a += (payload_length >> 8) & 0xff;
  ck_b += ck_a;

  ck_a += (payload_length) & 0xff;
  ck_b += ck_a;


  //continue checksumming with payload bytes
  int i;
  for(i = 0; i < payload_length; i++) {
    ck_a += payload[i];
    ck_b += ck_a;
  }

  //package checksums together and return
  return((uint16_t)ck_a << 8) | ck_b;
}

void check_packet_and_store() {
  uint16_t actual_checksum = calculate_checksum();
  if(actual_checksum != checksum) {
    reset_state();
    return;
  }

  //sort packet based on type
  switch(packet_type) {

    case 0x0122: //UBX-NAV-CLOCK
      store_nav_clock_payload(payload);
      reset_state();
      return;

    default: //unused packet type
      reset_state();
      return;
  }
}

void handlepacket() {

  //check for framing error
  if(U2STA & 0x2) {
    clear_framing_error();
    reset_state();
  }

  if(in_packet == 0) {
    scan_for_magic_bytes();
  }
  else {
    switch(header_bytes_read) {

      case 0: //message class byte
        packet_type = (uint16_t)read_shifted_byte(align_offset) << 8;
        header_bytes_read++;
        break;

      case 1: //message ID byte
        packet_type |= read_shifted_byte(align_offset);
        header_bytes_read++;
        break;

      case 2: //length field MSB
        payload_length = (uint16_t)read_shifted_byte(align_offset) << 8;
        header_bytes_read++;
        break;

      case 3: //length field LSB
        payload_length |= read_shifted_byte(align_offset);
        header_bytes_read++;
        if(payload_length > 2048) { //drop packet if payload is too big
          reset_state();
          return;
        }
        break;

      default: //payload or checksum
        if (payload_bytes_read < payload_length) { //payload
          payload[payload_bytes_read] = read_shifted_byte(align_offset);
        }

        else { //checksum
          if (checksum_bytes_read = 0) { //1st byte of cksm
            checksum = (uint16_t)read_shifted_byte(align_offset) << 8;
          }
          else { //2nd byte of cksm
            checksum |= read_shifted_byte(align_offset);
            check_packet_and_store();
          }
        }

    }

  }
}
