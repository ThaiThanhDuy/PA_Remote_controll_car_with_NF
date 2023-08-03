//Board Arduino Nano
#include <Arduino.h>
//Library for radio
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>
#include <RF24_config.h>
//library for display
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
//Variable basic
//Display
#define Screen_width 128
#define Screen_height 64
#define MOSI 5
#define CLK 4
#define RES 6
#define DC 9
#define CS 10
//RF
const byte Address[6]="12345";
int command=0;
//Joystick
#define JX1 A2
#define JY1 A3
#define JX2 A0
#define JY2 A1
//Function for Joystick
void initializeJoystick1();
void initializeJoystick2();
void commandJoystick();
//Function for radio
void initializeRF();
void connectRX();
void sendCommand();
//Function for Display
void initializeDisplay();
void turnOn();
//Initialized board pin
RF24 radio(7,8); // CE, CSN
Adafruit_SSD1306 display(Screen_width,Screen_height,MOSI,CLK,DC,RES,CS);
void setup() {
  Serial.begin(9600);
  initializeDisplay();
  initializeRF();
  initializeJoystick1();
  initializeJoystick2();
  turnOn();
}
void loop() {
commandJoystick();
sendCommand();
delay(2000);
}
void initializeRF(){
  if (!radio.begin()){
    Serial.println("Module error!!");
    while (1) {}
  } 
  radio.openWritingPipe(Address);
  radio.setPALevel(RF24_PA_MIN); 
  radio.setChannel(80); 
  radio.setDataRate(RF24_250KBPS);
  radio.stopListening(); 
}
void initializeDisplay(){
  if(!display.begin(SSD1306_SWITCHCAPVCC)){
    Serial.println("SSD1306 allocation failed!");
    while(1){}
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(2);
  display.setCursor(30,15);
}
void connectRX(){
   sendCommand();
}
void sendCommand(){
radio.write(&command,sizeof(command));
}
void initializeJoystick1(){
  pinMode(JX1,INPUT);
  pinMode(JY1,INPUT);
}
void initializeJoystick2(){
  pinMode(JX2,INPUT);
  pinMode(JY2,INPUT);
}
void commandJoystick(){
int x1 = analogRead(JX1);
int y1 = analogRead(JY1);
int x2 = analogRead(JX2);
int y2 = analogRead(JY2);
Serial.println("X1-Y1");
Serial.println(x1);
Serial.println(y1);
Serial.println("X2-Y2");
Serial.println(x2);
Serial.println(y2);
Serial.println("End line");
if(500<x1&&600>x1&&500<y1&&600>y1&&500<x2&&600>x2&&500<y2&&600>y2){
command = 0;
display.setCursor(40,20);
display.clearDisplay();
display.print("Stop!");
display.display();
}
else if(x1>1000&&x2>1000){
command = 1;
display.setCursor(10,20);
display.clearDisplay();
display.print("<Forward>");
display.display();
}
else if(x1==0&&x2==0){
command = 2;
display.setCursor(5,20);
display.clearDisplay();
display.print("<Backward>");
display.display();
}
else if(y1==0&&y2==0&&x1>500&&x2>500){
command = 3;
display.setCursor(30,20);
display.clearDisplay();
display.print("<Left>");
display.display();
}
else if(500<x1&&x1<600&&500<x2&&x2<600&&y1>1000&&y2>1000){
command = 4;
display.setCursor(25,20);
display.clearDisplay();
display.print("<Right>");
display.display();
}
else if(500<x1&&x1<600&&1000<x2&&500<y1&&y1<600&&500<y2&&y2<600){
command = 5;
display.setCursor(10,20);
display.clearDisplay();
display.print("<Diagonal");
display.setCursor(40,40);
display.print("Left>");
display.display();
}
else if(500<x2&&x2<600&&1000<x1&&500<y1&&y1<600&&500<y2&&y2<600){
command = 6;
display.setCursor(10,20);
display.clearDisplay();
display.print("<Diagonal");
display.setCursor(35,40);
display.print("Right>");
display.display();
}
else if(500<x1&&x1<600&&x2==0&&500<y1&&y1<600&&500<y2&&y2<600){
command = 7;
display.setCursor(10,20);
display.clearDisplay();
display.print("<Diagonal");
display.setCursor(10,40);
display.print("LeftBack>");
display.display();
}
else if(500<x2&&x2<600&&x1==0&&500<y1&&y1<600&&500<y2&&y2<600){
command = 8;
display.setCursor(10,20);
display.clearDisplay();
display.print("<Diagonal");
display.setCursor(0,40);
display.print("RightBack>");
display.display();
}
}
void turnOn(){
display.setTextSize(1);
display.setCursor(30,20);
display.clearDisplay();
display.print("Connecting");
display.display();
delay(500);
display.setCursor(30,20);
display.clearDisplay();
display.print("Connecting.");
display.display();
delay(500);
display.setCursor(30,20);
display.clearDisplay();
display.print("Connecting..");
display.display();
delay(500);
display.setCursor(30,20);
display.clearDisplay();
display.print("Connecting...");
display.display();
delay(500);
display.setTextSize(2);
display.setCursor(25,20);
display.clearDisplay();
display.print("Welcome");
display.display();
delay(1000);
display.setCursor(25,20);
display.clearDisplay();
display.print("=^...^=");
display.display();
delay(3000);
}
