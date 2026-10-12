#include <Wire.h>

#define SLAVE_ADDR 0x10

Wire.begin(); // join i2c bus (address optional for master)

while (1) 
{
  Wire.beginTransmission(SLAVE_ADDR); // transmit to device #4
  for (int i = 0; i < 4; i++) {
    uint8_t request[2];
    request[0] = i;
    request[1] = (i % 2);
    Wire.write(request);              // sends one byte
    delay(500);
  }
  Wire.endTransmission();    // stop transmitting
}
