/* 
Within this lab we added the proportional gain value, known as KP. this is used to calculate
 the control output (CO) value, which is then converted and sent to the actuator pin. 
 Through running this code, one can learn how to use an Arduino to create a simple proportional
  controller system and gain hands-on experience with programming an embedded system.
  and futher your own understanding of what the effects of proportinal gain on an input
*/
 #include <LiquidCrystal.h>
// Sets integer of pin A0 to A0Value

// assiging pins to the LCD Display 
LiquidCrystal lcd(7, 8, 9, 10, 11, 12);
int sensorPin = A0; // define the analog pin for the light sensor
int sensorValue; // variable to store the sensor reading
int Setpoint = 300; // desired light level
int CO ; // control output
float COPersise; // control output percentage
int actuator = 3; // pin to control the actuator
int HYS = 30; // hysteresis value
int UpButton = 6; // pin for the up button
int DownButton = 4; // pin for the down button
int leftButton = 5; // pin for the left button
int rightButton = 2; // pin for the right button
int UpButtonState = LOW; // variable to store the state of the up button
int DownButtonState = LOW; // variable to store the state of the down button
int leftButtonState = LOW; // variable to store the state of the left button
int rightButtonState = LOW; // variable to store the state of the right button
int currentScreen = 0; // variable to store the current screen
int error =0; // variable to store the error value
float KP = 0.10; // proportional gain




void setup() {
pinMode(2,INPUT_PULLUP);
pinMode(4,INPUT_PULLUP);
pinMode(5,INPUT_PULLUP);
pinMode(6,INPUT_PULLUP);
  Serial.begin(9600); // Initialize serial communication at 9600 baud rate
  lcd.begin(16, 2); 
}

void loop() {

// error calculation 
  error = Setpoint-sensorValue;
  CO =(KP*error);
  // CO limit switches 
  if (CO > 255)
  {
    CO = 255;
  }
 if (CO < 0){
    CO = 0;
 }
 // Reads and stores the button states 
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
  // if the screen count goes higher than desiered return to 0 
 if (currentScreen == 4){
    currentScreen = 0;
  }
  // if the screen count goes negative return it to max value 
 if (currentScreen == -1)
  {
    currentScreen = 3;
  }
  lcd.clear();
  sensorValue = analogRead(sensorPin); // Read the sensor value




if (currentScreen == 0) {  
  lcd.setCursor(0,0);
    // display the "raw value: screen
    lcd.print("PV value:");
    // Displays the actual value
    lcd.print(sensorValue);
delay(100);
  } 
  if (currentScreen == 1) { 
    lcd.setCursor(0,0); 
  lcd.print("SP value:");
  // Displays the actual value  
  lcd.print(Setpoint); 
  delay(100);
  if  (UpButtonState == 0){
  Setpoint = Setpoint +10;
  }
  if  (DownButtonState == 0){
  Setpoint = Setpoint -10;
  } 
  //Set point limit switch
   if  (Setpoint  >= 810){
  Setpoint = 810;
  } 
     if  (Setpoint  <= 0){
  Setpoint = 0;
  } 
  }
if (currentScreen == 2) {  
    lcd.setCursor(0,0);
  lcd.print("Error value:");
  // Displays the actual value  
  lcd.print(error); 
  delay(100);
 }
 if (currentScreen == 3) {  
    lcd.setCursor(0,0);
  lcd.print("KP value:");
  // Displays the actual value  
  lcd.print(KP); 
  delay(100);
 // Adjust KI
  if  (UpButtonState == 0){
  KP = KP +0.01;
  }
  if  (DownButtonState == 0){
  KP = KP -0.01;
  }
     if  (KP  <= 0){
  KP = 0;
  } 
 }
 
 
 COPersise = (CO / 10);
 // write the LED the intenstity of calculated CO 
 analogWrite(actuator,COPersise);
  Serial.print(sensorValue); // Print the sensor reading
    Serial.print("\t");
  Serial.print(CO); // Print the sensor reading
  Serial.print("\t");
  Serial.println(Setpoint); // Print the sensor reading


}
