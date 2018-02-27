//functions for processing packet data

_Bool in_packet = 0; //0: no μ found, 1: μ found, no b yet

_Bool in_checksum = 0;

uint8_t header_bits_read = 0;

uint16_t packet_type = 0;

uint16_t packet_length = 0;

uint8_t* payloadptr;


void handlepacket(void) {

  //scan for μb packet start
  if(!in_packet) {
    if(U2RXREG == 'μ')
    in_packet = 1;
  }
  if(!in_packet) {
    if(U2RXREG == 'b')
      in_packet = 2;
    else in_packet = 0;
  }

}
