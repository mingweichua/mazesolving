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
}
void loop() {
  Serial.print("front: ");
  Serial.print(sonar.ping());
  Serial.print("\t");
  Serial.print("left: ");
  Serial.print(sonar1.ping());
  Serial.print("\t");
  Serial.print("right: ");
  Serial.println(sonar2.ping());
  distance = sonar.ping();
  distanceL = sonar1.ping();
  distanceR = sonar2.ping();
  if (distanceL <= 250 && distanceR <= 250) {
    if ( distanceL > distanceR) {
      analogWrite(pwml, 35);
      analogWrite(pwmr, 40);
      goS();
    }
    else if (distanceL < distanceR) {
      analogWrite(pwml, 40);
      analogWrite(pwmr, 35);
      goS();
    }
    else if (distanceL == distanceR) {
      analogWrite(pwml, 40);
      analogWrite(pwmr, 40);
      goS();
    }
  }
  else if (distanceR >= 250) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    goS();
  }
  else if (distanceL >= lmax && distance <= mid) {  // T junction
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    turnL();
  }
  else if (distanceL <= lmin && distance <= mid && distanceR >= rmax) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    turnR();
  }
  else if (distanceL <= lmin && distance <= mid && distanceR <= rmin) {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    uturn();
  }
  else if (distanceL > 8000 && distance > 8000 && distanceR > 8000) {
    stopM();
  }
  else {
    analogWrite(pwml, 40);
    analogWrite(pwmr, 40);
    goS();
  }
}
//##############################################################
void goS() {                                    // go straight
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}
void stopM() {                                 // stop all motors
  digitalWrite(in1, HIGH);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
}
void turnL() {                                // stop for 1 sec
  digitalWrite(in1, HIGH);                    // turn l
  digitalWrite(in2, HIGH);                    // moves forward
  digitalWrite(in3, HIGH);
  digitalWrite(in4, HIGH);
  delay(1000);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(500);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(1000);
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
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(1000);
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
void reverse(){
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}
