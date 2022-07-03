#include <WiFi.h>
#include <WiFiMulti.h>
#include <unistd.h>
#include <ESP32_Servo.h>

static const int servoPin = 27;

Servo servo;

WiFiMulti WiFiMulti;
WiFiClient client;

void setup()
{
  Serial.begin(115200);
  servo.attach(servoPin);
  delay(10);

  // We start by connecting to a WiFi network
  WiFiMulti.addAP("iot0", "iot00000");

  Serial.println();
  Serial.println();
  Serial.print("Waiting for WiFi... ");

  while(WiFiMulti.run() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //connections();
  delay(500);
}

void connections(){
  const uint16_t port = 5000;
  const char * host = "10.10.141.217"; // ip or dns
  
  Serial.print("Connecting to ");
  Serial.println(host);
  
  // Use WiFiClient class to create TCP connections
  //WiFiClient client;
  
  if (!client.connect(host, port)) {
    Serial.println("Connection failed.");
    Serial.println("Waiting 5 seconds before retrying...");
    delay(5000);
    return;
  }
}

void loop()
{
  char a;
  uint8_t data[30];
  connections();
  while(client.connected()){
    if(client.available()>0){
      //Serial.write(client.read());
      a = client.read();
      Serial.print(a);
      if(a=='1')
      {
        servo.write(180);
        delay(1000);
        servo.write(0);
      }
      if(a=='0')
      {
        servo.write(0);
        delay(1000);
      }
    }
    if(Serial.available()>0){
      client.write("start"); 
    }
  }
  Serial.println(" ");
  client.stop();
  delay(1000);
}
