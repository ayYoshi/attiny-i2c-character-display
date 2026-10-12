#include <avr/io.h>
#include <util/delay.h>
#include "shift.h"

uint8_t shift_register_status = 0b0000; // saved status of all pins on the Shift Register

static void process_data(volatile uint8_t input_buffer_length, const uint8_t *input_buffer,
        uint8_t *output_buffer_length, uint8_t *output_buffer);
int main(int argc, char *argv[]) {

  // first i2c objective:
  // Read 2 bytes at a time
  // Byte 1: Number 1-4 - targets a pin on the shift register
  // Byte 2: Bool 0 or 1 - Turns that pin off (0) or on (1)

  // Set Shift Register pins to OUTPUT
  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  // Set register state to 0
  clear_register();

  while (1) {
    for (int i = 16; i < 255; i++) {
      send_byte((uint8_t)i);
      _delay_ms(50);
    }
  }
  
}

static void process_data(volatile uint8_t input_buffer_length, const uint8_t *input_buffer,
        uint8_t *output_buffer_length, uint8_t *output_buffer) {
  *output_buffer_length = 0; //In no case do we return data to the master
  // Since every request contains 2 bytes, the buffer length should never be odd
  // TODO add an error bit?
  if (((input_buffer_length)%2) != 0) {
    return;
  }
  for (int i = 0; i < input_buffer_length; i+=2) {


  }

}
