#include<LiquidCrystal_I2C.h>
#include<DS1302.h>
#include<DHT11.h>
#define PIN_DHT A0 //signal pin DHT11
//for RTC(DS1302)
#define CLK 8
#define DATA 9
#define RST 10
char bufferTime[9];
char bufferDate[11];
LiquidCrystal_I2C lcd(0x27,20,4);
DHT11 dht(PIN_DHT);
DS1302 rtc(RST, DATA, CLK);
void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  rtc.writeProtect(false);
  rtc.halt(false);
  Time t(2025, 10, 4, 21, 38, 15, Time::kSaturday);
  rtc.time();
}
void loop() {
  Time now = rtc.time();
  snprintf(bufferTime, 9, "%02d:%02d:%02d", now.hr, now.min, now.sec);
  snprintf(bufferDate, 11, "%04d.%02d.%02d", now.yr, now.mon, now.date);
  lcd.setCursor(0, 0);
  lcd.print("Temperature: ");
  lcd.print(dht.readTemperature());
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Humidity: ");
  lcd.print(dht.readHumidity());
  lcd.print(" %");
  lcd.setCursor(0,2);
  lcd.print(bufferDate);
  lcd.setCursor(0,3);
  lcd.print(bufferTime);
}
