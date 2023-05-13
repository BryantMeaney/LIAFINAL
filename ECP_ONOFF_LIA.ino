/* This code is for a system that controls an actuator based on the reading of a light sensor. 
The system has several buttons to control the setpoint and hysteresis values. The LCD display
 shows the current sensor reading, setpoint value, and hysteresis value depending on which screen 
 is selected using the left and right buttons. The actuator is controlled using the CO (control output)
  value is calculated based on the difference between the sensor reading and setpoint value with 
  the hysteresis value as a threshold
  
  The purpose of this lab was to become familiar with the most basic fourm of automatic control 
that being the simple on off control, this will simply write 100% or 0% to try to reach the Setpoint
  */

// assiging pins to the LCD Display
#include <LiquidCrystal.h>
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);

int sensorPin = A0; // Define the analog pin for the light sensor
// Variable to store the sensor reading   
int sensorValue = 100;
// Setpoint value for the controller
int Setpoint = 100;
// Output value for the actuator
int CO;
// Pin for the actuator
int actuator = 3;
// Hysteresis value for the controller
int HYS = 30;

// Pin numbers for the buttons
int UpButton = 6;
int DownButton = 4;
int leftButton = 5;
int rightButton = 2;

// Button state variables
int UpButtonState = LOW;
int DownButtonState = LOW;
int leftButtonState = LOW;
int rightButtonState = LOW;

// Variable to keep track of the current screen
int currentScreen = 0;

void setup() {
  // Set button pins as inputs with pull-up resistors
  pinMode(2, INPUT_PULLUP);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  
  // Start serial communication at 9600 baud
  Serial.begin(9600);
  
  // Initialize the LCD display with 16 columns and 2 rows
  lcd.begin(16, 2);
}

void loop() {
  // Read the state of the buttons
  UpButtonState = digitalRead(UpButton);
  DownButtonState = digitalRead(DownButton);
  rightButtonState = digitalRead(rightButton);
  leftButtonState = digitalRead(leftButton);
  
  // If the left button is pressed, toggle to the next screen
  if (leftButtonState == 0) {
    currentScreen = currentScreen + 1;
    // Wait to prevent errors
    delay(100);
  }
  // If the right button is pressed, toggle to the previous screen
  else if (rightButtonState == 0) {
    currentScreen = currentScreen - 1;
    // Wait to prevent errors
    delay(100);
  }
  
  // Wrap around to the first screen if we've gone too far
  if (currentScreen == 3) {
    currentScreen = 0;
  }
  // Wrap around to the last screen if we've gone too far backwards
  if (currentScreen == -1) {
    currentScreen = 2;
  }
  
  // Clear the LCD display
  lcd.clear();
  
  // Read the sensor value
  sensorValue = analogRead(sensorPin);


// if the sensor reading is below the setpoint minus the hysteresis value, turn on the actuator
// (in this case, a digital output is used, so this is equivalent to setting the output to HIGH)
if (sensorValue < (Setpoint - HYS)) {
  CO = 255;
}

// if the sensor reading is above the setpoint plus the hysteresis value, turn off the actuator
// (in this case, a digital output is used, so this is equivalent to setting the output to LOW)
if (sensorValue > (Setpoint + HYS)) {
  CO = 0;
}

// if the current screen is 0, display the raw sensor value
if (currentScreen == 0) {
  lcd.setCursor(0, 0);
  lcd.print("PV value:");
  lcd.print(sensorValue);
  delay(100);
}

// if the current screen is 1, display the setpoint value and allow the user to adjust it with the up and down buttons
if (currentScreen == 1) {
  lcd.setCursor(0, 0);
  lcd.print("SP value:");
  lcd.print(Setpoint);
  delay(100);

  if (UpButtonState == 0) {
    Setpoint = Setpoint + 10;
  }
  if (DownButtonState == 0) {
    Setpoint = Setpoint - 10;
  }
}

// if the current screen is 2, display the hysteresis value and allow the user to adjust it with the up and down buttons
if (currentScreen == 2) {
  lcd.setCursor(0, 0);
  lcd.print("HYS value:");
  lcd.print(HYS);
  delay(100);

  if (UpButtonState == 0) {
    HYS = HYS + 1;
  }
  if (DownButtonState == 0) {
    HYS = HYS - 1;
  }
}

// write the current actuator value to the output pin (PWM is used, so the value can be anywhere from 0 to 255)
analogWrite(actuator, CO);

// print the sensor reading and setpoint value to the serial monitor
Serial.print(sensorValue);
Serial.print("\t");
Serial.println(Setpoint);
}