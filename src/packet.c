#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

#define MAGIC 0xb562
#define NAVPVTCODE 0x0107

/*functions for processing packet data, written mainly by Justin Lex*/

uint16_t packet_start_bits = 0; //holds interpacket bits while we search for a packet header

_Bool in_packet = 0; // =1 when we have found header and are in packet

uint16_t packet_type = 0;
uint16_t payload_length = 0;


uint8_t header_bytes_read = 0;
uint16_t payload_bytes_read = 0;
uint8_t checksum_bytes_read = 0;

uint8_t payload[512];
uint16_t checksum = 0;


void reset_rx_state() {
  packet_start_bits = 0;
  in_packet = 0;
  header_bytes_read = 0;
  payload_bytes_read = 0;
  checksum_bytes_read = 0;
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

  ck_a += (payload_length) & 0xff;
  ck_b += ck_a;

  ck_a += (payload_length >> 8) & 0xff;
  ck_b += ck_a;


  //continue checksumming with payload bytes
  int i;
  for(i = 0; i < payload_length; i++) {
    ck_a += payload[i];
    ck_b += ck_a;
  }

  //package checksums together and return
  return(((uint16_t)ck_a << 8) | ck_b);
}

void check_packet_and_store() {
  uint32_t actual_checksum = calculate_checksum();
  if(actual_checksum != checksum) {
    reset_rx_state();
    return;
  }
  switch(packet_type) {

    case NAVPVTCODE: //UBX-NAV-PVT
      store_nav_pvt_payload(payload);
      setleds();
      reset_rx_state();
      return;

    default: //unused packet type
      reset_rx_state();
      return;
  }
}

volatile void handlepacket() {

  //check for framing error
  if(U2STA & 0x2) {
    clear_framing_error();
    reset_rx_state();
  }

  if(in_packet == 0) {
    packet_start_bits <<= 8;
    packet_start_bits |= read_byte();

    if ( packet_start_bits == MAGIC ) { //magic bytes at the start of a UBX packet
      in_packet = 1;
    }
  }
  else {
    switch(header_bytes_read) {

      case 0: //message class byte
        packet_type = (uint16_t) read_byte() << 8;
        header_bytes_read++;
        break;

      case 1: //message ID byte
        packet_type |= read_byte();
        header_bytes_read++;
        break;

      case 2: //length field MSB
        payload_length = read_byte() ;
        header_bytes_read++;
        break;

      case 3: //length field LSB
        payload_length |= (uint16_t) read_byte() << 8;
        header_bytes_read++;
        if(payload_length > 512) { //drop packet if payload is too big
          reset_rx_state();
        }
        break;

      default: //payload or checksum
        if (payload_bytes_read < payload_length) { //payload
          payload[payload_bytes_read] = read_byte();
          payload_bytes_read++;
        }

        else { //checksum
          if (checksum_bytes_read == 0) { //1st byte of cksm
            checksum = (uint16_t)read_byte() << 8;
            checksum_bytes_read++;
          }
          else { //2nd byte of cksm
            checksum |= read_byte();
            check_packet_and_store();
          }
        }

    }

  }
  IFSCLR(1) = 0x200; //clear U2RX interrupt flag
}
