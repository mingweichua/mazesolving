/**********************************
 *  6 Key Ultrasonic Piano        *
 *  Works with Processing on PC   *
 *  by Kenneth Tan                *
 *  27/10/2016                    *
 *  Rev v2 03/08/2017             *
 **********************************/
#include <NewPing.h>

#define SONAR_NUM 6
#define MAX_DIST 200
#define THRESHOLD_CM 20

//unsigned long currentTime = 0, previousTime = 0;
int ledArray[SONAR_NUM] = {2, 3, 4, 7, 6, 5};

int dist;
unsigned int c = 6;
int i,j,x,r;

NewPing sonar[SONAR_NUM] = {
  NewPing(28,29,MAX_DIST),
  NewPing(30,31,MAX_DIST),
  NewPing(32,33,MAX_DIST),
  NewPing(26,27,MAX_DIST),
  NewPing(24,25,MAX_DIST),
  NewPing(22,23,MAX_DIST),
};

void setup() {
  Serial.begin(9600);
  for (i = 0; i < SONAR_NUM; i++){
    pinMode(ledArray[i],OUTPUT);
    digitalWrite(ledArray[i],LOW);
  }
}

void loop() {
  //currentTime = millis()-previousTime;
  if(Serial.available()){
    c = Serial.read();
//    //Power update
//    if (c == 'p'){
//      pwr = true;
//      //previousTime = millis();
//      //c = 7;
//    }
//    else if (c == 's'){
//      pwr = false;
//      //c = 7;
//    }
    //LED update
//    else{
      for(i = 0; i < SONAR_NUM; i++){
        r = c % 2;
        if(r){
          digitalWrite(ledArray[i], HIGH);
        }
        else{
          digitalWrite(ledArray[i], LOW);
        }
        c = c / 2;
      }
//    }
  }
  
  //Sonar update
  j = 0;
  for(i = SONAR_NUM; i >0; i--){
    j = j * 2;
    //while((millis()-previousTime) % 40 != 7);       //33+(n*40)ms real time marking
    delay(20);
    dist = sonar[i-1].ping_cm();
    //Serial.println('%d',j);
    j = (dist > 0 && dist < THRESHOLD_CM)? j + 1: j;
  }

  //Key update
    Serial.write(j);

}
