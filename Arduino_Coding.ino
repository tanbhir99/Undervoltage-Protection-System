#include <ZMPT101B.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define SENSITIVITY 160.0f
const int vt = 215;
const int relay = 8;
const int vcc_relay = 9;
int zmpt = 7;

ZMPT101B voltageSensor(A0, 50.0);
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display

void setup() {
  Serial.begin(115200);
  lcd.init();         // initialize the lcd
  lcd.backlight();    // Turn on the LCD screen backlight
  pinMode(zmpt,OUTPUT);
  pinMode(relay, OUTPUT);
  pinMode(vcc_relay,OUTPUT);
  digitalWrite(relay,HIGH);
  voltageSensor.setSensitivity(SENSITIVITY);
}

void loop() {
  digitalWrite(zmpt,HIGH);
  digitalWrite(vcc_relay,HIGH);
  float voltage = voltageSensor.getRmsVoltage();
  Serial.print("Voltage is: ");
  Serial.println(voltage);
  if (voltage < vt ) {
    digitalWrite(relay,LOW);
    lcd.setCursor(0, 0);
    lcd.print("Under Voltage ! ");
    lcd.setCursor(1,1);
    lcd.print("Voltage: ");
    lcd.print(voltage);
    Serial.println("Under Voltage Detected !");
  } else {
    digitalWrite(relay,HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Normal Condition.");
    lcd.setCursor(1,1);
    lcd.print("Voltage: ");
    lcd.print(voltage);
  }
  delay(200);
}
