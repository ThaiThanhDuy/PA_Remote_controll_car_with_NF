//Board Arduino Uno
#include <Arduino.h>
//Library for motor
#include <AFMotor.h>
#include <Servo.h>
//Library for radio
#include <RF24.h>
#include <nRF24L01.h>
#include <SPI.h>
//library for display
#include <Adafruit_SSD1306.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
//Variable basic
#define Speed 200  
#define Screen_width 128
#define Screen_height 32
const byte Address[6]= "12345";
int x1=0;
int y1=0;
//Initialized board pin
AF_DCMotor motor1(1);
AF_DCMotor motor3(3);
RF24 radio(9, 10); // CE, CSN
Adafruit_SSD1306 display(Screen_width,Screen_height,&Wire,-1);
//Function for motor
void initializeMotor();
void runForward();
void runBackward();
void turnRight();
void turnLeft();
void diagonalRight();
void diagonalLeft();
void diagonalRightBack();
void diagonalLeftBack();
void stop();
void moving();
//Function for display
void initializeDisplay();
void ForwardDisplay();
void turnOn();
//Function for nRF
void initializeRF();
void connectTX();
void receiveCommand();
int command = 0;
void setup() {    
Serial.begin(9600);                              
initializeRF();
initializeDisplay();
initializeMotor();
turnOn();
}
void loop(){
  connectTX();
  moving();
}
void initializeMotor(){
  motor1.setSpeed(Speed-14);
  motor3.setSpeed(Speed+32);
}
void runForward(){
  motor1.run(FORWARD);
  motor3.run(FORWARD);
}
void stop(){
  motor1.run(RELEASE);
  motor3.run(RELEASE);
}
void runBackward(){
  motor1.run(BACKWARD);
  motor3.run(BACKWARD);
}
void turnRight(){
  motor1.run(FORWARD);
  motor3.run(RELEASE);
  delay(2200);
}
void turnLeft(){
  motor1.run(RELEASE);
  motor3.run(FORWARD);
  delay(1400);
}
void diagonalRight(){
  motor1.run(FORWARD);
  motor3.run(RELEASE);
  delay(1200);
}
void diagonalLeft(){
  motor1.run(RELEASE);
  motor3.run(FORWARD);
  delay(1000);
}
void diagonalRightBack(){
  motor1.run(BACKWARD);
  motor3.run(RELEASE);
  delay(1200);
}
void diagonalLeftBack(){

  motor1.run(RELEASE);
  motor3.run(BACKWARD);
  delay(800);
}
void initializeDisplay(){
  if(!display.begin(SSD1306_SWITCHCAPVCC,0x3C)){
    Serial.println("SSD1306 allocation failed!");
    while(1){}
  }
   display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(30,15);

}
void ForwardDisplay(){
  display.println("Run Forward");
  display.display();
}
void connectTX(){
  if(radio.available()){
    receiveCommand();
  }
  else {
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Waiting");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Waiting.");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Waiting..");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Waiting...");
  display.display();
  stop();
  }
}
void initializeRF(){
  if (!radio.begin()) 
  {
    display.println("Module error !!");
    while (1) {}
  } 
  radio.openReadingPipe(1,Address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(80);
  radio.setDataRate(RF24_250KBPS);
  radio.startListening();

}
void receiveCommand(){
  if(radio.available()){
  radio.read(&command,sizeof(command));
  if(command==0){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Stop!");
  display.display();

  }
  else if(command==1){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Forward");
  display.display();

  }
  else if(command==2){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Backward");
  display.display();

  }
  else if(command==3){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Left");
  display.display();
  }
  else if(command==4){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Right");
  display.display();
  }
  else if(command==5){
  display.setCursor(30,15);
  display.clearDisplay();
  display.print("Diagonal Left");
  display.display();
  }
  else if(command==6){
  display.setCursor(30,15);
  display.clearDisplay();
  display.print("Diagonal Right");
  display.display();
 
  }
  else if(command==7){
  display.setCursor(10,15);
  display.clearDisplay();
  display.print("Diagonal Left Back");
  display.display();

  }
  else if(command==8){
  display.setCursor(10,15);
  display.clearDisplay();
  display.print("Diagonal Right Back");
  display.display();
  }
  }
}
void turnOn(){
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Connecting");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Connecting.");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Connecting..");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("Connecting...");
  display.display();
  delay(500);
  display.setCursor(50,15);
  display.clearDisplay();
  display.print("Welcome");
  display.display();
  delay(500);
  display.setCursor(40,15);
  display.clearDisplay();
  display.print("=^...^=");
  display.display();
  delay(500);
  delay(3000);
}
void moving(){
  if(command==0){
  stop();
  }
  else if(command==1){
  runForward();
  }
  else if(command==2){
  runBackward();
  }
  else if(command==3){
  turnLeft();
  }
  else if(command==4){
  turnRight();
  }
  else if(command==5){
  diagonalLeft();
  }
  else if(command==6){
  diagonalRight();
  }
  else if(command==7){
  diagonalLeftBack();
  }
  else if(command==8){
  diagonalRightBack();
  }
}