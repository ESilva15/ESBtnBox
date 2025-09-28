#ifndef __165__
#define __165__

#include "Arduino.h"
#include <stdint.h>

typedef struct SR165 {
  uint8_t parallelLoadIn;
  uint8_t clockEnable;
  uint8_t complementaryOut;
  uint8_t clockIn;
} SR165;

SR165 NewSR165(uint8_t pl, uint8_t ce, uint8_t cp, uint8_t q7);
byte SR165_read(SR165 *sr);

#endif
