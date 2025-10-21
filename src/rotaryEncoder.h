#ifndef __ROTARY_ENC__
#define __ROTARY_ENC__

const int RE_NOCHANGE = 0;
const int RE_CCW = -1;
const int RE_CW = 1;
const int RE_PULSE_DURATION = 20000; // microsseconds

typedef struct {
  int clkPin;
  int dtPin;

  int lastStateCLK;
} RotaryEncoder;

RotaryEncoder NewRotaryEncoder(int clk, int dt);
void RotaryEncoder_init(RotaryEncoder *enc);
int RotaryEncoder_read(RotaryEncoder *enc);

#endif
