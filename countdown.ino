#include <NTPClient.h>
#include <ESP8266WiFi.h>
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <LiquidCrystal.h>
//LCD pins. Adjust to your requirements
LiquidCrystal lcd(2, 14, 16, 5, 4, 0);
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "time.google.com", 3600, 60000);
const char* ssid = "SSID";
const char* password = "password";
long timeRemaining = 1;
long target = 1545609599;
void setup() {
  lcd.begin(16, 2);
  Serial.begin(115200);
  Serial.println("Booting");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
   Serial.println("Connection Failed! Rebooting...");
   delay(5000);
   ESP.restart();
}
}

void loop() {
  if (timeRemaining > 0) {
 lcd.clear();
timeClient.update();
timeRemaining = target - timeClient.getEpochTime();
lcd.setCursor(0, 0);
int days = floor(timeRemaining / 86400);
int hours = floor(timeRemaining % 86400 / 3600);
int minutes = floor(timeRemaining % 3600 / 60);
int seconds = timeRemaining % 60;
int percentage = target / timeRemaining *100;
lcd.print(days);
lcd.print("-Day ");
lcd.print(hours);
lcd.print("-Hr ");
lcd.setCursor(0, 1);
lcd.print(minutes);
lcd.print("-Min ");
lcd.print(seconds);
lcd.print("-Sec ");
 }

 else {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("TIME");
  lcd.setCursor(0, 1);
  lcd.print("REACHED");
 }

 delay(1000);
}
