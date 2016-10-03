#include <ESP8266WiFi.h>
 
const char* ssid     = "";
const char* password = "";
const char* host = "wifitest.adafruit.com";

int light = 0;
int buttonPin = 15;
int outputPin = 12;

int previousState = 1;

unsigned long lastPressed = 0;
int timeBetweenPresses = 3 * 1000;

void setup() {
  pinMode(light, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(outputPin, OUTPUT);
  
  Serial.begin(115200);
  delay(100);

   WiFi.begin(ssid, password);
    
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
   }

   digitalWrite(light, LOW);
   delay(500);
   digitalWrite(light, HIGH);
   delay(500);
   digitalWrite(light, LOW);
   delay(500);
   digitalWrite(light, HIGH);
   delay(500);

}

void loop() {

  digitalWrite(outputPin, HIGH);
  
  if(digitalRead(buttonPin) == 0 && previousState == 1 && millis() - lastPressed > timeBetweenPresses){
    digitalWrite(light, LOW);
    Serial.println("BUTTON DOWN");
    lastPressed = millis();
    launch();
  }

  if(millis() - lastPressed > timeBetweenPresses){
    digitalWrite(light, HIGH);
  }
  
  previousState = digitalRead(buttonPin);
 
}

void launch(){
  
}
}
