#include <ESP8266WiFi.h>
 
const char* ssid = "<ssid>";
const char* password = "<wifi_password>";
int red = D6;
int yellow = D5;
int green = D0;
 
int count = 0;
 
bool isBlinking = false;
 
unsigned long previousMillis = 0;
 
int interval = 100;
 
WiFiServer server(80);
 
void setup() {
 Serial.begin(115200);
 delay(10);
 pinMode(red, OUTPUT);
 pinMode(yellow, OUTPUT);
 pinMode(green, OUTPUT);
  digitalWrite(red, LOW);
 digitalWrite(yellow, LOW);
 digitalWrite(green, LOW);
 // Connect to WiFi network
 Serial.println();
 Serial.println();
 Serial.print("Connecting to ");
 Serial.println(ssid);
 
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
   delay(500);
   Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 // Start the server
 server.begin();
 Serial.println("Server started");
 // Print the IP address
 Serial.print("Use this URL : ");
 Serial.print("http://");
 Serial.print(WiFi.localIP());
 Serial.println("/");
}
void loop() {
 if(isBlinking == true){
   unsigned long currentMillis = millis();
     if ((unsigned long)(currentMillis - previousMillis) >= interval) {
       if(count % 2 == 0){
         digitalWrite(red, HIGH);
         digitalWrite(yellow, LOW);
         digitalWrite(green, LOW);
       }
       if(count % 2 == 1){
         digitalWrite(red, LOW);
         digitalWrite(yellow, LOW);
         digitalWrite(green, LOW);
       }
       ++count;
       previousMillis = currentMillis;
    }
 }
 // Check if a client has connected
 WiFiClient client = server.available();
 if (!client) {
   return;
 }
 // Wait until the client sends some data
 Serial.println("new client");
 while(!client.available()){
   delay(1);
 }
 // Read the first line of the request
 String request = client.readStringUntil('\r');
 Serial.println(request);
 client.flush();
 
 // Match the request
 if (request.indexOf("/RED") != -1) {
   digitalWrite(red, HIGH);
   digitalWrite(yellow, LOW);
   digitalWrite(green, LOW);
   isBlinking = false;
 }
 if (request.indexOf("/YELLOW") != -1){
   digitalWrite(red, LOW);
   digitalWrite(yellow, HIGH);
   digitalWrite(green, LOW);
   isBlinking = false;
 }
 if (request.indexOf("/GREEN") != -1){
   digitalWrite(red, LOW);
   digitalWrite(yellow, LOW);
   digitalWrite(green, HIGH);
   isBlinking = false;
 }
 if (request.indexOf("/OFF") != -1){
   digitalWrite(red, LOW);
   digitalWrite(yellow, LOW);
   digitalWrite(green, LOW);
   isBlinking = false;
 }
 if (request.indexOf("/BLINK") != -1){
   count = 0;
   isBlinking = true;
 }
}
