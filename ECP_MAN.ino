/*
This is an Arduino sketch that uses a LDR and a potentiometer to control the brightness of an actuator
 our a LED. The potentiometer sets the desired brightness level (SP), which is set to the value (CO)
  using the map function. The light sensor (PV) measures the actual brightness level, 

  The purpose of this lab was to become familiar with the LDR along with becoming
   aware of our max and minimum PV values we can receive from our LDR

*/
#include <LiquidCrystal.h>
// Sets integer of pin A0 to A0Value

// assiging pins to the LCD Display 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int sensorPin = A0; // Define the analog pin for the light sensor
int SetPoint ; // Variable to Set SP
int PetPin = A1; // Define the analog pin for the petentiometer 
int PV; 
int CO = 0;
int actuator = 3;

void setup() {
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16, 2); 
}

void loop() {
  CO = map (SetPoint, 0, 1023, 0, 255);
  lcd.clear();
  PV = analogRead(sensorPin); // Read the sensor value
  SetPoint = analogRead(PetPin); // Read the sensor value
  analogWrite(actuator, CO);
 
  Serial.print("PV: "); // Print a message to the serial monitor
  Serial.println(PV); // Print the sensor reading
 Serial.print("CO: "); // Print a message to the serial monitor
  Serial.println(CO); // Print the sensor reading
  Serial.print("Input value: "); 
  Serial.println(SetPoint); // Print the sensor reading
 lcd.setCursor(0,0);
//print "raw value:" on LCD
lcd.print("pv:");
//print actual value of A0value on LCD
lcd.print(PV);
 lcd.setCursor(0,1);
 lcd.print("Input value:");
//print actual value of A0value on LCD
lcd.print(SetPoint);

  delay(200); // Wait for 1 second before reading the sensor again
}
//