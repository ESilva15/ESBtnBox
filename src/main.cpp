/* BtnBOX by Eduardo Silva
 * Notes:
 * calling Wire.begin() will take use of the pins 2 and 3. Maybe try not using
 * them from the getgo
 */

#include <Arduino.h>
#include "595n.h"
#include "165.h"
// #include "Wire.h"

// NOTES - 595N
// On the board, the first output pin on the SR595 is Qb
// Which means that our outputs go from 0b00000010 to 0b01111110
#define IN_SERIAL_PIN 4 // SER   - pin14 (Serial Pin)
#define IN_LATCH_PIN  5 // RCLK  - pin12 (Latch Pin)
#define IN_CLOCK_PIN  6 // SRCLK - pin11 (Clock Pin)
/*                      
+--             --+
|P5 P4 P3 P2 P1 P0|
+-----------------+
P0 0b00000010
P1
*/

// NOTES - 165
#define OUT_PARALLEL_LOAD_IN  10 // PL - pin1  (Async Parallel Load In)
#define OUT_CLOCK_IN          9  // CP - pin2  (Clock In)
#define OUT_COMPLEMENTARY_OUT 8  // Q7 - pin7  (Complementary Output)
#define OUT_CLOCK_ENABLE      7  // CE - pin15 (Clock Enable)

SR595N input = NewSR595N(IN_SERIAL_PIN, IN_LATCH_PIN, IN_CLOCK_PIN);
SR165 output = NewSR165(OUT_PARALLEL_LOAD_IN, OUT_CLOCK_ENABLE, 
                        OUT_CLOCK_IN, OUT_COMPLEMENTARY_OUT);

void setup() {
  Serial.begin(115200);

  SR595N_write(&input, 0b10101010);
}

void loop(void) {
  delay(200);

  byte srOutput = SR165_read(&output);

  Serial.println(srOutput, BIN);
}
