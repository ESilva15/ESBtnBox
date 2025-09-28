#include "Arduino.h"
#include <stdint.h>
#include "165.h"

SR165 NewSR165(uint8_t pl, uint8_t ce, uint8_t cp, uint8_t q7) {
  SR165 newSr = {
    .parallelLoadIn = pl,
    .clockEnable = ce,
    .complementaryOut = q7,
    .clockIn = cp
  };

  pinMode(newSr.clockIn, OUTPUT);
  pinMode(newSr.clockEnable, OUTPUT);
  pinMode(newSr.parallelLoadIn, OUTPUT);
  pinMode(newSr.complementaryOut, INPUT);

  return newSr;
}

byte SR165_read(SR165 *sr) {
  // Write pulse to load pin
  digitalWrite(sr->parallelLoadIn, LOW);
  delayMicroseconds(5);
  digitalWrite(sr->parallelLoadIn, HIGH);
  delayMicroseconds(5);
 
  // Get data from 74HC165
  digitalWrite(sr->clockIn, HIGH);
  digitalWrite(sr->clockEnable, LOW);
  byte incoming = shiftIn(sr->complementaryOut, sr->clockIn, LSBFIRST);
  digitalWrite(sr->clockEnable, HIGH);

  return incoming;
}
