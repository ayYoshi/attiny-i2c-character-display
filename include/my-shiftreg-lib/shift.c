#include "shift.h"

void PULSE_SRCLK() {
  SRCLK_PORT |= (1<<SRCLK_PIN);
  SRCLK_PORT &= ~(1<<SRCLK_PIN);
}

void PULSE_RCLK() {
  RCLK_PORT |= (1<<RCLK_PIN);
  RCLK_PORT &= ~(1<<RCLK_PIN);
}
void SET_SER_VAL(uint8_t bit) {
  // 0 % 2 = 0, 1 % 2 = 1
  if ((bit & 1u) == 1) {
    SER_PORT |= (1<<SER_PIN);
  } else {
    SER_PORT &= ~(1<<SER_PIN);
  }
}

void send_bit(uint8_t bit) {
  SET_SER_VAL(bit);
  PULSE_SRCLK();
  PULSE_RCLK();
}

void send_byte(uint8_t byte) {
  for (int i = 0; i < 8; i++) {
    SET_SER_VAL(byte & 1u);
    PULSE_SRCLK();
    byte = byte >> 1;
  }
  PULSE_RCLK();
}

void clear_register() {
  send_byte(0);
}
