#ifndef __595N__
#define __595N__

#include <stdint.h>

typedef struct SR595N {
  uint8_t ser;
  uint8_t rclk;
  uint8_t srclk;
} SR595N;

SR595N NewSR595N(uint8_t ser, uint8_t rclkh, uint8_t srclk);
void SR595N_write(SR595N *sr, uint8_t value);

#endif
