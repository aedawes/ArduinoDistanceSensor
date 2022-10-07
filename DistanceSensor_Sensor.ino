#include <ESP8266WiFi.h>

const char* ssid = "ImNotAWitchImYourWifi";
const char* password = "Inconceivable963!";

WiFiClient client;

const int trigPin = D1;
const int echoPin = D2;

long duration;
String send = "-";

float distanceCm;
float distanceInch;

#define SOUND_SPEED 0.034
#define CM_TO_INCH 0.393701 
void setup()
{
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input
  
  WiFi.begin(ssid, password);
  Serial.begin(115200); // Starts the serial communication
  
  while (WiFi.status() != WL_CONNECTED) {
 
    delay(1000);
    Serial.print("Connecting..");
 
  }

  Serial.print("Connected!");
}

void loop(){

  // Clears the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echoPin, HIGH);
  // Calculate the distance
  distanceCm = duration * SOUND_SPEED/2;

  if(distanceCm > 40){
    send = "/OFF";
  }
  if(distanceCm > 30 && distanceCm <= 40){
    send = "/GREEN";
  }
  if(distanceCm > 20 && distanceCm <= 30){
    send = "/YELLOW";
  }
  if(distanceCm > 10 && distanceCm <= 20){
    send = "/RED";
  }
  if(distanceCm <= 10){
    send = "/BLINK";
  }

  Serial.print(send);
  delay(500);

  if(client.connect("192.168.1.139", 80)){
    client.print(String("GET" ) + send + " HTTP/1.1\r\n" + "Host: " + "192.168.1.139"  + "\r\n" + "Connection: keep-alive\r\n\r\n");
  }
}
