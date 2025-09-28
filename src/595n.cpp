#include "Arduino.h"
#include "595n.h"

SR595N NewSR595N(uint8_t ser, uint8_t rclk, uint8_t srclk) {
  struct SR595N newSR = {
    .ser = ser,
    .rclk = rclk,
    .srclk = srclk
  };

  pinMode(newSR.ser, OUTPUT);
  pinMode(newSR.rclk, OUTPUT);
  pinMode(newSR.srclk, OUTPUT);

  return newSR;
}

void SR595N_write(SR595N *sr, uint8_t value) {
  digitalWrite(sr->rclk, LOW);
  shiftOut(sr->ser, sr->srclk, MSBFIRST, value);
  digitalWrite(sr->rclk, HIGH);
}
