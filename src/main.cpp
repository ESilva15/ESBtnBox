/* BtnBOX by Eduardo Silva
 * Notes:
 * calling Wire.begin() will take use of the pins 2 and 3. Maybe try not using
 * them from the getgo
 */

// The Matrix
/* 
 * 1 1 1 R3 F9 F10 F11 F12
 * 1 1 1 R2 F5 F6  F7  F8
 * 1 1 1 M1 F1 F2  F3  F4
 * 1 1 1 m1 R1 r1  r2  r3
 * 1 1 1 M2 T3 T4  T5  T6
 * 1 1 1 m2 t3 t4  t5  t6
 *
 * Toggle Switches (On - Off - On):
 * T -> up, t -> down.
 * From left to right
 *
 * Toggle Switches (Hold On - Off - Hold On)
 * M -> up, m -> down
 * From left to right
 *
 * Puny Rotary Encoders Click:
 * R1 - 3
 * From left to right
 *
 * Chonky Rotary Encoder:
 * R0 - 3
 * Positions on the encoder
 *
 * F keys:
 * F1 - F12
 * Count them
 *
 */

#include <Arduino.h>
#include "595n.h"
#include "165.h"
#include <Joystick.h>

// NOTES - 595N
// On the board, the first output pin on the SR595 is Qb
// Which means that our outputs go from 0b00000010 to 0b01111110
#define IN_SERIAL_PIN 4 // SER   - pin14 (Serial Pin)
#define IN_LATCH_PIN  5 // RCLK  - pin12 (Latch Pin)
#define IN_CLOCK_PIN  6 // SRCLK - pin11 (Clock Pin)
/*                      
+--             --+
|P0 P1 P2 P3 P4 P5|
+-----------------+
*/
#define IN_P0 0b01000000
#define IN_P1 0b00100000
#define IN_P2 0b00010000
#define IN_P3 0b00001000
#define IN_P4 0b00000100
#define IN_P5 0b00000010
uint8_t rows[] = {IN_P0, IN_P1, IN_P2, IN_P3, IN_P4, IN_P5};
const size_t NUM_ROWS = 6;

// NOTES - 165
#define OUT_PARALLEL_LOAD_IN  10 // PL - pin1  (Async Parallel Load In)
#define OUT_CLOCK_IN          9  // CP - pin2  (Clock In)
#define OUT_COMPLEMENTARY_OUT 8  // Q7 - pin7  (Complementary Output)
#define OUT_CLOCK_ENABLE      7  // CE - pin15 (Clock Enable)
/*
+--          --+
|P4 P3 P2 P1 P0|
+--------------+
*/
#define OUT_P0 0b11111110
#define OUT_P1 0b11111101
#define OUT_P2 0b11111011
#define OUT_P3 0b11110111
#define OUT_P4 0b11101111
uint8_t cols[] = {OUT_P0, OUT_P1, OUT_P2, OUT_P3, OUT_P4};
const size_t NUM_COLS = 5;

SR595N input = NewSR595N(IN_SERIAL_PIN, IN_LATCH_PIN, IN_CLOCK_PIN);
SR165 output = NewSR165(OUT_PARALLEL_LOAD_IN, OUT_CLOCK_ENABLE, 
                        OUT_CLOCK_IN, OUT_COMPLEMENTARY_OUT);

#define JOYSTICK_BTN_COUNT 32
#define JOYSTICK_HAT_COUNT 0
Joystick_ Joystick(
  JOYSTICK_DEFAULT_REPORT_ID,
  JOYSTICK_TYPE_JOYSTICK,
  JOYSTICK_BTN_COUNT, // Button count
  JOYSTICK_HAT_COUNT, // Hat switch count
  // no axes since this is just buttons
  false, false, false, false, false,
  false, false, false, false, false,
  false
);

void setup() {
  Serial.begin(115200);

  Joystick.begin();
  for(int k = 0; k < JOYSTICK_BTN_COUNT; k++) {
    Joystick.setButton(k, 0);
  }

  SR595N_write(&input, 0b00000100);
}

void loop(void) {
  uint8_t scanResults[NUM_ROWS];

  for (size_t row = 0; row < NUM_ROWS ; row++) {
    SR595N_write(&input, rows[row]);
    delayMicroseconds(5);
  
    scanResults[row] = SR165_read(&output);
  }
  
  Serial.print("\033[2J\033[H");
  for(size_t row = 0; row < NUM_ROWS; row++) {
    Serial.println(scanResults[row], BIN);
  }

  delay(35);
}
