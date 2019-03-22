/**********************************
 *  6 Key Ultrasonic Piano        *
 *  Works with Arduino Mega       *
 *  by Kenneth Tan                *
 *  27/10/2016                    *
 *  Rev v2 03/08/2017             *
 **********************************/

import processing.serial.*;
import processing.sound.*;

float[] t60 = {2000, 600, 2};
float[] t75 = {1600, 300, 1.6};
float[] t80 = {1500, 100, 1.5};
float[] t100 = {1200, 15, 1.2};
float[] t120 = {1000, 5, 1}; 

String[] songList = {"T60.wav","T80-2.wav","T60-3.wav","T80-4.wav","T60-5.wav","T100-6.wav","T80.wav","T100.wav","T80-7.wav"};
float[][] tempoList = {t60,t80,t60,t80,t60,t100,t80,t100,t80};
SoundFile file, file1;
PImage logoPng;
PShape logoSvg, rectangle;
Serial myPort;
//String portName = "/dev/cu.usbmodem6";     //Substitute with suitable COM port before running
String portName = "COM17 ";     //Substitute with suitable COM port before running

color grey = #878787;
color red = #FF0000;
color green = #00FF00;
color rcolor = #000000;

long currentTime, setupTime;
int currentKey = 0, correctKey = 0;
boolean gameState = false;
int songDuration = 0;
int comboCounter = 0;
int yourCombo = 0;
int highestCombo = 0;
int songNum = 0;
int offset = 50;            //Offset in ms for laptop comm calibration

float[] songVal = tempoList[songNum];
float[] songTempo = songVal;
String songName = songList[songNum];
float bias = 0;

void setup() {
  fullScreen();
  background(grey);
  textSize(height/15);
  textAlign(CENTER,CENTER);
  shapeMode(CENTER);
  logoSvg = loadShape("logo.svg");
  setSongValues();
  file1 = new SoundFile(this, "alarm.mp3");
  setupTime = millis();
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  //@300ms
  while (((currentTime = millis() - setupTime) % int(songTempo[0])) < int(songTempo[1]));
  background(rcolor); 
  if (gameState == true){
//    correctKey = int(pow(2,floor(random(6))) + pow(2,(floor(random(6))-1)) + pow(2,(floor(random(6))-1)));    //Samuek 3key edition. Certain death version.
//    if (correctKey>56){
//        correctKey = 56;
//    }
    correctKey = int(pow(2,floor(random(6))) + pow(2,(floor(random(6))-1)));
    myPort.write(correctKey);
  }
  //@1000ms
  while(((currentTime = millis() - setupTime) % int(songTempo[0])) > 0);
  file1.stop();
//  currentKey = correctKey;
  if (gameState == false){
    rcolor = grey;
    
    file1.stop();
    text("Press SPACE to play!", width/2, 1.5 *height/5);
    shape(logoSvg, width/2, height/2);
    text("Your combo:\n"+str(yourCombo), 3*width/4, 3*height/4);
    text ("Highest combo today:\n" + str(highestCombo), width/4, 3*height/4);
    myPort.write(63);
  }
  else if(songDuration < comboCounter * songTempo[2]){
    file.stop();
    rcolor = green;
    text("You did it!\nCombo:\n" + str(comboCounter), width/2, height/2);
    gameState = false;
    yourCombo = comboCounter;
    if(yourCombo > highestCombo){
      highestCombo = yourCombo;
    }
    comboCounter = 0;
    myPort.write(63);
    delay(500);
    myPort.write(0);
    delay(500);
    myPort.write(63);
    delay(500);
    myPort.write(0);
    delay(500);
    myPort.write(63);
    delay(500);
    myPort.write(0);
  }
  else if(currentKey == correctKey){
    myPort.write(0);
//    file.jump(bias + songTempo[2] * comboCounter);
    if (songName == "T100-6.wav" && comboCounter == 19){
      songTempo = t120;
      bias = t100[2] * 20 - t120[2] * 20;      
      setupTime += bias;
    }
    if (songName == "T80-4.wav" && comboCounter == 150){
      songTempo = t75;
      bias = t80[2] * 151 - t75[2] * 151;
      setupTime += bias;
    }
    if (songName == "T80-4.wav" && comboCounter == 178){
      songTempo = t80;
      bias = t75[2] * 28 - t80[2] * 28;
      setupTime += bias;
    }
    if (songName == "T80-7.wav" && comboCounter == 8){
      songTempo = t120;
      bias = t80[2] * 9 - t120[2] * 9;
      setupTime += bias;
    }
    if (songName == "T80-7.wav" && comboCounter == 27){
      songTempo = t100;
      bias = t120[2] * 19 - t100[2] * 19;
      setupTime += bias;
    }
    comboCounter++;
    rcolor = color(int(random(256)),int(random(256)),int(random(256)));
    background(rcolor);
    shape(logoSvg, width/2, height/2);
    String comboString = (comboCounter > 10)? "COMBO!\n" + str(comboCounter) : str(comboCounter);
    text(comboString, width/2, 3*height/4);
    
  }
  else{
    rcolor = red;
    text("GAME OVER\nCombo:\n" + str(comboCounter), width/2, height/2);
    file.stop();
    file1.play();
    yourCombo = comboCounter;
    if(yourCombo > highestCombo){
      highestCombo = yourCombo;
    }
    comboCounter = 0;
    bias = 0;
    songTempo = songVal;
    gameState = false;
    myPort.write(9);
    delay(200);
    myPort.write(18);
    delay(200);
    myPort.write(36);
    delay(200);
    myPort.write(0);
  }
    text("Electrical & Electronics, Mechatronic Engineering",width/2, height/5);
 
}

void serialEvent(Serial myPort) {
  currentKey = myPort.read();
  println(currentKey);
}

void keyTyped(){
  switch (key){
    case ' ':
    gameState = !gameState;
    //comboCounter = 130;
    if (gameState == true){
      setupTime = millis()-offset;
      file.play();
    }
    else{
      file.stop();
      comboCounter = 0;
    }
    break;
    case '1': 
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    songNum = key-49;
    setSongValues();
    break;
    case '0': songTempo = t120;
    default:
  }
}

void setSongValues(){
  songVal = tempoList[songNum];
  songTempo = songVal;
  songName = songList[songNum];
  bias = 0;
  file = new SoundFile(this, songName);
  songDuration = int(file.duration()) - 1;
}

//String filenamegen(int track, int part){
  
//  String prefix = "T";
//  String subfix = "P";
//  String zero = "0";
//  String trackString = track/10 > 0 ? prefix + str(track) : prefix + zero + str(track);
//  String partString = part/100 > 0 ? subfix + str(part) : part/10 > 0 ? subfix + zero + str(part) : subfix + zero + zero + str(part);
//  return trackString + partString;
//}  
