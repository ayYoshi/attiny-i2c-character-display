#pragma once
#include <avr/io.h>

// PB1: Data Bus (SER)
// PB3: Input Clock (SRCLK) (shift register clock)
// PB4: Output Clock (RCLK) (storage register clock)

#define SER_PORT    PORTB
#define SER_PIN     PORTB1
#define SRCLK_PORT  PORTB
#define SRCLK_PIN   PORTB3
#define RCLK_PORT   PORTB
#define RCLK_PIN    PORTB4

// Pulse the Input Clock
void PULSE_SRCLK();
// Pulse the Storage Register Clock
void PULSE_RCLK();
// Set value on the Data Bus 
// NOTE: Will only account for the LSB of val. If val is not 0 or 1, expect undefined behavior
void SET_SER_VAL(uint8_t bit);

// Send a single bit on the DATA Bus and toggle the Output Clock
// NOTE: Will only account for the LSB of bit. If val is not 0 or 1, expect undefined behavior
void send_bit(uint8_t bit);

// Send 8 consecutive bits on the DATA Bus and toggle the Output Clock
void send_byte(uint8_t byte);

// Clear the memory of the input register AND toggle the Output Clock
// NOTE: This clears the memory by writing 8 '0' bits, not toggling the SRCLR pin. This is the equivlent of send_byte(0)
void clear_register();
