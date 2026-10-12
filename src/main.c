
#include <avr/io.h>
#include <util/delay.h>
#include "shift.h"
#include "usitwislave.h"

#define I2C_ADDRESS 0x10 // address of the i2c device

uint8_t reg_status = 0b0000; // saved status of all pins on the Shift Register

static void process_data(volatile uint8_t input_buffer_length, const uint8_t *input_buffer,
        uint8_t *output_buffer_length, uint8_t *output_buffer);
int main(int argc, char *argv[]) {

  // first i2c objective:
  // Read 2 bytes at a time
  // Byte 1: Number 0-3 - targets a pin on the shift register
  // Byte 2: Bool 0 or 1 - Turns that pin off (0) or on (1)
  // Example: "0x00" "0x01" turns Pin 0 on
  //          "0x03" "0x00" turns Pin 3 off

  // Set Shift Register pins to OUTPUT
  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  // Set register state to 0
  clear_register();
  usi_twi_slave(I2C_ADDRESS, 0, process_data, (void*)0);

  while (1) {
  }
  
}

// This function should be called whenever the device recieves an i2C request
static void process_data(volatile uint8_t input_buffer_length, const uint8_t *input_buffer,
        uint8_t *output_buffer_length, uint8_t *output_buffer) {
  *output_buffer_length = 0; //In no case do we return data to the master
  // Since every request contains 2 bytes, the buffer length should always be 2
  // TODO add an error led
  if (input_buffer_length != 2) {
    return;
  }
  switch (input_buffer[0]) {
    case 0:
      input_buffer[1] ? (reg_status |= (1<<0)) : (reg_status &= ~(1<<0));
      break;
    case 1:
      input_buffer[1] ? (reg_status |= (1<<1)) : (reg_status &= ~(1<<1));
      break;
    case 2:
      input_buffer[1] ? (reg_status |= (1<<2)) : (reg_status &= ~(1<<2));
      break;
    case 3:
      input_buffer[1] ? (reg_status |= (1<<3)) : (reg_status &= ~(1<<3));
      break;
    default:
      return; // Any value out of bounds will return without doing anything
  }
  send_byte(reg_status);
}
