 #include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h> 
#include<SoftwareSerial.h>
#define FIREBASE_HOST "follower-robot-default-rtdb.firebaseio.com"      //-->https://esp8266control-8aa15-default-rtdb.firebaseio.com/
#define FIREBASE_AUTH "tRX1qSLfgi3gT96BcUF2hF3pkcWf3DkeBCWxRM2R"
#define signal1 D1
#define signal2 D2
const char* ssid ="galaxy";
const char* password ="galaxy1234";

String switch2;
String lock;



void setup(){
  pinMode(D1,OUTPUT);
  pinMode(D2,OUTPUT);
  Serial.begin(9600);
  delay(500);
  WiFi.begin(ssid,password);
  Serial.println("");
  Serial.println("Connecting");
  while(WiFi.status()!=WL_CONNECTED){
    Serial.println(".");
    delay(1000);
    }
   Serial.println("Successfully connected to : ");
   Serial.print(ssid);
   Serial.println("");

   Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
   digitalWrite(signal1,LOW);
   digitalWrite(signal2,LOW);
  }
void loop(){
  
  switch2= Firebase.getString("switch2");
  lock= Firebase.getString("lock");

  if(Firebase.failed()){
    Serial.println("Geting  /Value failed : ");
    delay(500);
    return;
    }
    
    if(lock=="closed"){
      digitalWrite(signal2,HIGH);
      Serial.println("Senting lock closed, sig 2 high");
      }
    if(lock=="opened"){
        digitalWrite(signal2,LOW);
        Serial.println("Senting lock openeded, sig 2 low");
        }
      
    if(switch2=="control"){
      digitalWrite(signal1,HIGH);
      Serial.println("Senting control mode , sig 1 high");
      }
      
    if(switch2=="follow"){
      digitalWrite(signal1,LOW);
      Serial.println("Senting follow mode, sig 1 low");
      }
      
   Serial.println(lock);
   Serial.println(switch2);
  }
