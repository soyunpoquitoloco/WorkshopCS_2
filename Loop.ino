#include "DHT.h"
#define DHTPIN 1
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
int ledPin = 5;
int t = 500;
int trig = 2;
int echo = 3;
long lecture_echo;
long cm;

#include <WiFi.h>
#include <WebSocketsServer.h>

const char* ssid = "PoleDeVinci_IFT";
const char* password = "*c.r4UV@VfPn_0";


WebSocketsServer webSocket = WebSocketsServer(80);

void onWebSocketEvent(uint8_t num, WStype_t type, uint8_t * payload, size_t length) {
  // Handle WebSocket events here
  if (type == WStype_TEXT) {
      // Message reçu
      String message = (char *)payload;
      // Traitement du message
      Serial.println("Message reçu : " + message);

      // Send a response back to the client
      webSocket.sendTXT(num, "Message well received !");
      if(message.charAt(0) == 'f'){ 
        // Extract the substring from index 1 to the end
      String messagesub = message.substring(1);
        // Convert the substring to an integer
      t = messagesub.toInt();
      }
    }
  
}

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(ledPin,OUTPUT);
  pinMode(trig, OUTPUT);
digitalWrite(trig, LOW);
pinMode(echo, INPUT);
Serial.println ("Bienvenue sur les tutoriels d'IHM 3D");

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println("Starting WebSocket server...");
  webSocket.begin();
  webSocket.onEvent(onWebSocketEvent);
  Serial.println("Ready");
}

void loop() {
  //Serial.println("Temperature = " + String(dht.readTemperature())+" °C");
  //Serial.println("Humidite = " + String(dht.readHumidity())+" %");
  webSocket.broadcastTXT("t" + String(dht.readTemperature())+" °C");
  webSocket.broadcastTXT("h" + String(dht.readHumidity())+" %");
  digitalWrite(ledPin, HIGH);
  delay(t);
  digitalWrite(ledPin, LOW);
  delay(t);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);
  lecture_echo = pulseIn(echo,HIGH);
  cm = lecture_echo /58;
  webSocket.broadcastTXT("d"+String(cm)+"cm");
  webSocket.broadcastTXT("f"+String(t)+"Hz");

  webSocket.loop();

}