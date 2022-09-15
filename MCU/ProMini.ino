#include <dht.h>
#include "WiFiEsp.h"
#include "SoftwareSerial.h"

dht DHT;
#define DHT11_PIN 5
//variable
  int Led1=0;
  int Led2=0;
  int Led3=0;
  int Gas_Motor=0;
  
  int PreLed1=0;
  int PreLed2=0;
  int PreLed3=0;
  int PreServo=0;
  
  int servoPin = 3;
  int Led1_Pin = 9;
  int Led2_Pin = 10;
  int Led3_Pin = 11;
  
  int hum;
  int temp;
  
  char msg[30];
  
  char ssid[] = "iot5";            // your network SSID (name)
  char pass[] = "iot50000";        // your network password
  int status = WL_IDLE_STATUS;     // the Wifi radio's status
  int m_max = 1500;
  
  char server[] = "10.10.141.217";
//variable

WiFiEspClient client;

#ifndef HAVE_HWSERIAL1
SoftwareSerial Serial1(6, 7); // RX, TX
#endif


//Wifi 정보 출력
void printWifiStatus()
{
  // print the SSID of the network you're attached to
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength
  long rssi = WiFi.RSSI();
  Serial.print("Signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
//Wifi 정보 출력


// 가스밸브 서보모터 제어
void servo_play(int servo)
{
  if(servo == 1)
  {
    for(int i=544;i<m_max;i++){
      digitalWrite(servoPin, HIGH);  
      delayMicroseconds(i);     
      digitalWrite(servoPin, LOW);   
      delayMicroseconds(m_max-i);    
    }
    delay(100);
  }
  if(servo == 0)
  {
    
    for(int i=m_max;i>544;i--){
      digitalWrite(servoPin, HIGH);  
      delayMicroseconds(i);     
      digitalWrite(servoPin, LOW);   
      delayMicroseconds(m_max-i);     
    }
    delay(100);
  }
}
// 가스밸브 서보모터 제어


//각 led analog제어
void led_play1(int led)
{
  analogWrite(Led1_Pin, led);
  delay(10);
}
void led_play2(int led)
{
  analogWrite(Led2_Pin, led);
  delay(10);
}
void led_play3(int led)
{
  analogWrite(Led3_Pin, led);
  delay(10);
}
//각 led analog제어



void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  pinMode(Led1_Pin, OUTPUT);
  pinMode(Led2_Pin, OUTPUT);
  pinMode(Led3_Pin, OUTPUT);
  pinMode(servoPin, OUTPUT);

  WiFi.init(&Serial1);
  if (WiFi.status() == WL_NO_SHIELD) {
    Serial.println("WiFi shield not present");
    // don't continue
    while (true);
  }
  // attempt to connect to WiFi network
  while ( status != WL_CONNECTED) {
    Serial.print("Attempting to connect to WPA SSID: ");
    Serial.println(ssid);
    // Connect to WPA/WPA2 network
    status = WiFi.begin(ssid, pass);
  }
  printWifiStatus();

  Serial.println();
  Serial.println("Starting connection to server...");
  // if you get a connection, report back via serial
  if (client.connect(server, 5000)) {
    Serial.println("Connected to server");
  }
}



void loop() {
//variable
  char word_msg;  //Receive
  char *sensing_msg;
  char *result;
  char *parsing[7];
  char msg_server[200]="";
  int j=0;
  String str="";
//variable

//DHT 온습도 센서 제어
  DHT.read11(DHT11_PIN);
  hum=DHT.humidity;
  temp=DHT.temperature;

  Serial.print("humidity : ");
  Serial.print(hum);
  Serial.print("%  Temperature : ");
  Serial.print(temp);
  Serial.println("°C");
//DHT 온습도 센서 제어

//수신부 파싱기능 구현을 위한 구분자를 삽입한 문자열 생성
  sprintf(msg, "PRO:%d:%d", temp,hum);
  sensing_msg = msg;
//수신부 파싱기능 구현을 위한 구분자를 삽입한 문자열 생성
  
  client.print(sensing_msg); //문자열 TCP 송신



//문자 TCP 수신
  while(client.available()){
    word_msg = client.read(); //문자 수신
    str+=word_msg; //문자열 제작
  }
  if(!str.equals(""))
  {
    str.toCharArray(msg_server,200);
    result = strtok(msg_server, "/"); //파싱 기능 구현
    while(result != NULL)
    {
      parsing[j++] = result;
      result = strtok(NULL, "/");
    }
    j=0;
    Gas_Motor=atoi(parsing[3]); //가스 모터 제어값
    Led1 = atoi(parsing[4]);    //Led1 제어값
    Led2 = atoi(parsing[5]);    //Led2 제어값
    Led3 = atoi(parsing[6]);    //Led3 제어값
  }
  delay(100);

  Serial.print("Gas : ");
  Serial.println(Gas_Motor);
  Serial.print("Led1 : ");
  Serial.println(Led1);
  Serial.print("Led2 : ");
  Serial.println(Led2);
  Serial.print("Led3 : ");
  Serial.println(Led3);
//문자 TCP 수신



//기존에 저장된 값과 새로 받은 값이 다를 경우 서보모터와 LED 동작 
  if(Gas_Motor!=PreServo)
  {
    PreServo = Gas_Motor;
    servo_play(PreServo);
  }
  if(Led1!=PreLed1)
  {
    PreLed1 = Led1;
    led_play1(PreLed1);
  }
  if(Led2!=PreLed2)
  {
    PreLed2 = Led2;
    led_play2(PreLed2);
  }
  if(Led3!=PreLed3)
  {
    PreLed3 = Led3;
    led_play3(PreLed3);
  }
//동작 끝


  if (!client.connected()) {
    Serial.println();
    Serial.println("Disconnecting from server...");
    client.stop();

    // do nothing forevermore
    while (true);
  }
  delay(1000);
}
