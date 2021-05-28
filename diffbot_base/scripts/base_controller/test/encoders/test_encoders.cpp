/* Encoder Library - TwoKnobs Example
 * http://www.pjrc.com/teensy/td_libs_Encoder.html
 *
 * This test code can be used to manually check the encoders.
 * Turn the wheels by hand and check the output in the serial monitor.
 */

#include <unity.h>

#include "diffbot_base_config.h"
#include "encoder.h"


// Encoder setup
// Change these pin numbers to the pins connected to your encoder.
//   Best Performance: both pins have interrupt capability
//   Good Performance: only the first pin has interrupt capability
//   Low Performance:  neither pin has interrupt capability
diffbot::Encoder encoderLeft(ENCODER_LEFT_H1, ENCODER_LEFT_H2);  // Default pins 5, 6
diffbot::Encoder encoderRight(ENCODER_RIGHT_H1, ENCODER_RIGHT_H2); // Default pins 7, 8
//   avoid using pins with LEDs attached

void setup() {
  Serial.begin(115200);
  Serial.println("DiffBot Wheel Encoders:");
}

long positionLeft  = -999;
long positionRight = -999;

int test_start_time = millis();
int test_max_time = 5000;

void loop() {
  UNITY_BEGIN();
  long newLeft, newRight;
  newLeft = encoderLeft.read();
  newRight = encoderRight.read();
  if (newLeft != positionLeft || newRight != positionRight) {
    Serial.print("Left = ");
    Serial.print(newLeft);
    Serial.print(", Right = ");
    Serial.print(newRight);
    Serial.println();
    positionLeft = newLeft;
    positionRight = newRight;
  }
  // if a character is sent from the serial monitor,
  // reset both back to zero.
  if (Serial.available()) {
    Serial.read();
    Serial.println("Reset both wheel encoders to zero");
    encoderLeft.write(0);
    encoderRight.write(0);
    UNITY_END();
  }

  if (millis() - test_start_time > test_max_time)
  {
    UNITY_END();
  }
}


