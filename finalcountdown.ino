#include <ESP8266WiFi.h>
 
const char* ssid     = "buttonwifi";
const char* password = "deploy1a";
const char* host = "";

int light = 0;
int buttonPin = 15;
int outputPin = 12;

int onLight = 13;
int connectedLight = 16;
int activatedLight = 2;

int previousState = 1;

unsigned long lastPressed = 0;
int timeBetweenPresses = 5 * 1000;

void setup() {
  pinMode(light, OUTPUT);
  pinMode(buttonPin, INPUT);
  pinMode(outputPin, OUTPUT);

  pinMode(onLight, OUTPUT);
  pinMode(connectedLight, OUTPUT);
  pinMode(activatedLight, OUTPUT);

  digitalWrite(onLight, HIGH);
  
  Serial.begin(115200);
  delay(100);

   WiFi.begin(ssid, password);
    
   while (WiFi.status() != WL_CONNECTED) {
     delay(500);
     Serial.print('.');
   }
   
   Serial.println("Connected to WiFi");
   digitalWrite(connectedLight, HIGH);

}

void loop() {

  digitalWrite(outputPin, HIGH);
  
  if(digitalRead(buttonPin) == 0 && previousState == 1 && millis() - lastPressed > timeBetweenPresses){
    digitalWrite(light, LOW);
    Serial.println("BUTTON DOWN");
    digitalWrite(activatedLight, HIGH);
    lastPressed = millis();
    launch();
  }

  if(millis() - lastPressed > timeBetweenPresses){
    digitalWrite(activatedLight, LOW);
  }
  
  previousState = digitalRead(buttonPin);
 
}

void launch(){

  delay(500);
  
  Serial.print("connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  WiFiClient client;
  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
  Serial.println("connection failed");
  return;
  }
  
  // We now create a URI for the request
  String url = "/";
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
             "Host: " + host + "\r\n" + 
             "Connection: close\r\n\r\n");
  delay(500);
  
  // Read all the lines of the reply from server and print them to Serial
  while(client.available()){
  String line = client.readStringUntil('\r');
  Serial.print(line);
  }
  
  Serial.println();
  Serial.println("closing connection");
  
}
