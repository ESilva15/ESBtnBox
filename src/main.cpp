/* BtnBOX by Eduardo Silva
 * Notes:
 * calling Wire.begin() will take use of the pins 2 and 3. Maybe try not using
 * them from the getgo
 */

#include <Arduino.h>
#include "595n.h"
#include "165.h"

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
size_t num_rows = sizeof(rows) / sizeof(rows[0]);

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
size_t num_cols = sizeof(cols) / sizeof(cols[0]);

SR595N input = NewSR595N(IN_SERIAL_PIN, IN_LATCH_PIN, IN_CLOCK_PIN);
SR165 output = NewSR165(OUT_PARALLEL_LOAD_IN, OUT_CLOCK_ENABLE, 
                        OUT_CLOCK_IN, OUT_COMPLEMENTARY_OUT);

void setup() {
  Serial.begin(115200);
  SR595N_write(&input, 0b00000100);
}

void loop(void) {
  uint8_t scanResults[num_rows];

  for (size_t row = 0; row < num_rows ; row++) {
    SR595N_write(&input, rows[row]);
    delayMicroseconds(5);
  
    scanResults[row] = SR165_read(&output);
  }
  
  for(size_t row = 0; row < num_rows; row++) {
    Serial.println(scanResults[row], BIN);
  }
  // Serial.println(SR165_read(&output), BIN);

  delay(5);
}
