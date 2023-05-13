 /*
The loop uses the LDR to measure light intensity and controls an LED based on the measured values. 
It also uses a LCD display and buttons to allow the user to set the desired light intensity and adjust various control parameters.
 This version however implements a Proportional-Integral (PI) control function to adjust the LED's brightness 
 to match the desired light intensity set by the SP and remove the eror in comparison with the KP

 The purpose of this lab was to become familiar with the implementation of Intergral Gain and how it removes error.
 */
 
// Declare necessary libraries
#include <LiquidCrystal.h>

// Define pins for the LCD display 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

// Define pin and variable for the light sensor
int sensorPin = A0;
int sensorValue;

// Define setpoint and CO variables for the controller
int Setpoint = 300;
int CO;

// Define COPersise variable for the actuator
float COPersise;

// Define pin and variable for the actuator
int actuator = 3;

// Define hysteresis and buttons for user interface
int HYS = 30;
int UpButton = 6;
int DownButton = 4;
int leftButton = 5;
int rightButton = 2

// Define button states and current screen for user interface
int UpButtonState = LOW;
int DownButtonState = LOW;
int leftButtonState = LOW;
int rightButtonState = LOW;
int currentScreen = 0;

// Define error and control constants for the controller
int error = 0;
float KP = 0.10;
float KI = 0.01;

// Define variables for integral action of controller
int intergralAction;
const long interval = 100;
unsigned long previousMillis;
unsigned long currentMillis;




void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16, 2); 
}
void loop() {
  //Setting up the millis counter to utilize in the intergral control 
   currentMillis = millis();
   if (currentMillis - previousMillis >= interval) {
   previousMillis = currentMillis;
   //Calculate the error based off SP-PV
  error = Setpoint-sensorValue;
  //Calculate the Intergral Action for the intergral gain 
  intergralAction = (intergralAction + error);
  //Calulate the CO with KP and KI
  CO =(KP*error)+(KI*intergralAction);
  //CO digital limit switch
  if (CO > 255)
  {
    CO = 255;
  }
 if (CO < 0){
    CO = 0;
 }
 //Store the button values to variables 
   UpButtonState = digitalRead(UpButton);
   DownButtonState = digitalRead(DownButton);
   rightButtonState = digitalRead(rightButton);
   leftButtonState = digitalRead(leftButton);
   if (leftButtonState == 0) {
    // toggle the screen between 0 and 1
    currentScreen = currentScreen+1;  
    // wait to prevent errors 
    delay(100);  
    
  }
else if (rightButtonState == 0) {
    // toggle the screen between 0 and 1
    currentScreen = currentScreen-1;  
    // wait to prevent errors 
    delay(100);  
  }
 if (currentScreen == 5){
    currentScreen = 0;
  }
 if (currentScreen == -1)
  {
    currentScreen = 4;
  }
  lcd.clear();
  sensorValue = analogRead(sensorPin); // Read the sensor value
// 1st screen 
if (currentScreen == 0) {  
  lcd.setCursor(0,0);
    // display the "raw value: screen
    lcd.print("PV value:");
    // Displays the actual value of the LDR
    lcd.print(sensorValue);
delay(100);
  } 
  //2nd Screen
  if (currentScreen == 1) { 
    lcd.setCursor(0,0); 
  lcd.print("SP value:");
  // Displays the actual value  
  lcd.print(Setpoint); 
  delay(100);
  //Adjuist Setpoint value 
  if  (UpButtonState == 0){
  Setpoint = Setpoint +10;
  }
  if  (DownButtonState == 0){
  Setpoint = Setpoint -10;
  } 
   if  (Setpoint  >= 810){
  Setpoint = 810;
  } 
     if  (Setpoint  <= 0){
  Setpoint = 0;
  } 
  }
  // 3rd Screen 
if (currentScreen == 2) {  
    lcd.setCursor(0,0);
  lcd.print("Error value:");
  // Displays the actual value  
  lcd.print(error); 
  delay(100);
 }
 //4th Screen
 if (currentScreen == 3) {  
    lcd.setCursor(0,0);
  lcd.print("KP value:");
  // Displays the actual value  
  lcd.print(KP); 
  delay(100);
 //Adjust KP value 
  if  (UpButtonState == 0){
  KP = KP +0.1;
  }
  if  (DownButtonState == 0){
  KP = KP -0.1;
  }
     if  (KP  <= 0){
  KP = 0;
  } 
 }
 //5th screen 
  if (currentScreen == 4) {  
    lcd.setCursor(0,0);
    // print "KI value:"
  lcd.print("KI value:");
  // Displays the actual value  
  lcd.print(KI); 
  delay(100);
 //Adjust KI's value 
  if  (UpButtonState == 0){
  KI = KI +0.1;
  }
  if  (DownButtonState == 0){
  KI = KI -0.1;
  }
     if  (KI  <= 0){
  KI = 0;
  } 
 }
 COPersise = (CO / 10);
 //Write the actuator aka the LED to the value of the CO
 analogWrite(actuator,COPersise);

  Serial.print(sensorValue); // Print the sensor reading
    Serial.print("\t");
  Serial.print(CO); // Print the sensor reading
  Serial.print("\t");

  Serial.println(Setpoint); // Print the sensor reading


}
}