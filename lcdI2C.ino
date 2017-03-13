// theiotlife.com
// Charlie Nguyen
#include <Wire.h>
#include <LiquidCrystal_PCF8574.h>

//Set I2C address of PCF8574 here
int PCF8574_Address = 0; //Mine 0x3f
LiquidCrystal_PCF8574 lcd(PCF8574_Address);
String scrollDirection = "none";

void setup() {
  int error;
  //Setting up Serial Connection for Debugging -
  //If there is something wrong with the LCD then open up serial monitor to see
  Serial.begin(115200);

  while (! Serial); //Wait until serial connection is established
  //Checks if address has been set
  if(PCF8574_Address == 0){
  	while(true){
  		Serial.println("You have not set an address for the I2C backpack! Please set it above!");
  		delay(5000);
  	}

  }

  Serial.println("LCD Starting up!");

  //Checks and establishes connection with PCF8574
  Wire.begin();
  Wire.beginTransmission(PCF8574_Address);
  error = Wire.endTransmission();

  //Takes care of any errors that occur with endTransmission
  if (error == 0) {
    Serial.println("LCD connected! Initializing now..");
  } else if (error == 2) {
  	Serial.print("Error: ");
  	Serial.print(error);
    Serial.println(": LCD not found.");
    Serial.println("Check if the address to the PCF8574 is correct with an I2CScanner");
  }
  else {
  	Serial.print("Error: ");
  	Serial.print(error);
  	Serial.println("Please refer to 'https://www.arduino.cc/en/Reference/WireEndTransmission' for error details");
  }

  lcd.begin(16, 2);
}

void loop() {
    lcd.setBacklight(255);
    lcd.home();
    lcd.clear();
    lcd.setCursor(1, 0); //Set Cursor Position 1, Line 1
    lcd.print("The LCD Works!");
    lcd.setCursor(1, 1); //Set Cursor Position 1, Line 2
    lcd.print("TheIoTLife.com");

    if (scrollDirection == "none"){
    	scrollDirection = "right";
    	lcd.scrollDisplayRight();
    	delay(1500);
    }
    else if(scrollDirection == "right"){
    	scrollDirection = "left";
    	lcd.scrollDisplayLeft();
    	delay(1500);
    }
    else if(scrollDirection == "left"){
    	scrollDirection = "right";
    	lcd.scrollDisplayRight();
    	delay(1500);
    }

}
