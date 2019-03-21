#include <NewPing.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     7
#define LTRIGGER_PIN  8
#define LECHO_PIN     9
#define RTRIGGER_PIN  12
#define RECHO_PIN     13
#define MAX_DISTANCE 500

#define lmin 230
#define rmin 230
#define mid 150
#define lmax 2000
#define rmax 2000

int diffdistance;
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);
NewPing sonar1(LTRIGGER_PIN, LECHO_PIN, MAX_DISTANCE);
NewPing sonar2(RTRIGGER_PIN, RECHO_PIN, MAX_DISTANCE);

int in1 = 2, in2 = 3, in3 = 4, in4 = 5; // define motor pin
int pwml = 10, pwmr = 11;
int distance, distanceL, distanceR;
void stopM();
void goS();
void turnL();
void turnR();
void uturn();
//##############################################################
void setup() {
  Serial.begin(9600);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  //ultrasonic front
  pinMode(pwml, OUTPUT);
  pinMode(pwmr, OUTPUT);
  analogWrite(pwml, 40);
  analogWrite(pwmr, 40);
  distance = sonar.ping_cm();
  distanceL = sonar1.ping_cm();
  distanceR = sonar2.ping_cm();
}
void loop() {

  while (distance > 200) {
    gostraight();
    if (distanceL < 3) {
      analogWrite(pwml, 40);
      analogWrite(pwmr, 0);
      return;
    }
    if (distance > 3) {
      analogWrite(pwml, 0);
      analogWrite(pwmr, 40);
      return;
    }
  }
  stopm();
  if (distanceR > distanceL) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    turnR();
    gostraight();
    return;
  }
  if (distanceL > distanceR) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    turnleft();
    gostraight();
    return;
  }
  if (distanceL < 5 && distanceR < 5) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    reverse();
    stopm();
    return;
  }
}
void turnR() {                              // stop for 1 sec
  digitalWrite(in1, HIGH);                  //
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(500);
}
void gostraight() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void stopm() {
  digitalWrite(in1, HIGH);                  //
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}
void uturn() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(1000);
}
void reverse() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
void turnleft(){
    digitalWrite(in1, HIGH);                  //
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500);
}
