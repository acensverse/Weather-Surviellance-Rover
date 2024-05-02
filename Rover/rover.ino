/*IR remote control car with Arduino.
 * http://srituhobby.com
 */
 
#include <AFMotor.h>
#include <IRremote.h>

AF_DCMotor m1(1);
AF_DCMotor m2(2);
AF_DCMotor m3(3);
AF_DCMotor m4(4);

IRrecv IR(A0);
decode_results result;

int Speed = 150;

#define up 16736925
#define down 16754775
#define left 16720605
#define right 16761405
#define Stop 16738455

void setup() {
  Serial.begin(9600);
  m1.setSpeed(Speed);
  m2.setSpeed(Speed);
  m3.setSpeed(Speed);
  m4.setSpeed(Speed);
  IR.enableIRIn();
}

void loop() {
  if (IR.decode(&result)) {
    Serial.println(result.value);
    IR.resume();
  }
  delay(100);
  if (result.value == up ) {
    m1.run(FORWARD);
    m2.run(FORWARD);
    m3.run(FORWARD);
    m4.run(FORWARD);
  } else if (result.value == down ) {
    m1.run(BACKWARD);
    m2.run(BACKWARD);
    m3.run(BACKWARD);
    m4.run(BACKWARD);
  } else if (result.value == Stop) {
    m1.run(RELEASE);
    m2.run(RELEASE);
    m3.run(RELEASE);
    m4.run(RELEASE);
  } else if (result.value == left) {
    m1.run(FORWARD);
    m2.run(BACKWARD);
    m3.run(BACKWARD);
    m4.run(BACKWARD);
  } else if (result.value == right) {
    m1.run(BACKWARD);
    m2.run(FORWARD);
  }
}
