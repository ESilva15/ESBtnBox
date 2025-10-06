#include "rotaryEncoder.h"
#include "Arduino.h"

RotaryEncoder NewRotaryEncoder(int clk, int dt) {
  return RotaryEncoder{
    .clkPin = clk,
    .dtPin = dt,
  };
}

void RotaryEncoder_init(RotaryEncoder *enc) {
  pinMode(enc->clkPin, INPUT_PULLUP);
  pinMode(enc->dtPin, INPUT_PULLUP);
  enc->lastStateCLK = digitalRead(enc->clkPin);
}

int RotaryEncoder_read(RotaryEncoder *enc) {
  int curStateClk = digitalRead(enc->clkPin);
  int direction = RE_NOCHANGE;
  
  if (curStateClk != enc->lastStateCLK && curStateClk == 1) {
    if (digitalRead(enc->dtPin) != curStateClk) {
      direction = RE_CCW; 
    } else {
      direction = RE_CW; 
    }
  }

  enc->lastStateCLK = curStateClk;

  return direction;
}
