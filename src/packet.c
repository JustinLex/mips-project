#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

/*functions for processing packet data, written mainly by Justin Lex*/

//Keeps track of which packet that we're either sending or looking for.
//Set externally with set_packet_type().
int packet_type_index = 0;

void set_packet_type(int packet_index) {
  packet_type_index = packet_index;
}


uint16_t packet_start_bits = 0; //holds interpacket bits while we search for a packet header

_Bool in_packet = 0; // =1 when we have found header and are in packet

uint16_t packet_type = 0;
uint16_t payload_length = 0;

//Array used to convert between our packet type index and that packet's class and ID bytes
uint16_t packet_type_table[1] = {
  0x0107 //UBX-NAV-PVT
};

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
    reset_rx_state();
    return;
  }
   //TODO: change this to work with polling format
  //sort packet based on type
  switch(packet_type_index) {

    case 0: //UBX-NAV-PVT
      store_nav_pvt_payload(payload);
      reset_rx_state();
      pollseq_next_step();
      return;

    default: //glitch (invalid type index, and somehow we matched a packet ID with garbage?)
      reset_rx_state();
      return;
  }
}

void handlepacket() {

  //check for framing error
  if(U2STA & 0x2) {
    clear_framing_error();
    reset_rx_state();
  }

  if(in_packet == 0) {
    packet_start_bits <<= 8;
    packet_start_bits |= read_byte();
    if ( packet_start_bits == 0xb562 ) { //magic bytes at the start of a UBX packet 0xb562
      in_packet = 1;
    }
  }
  else {
    switch(header_bytes_read) {

      case 0: //message class byte
        packet_type = (uint16_t)read_byte() << 8;
        header_bytes_read++;
        break;

      case 1: //message ID byte
        packet_type |= read_byte();

        //drop packet if we're not waiting for it
        if(packet_type != packet_type_table[packet_type_index]) {
          reset_rx_state();
          break;
        }

        header_bytes_read++;
        break;

      case 2: //length field MSB
        payload_length = (uint16_t)read_byte() << 8;
        header_bytes_read++;
        break;

      case 3: //length field LSB
        payload_length |= read_byte();
        header_bytes_read++;
        if(payload_length > 512) { //drop packet if payload is too big
          reset_rx_state();
          return;
        }
        break;

      default: //payload or checksum
        if (payload_bytes_read < payload_length) { //payload
          payload[payload_bytes_read] = read_byte();
          payload_bytes_read++;
        }

        else { //checksum
          if (checksum_bytes_read = 0) { //1st byte of cksm
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
}

//Pregenerated packets used for polling data from the gps, ordered by packet_type_index
//first number in the array contains the number of bytes we have to transmit,
//the following numbers are the bytes that make up the packet.
uint8_t pollpackets[1][9] = {
  {8,0xB5,0x62,0x01,0x07,0x00,0x00,0x08,0x25} //Poll for UBX-NAV-PVT
};

int bytes_sent = 0;

void send_packet_byte() {

  if(bytes_sent < pollpackets[packet_type_index][0]) { //send next byte
    U2TX = pollpackets[packet_type_index][bytes_sent+1];
    bytes_sent++;
  }

  else { //we finished the packet, lock until TX buffer is completely empty and then report back to poll sequencer
    while(U2STA & 0x100);
    pollseq_next_step();
  }

}
