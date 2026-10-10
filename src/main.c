#include <avr/io.h>
#include <util/delay.h>
#include "shift.h"
int main(int argc, char *argv[]) {
  // pins used for i2c: PB0, PB2
  // pins used for shift register: PB1, PB3, PB4
  // PB1: Data Clock (SER)
  // PB3: Input Clock (SRCLK) (shift register clock)
  // PB4: Output Clock (RCLK) (storage register clock)

  DDRB |= (1 << DDB1);
  DDRB |= (1 << DDB3);
  DDRB |= (1 << DDB4);

  while (1) {
    PORTB |= (1 << PORTB1);
    for (int i = 0; i < 4; i++) {
      PORTB |= (1 << PORTB3);
      PORTB |= (1 << PORTB4);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB3);
      PORTB &= ~(1 << PORTB4);
      _delay_ms(10);
    }
    PORTB &= ~(1 << PORTB1);
    for (int i = 0; i < 4; i++) {
      PORTB |= (1 << PORTB3);
      PORTB |= (1 << PORTB4);
      _delay_ms(500);
      PORTB &= ~(1 << PORTB3);
      PORTB &= ~(1 << PORTB4);
      _delay_ms(10);
    }
  }
}
