#include "shift.h"

void PULSE_SRCLK();
void PULSE_RCLK();
void SET_SER_VAL(uint8_t bit);

void send_bit(uint8_t bit);

void send_byte(uint8_t byte);

void clear_register();
