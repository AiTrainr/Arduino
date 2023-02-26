#include <OneWire.h>
#include <DallasTemperature.h>
#include <LiquidCrystal.h>

// Pin definitions
#define ONE_WIRE_BUS 2
#define LCD_RS 12
#define LCD_EN 11
#define LCD_D4 5
#define LCD_D5 4
#define LCD_D6 3
#define LCD_D7 6

// Setup the one wire bus and temperature sensor objects
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature tempSensor(&oneWire);

// Setup the LCD object
LiquidCrystal lcd(LCD_RS, LCD_EN, LCD_D4, LCD_D5, LCD_D6, LCD_D7);

void setup() {
  // Initialize the temperature sensor
  tempSensor.begin();

  // Initialize the LCD screen
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Temperature: ");
}

void loop() {
  // Request temperature reading from the sensor
  tempSensor.requestTemperatures();

  // Read the temperature in Fahrenheit
  float tempF = tempSensor.getTempFByIndex(0);

  // Print the temperature to the LCD screen
  lcd.setCursor(0, 1);
  lcd.print(tempF);
  lcd.print(" F");

  // Wait for a second before repeating the loop
  delay(1000);
}