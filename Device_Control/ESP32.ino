#include <Adafruit_Fingerprint.h>
#include <HardwareSerial.h>
#include <ESP32_Servo.h>
#include <WiFi.h>
#include <WiFiMulti.h>
#include <unistd.h>

HardwareSerial mySerial(2);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

//variable
  char msg[30];
  int enroll_flag = 0;
  int pir_flag = 0;
  int pwm;
  int servoPin = 2;
  int angle;
  int m_max=1500;
  uint8_t id;
  uint8_t num = 0;
//variable

WiFiMulti WiFiMulti;
WiFiClient client;


//지문 조회 함수
uint8_t getFingerprintID() {
  int a = 0;
  uint8_t p = finger.getImage();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println("No finger detected");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK success!

  p = finger.image2Tz();
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  p = finger.fingerSearch();
  if (p == FINGERPRINT_OK) {
    Serial.println("Found a print match!");
    a= 1;
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_NOTFOUND) {
    Serial.println("Did not find a match");
    a = 3;
    return a;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  // found a match!
  Serial.print("Found ID #"); Serial.print(finger.fingerID);
  Serial.print(" with confidence of "); Serial.println(finger.confidence);

  return a;
  //return finger.fingerID;
}
//지문 조회 함수



//지문 등록시 각 번호에 저장, 등록 시 마다 저장 번호 증가
uint8_t readnumber(void)
{
  num++;
  if(num==127)
  {
    num=1;
  }
  return num;
}
//지문 등록시 각 번호에 저장, 등록 시 마다 저장 번호 증가



//지문 등록 함수
uint8_t getFingerprintEnroll() {

  int p = -1;
  Serial.print("Waiting for valid finger to enroll as #"); Serial.println(id);
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.println(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(1);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  Serial.println("Remove finger");
  delay(2000);
  p = 0;
  while (p != FINGERPRINT_NOFINGER) {
    p = finger.getImage();
  }
  Serial.print("ID "); Serial.println(id);
  p = -1;
  Serial.println("Place same finger again");
  while (p != FINGERPRINT_OK) {
    p = finger.getImage();
    switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image taken");
      break;
    case FINGERPRINT_NOFINGER:
      Serial.print(".");
      break;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      break;
    case FINGERPRINT_IMAGEFAIL:
      Serial.println("Imaging error");
      break;
    default:
      Serial.println("Unknown error");
      break;
    }
  }

  // OK success!

  p = finger.image2Tz(2);
  switch (p) {
    case FINGERPRINT_OK:
      Serial.println("Image converted");
      break;
    case FINGERPRINT_IMAGEMESS:
      Serial.println("Image too messy");
      return p;
    case FINGERPRINT_PACKETRECIEVEERR:
      Serial.println("Communication error");
      return p;
    case FINGERPRINT_FEATUREFAIL:
      Serial.println("Could not find fingerprint features");
      return p;
    case FINGERPRINT_INVALIDIMAGE:
      Serial.println("Could not find fingerprint features");
      return p;
    default:
      Serial.println("Unknown error");
      return p;
  }

  // OK converted!
  Serial.print("Creating model for #");  Serial.println(id);

  p = finger.createModel();
  if (p == FINGERPRINT_OK) {
    Serial.println("Prints matched!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_ENROLLMISMATCH) {
    Serial.println("Fingerprints did not match");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }

  Serial.print("ID "); Serial.println(id);
  p = finger.storeModel(id);
  if (p == FINGERPRINT_OK) {
    Serial.println("Stored!");
  } else if (p == FINGERPRINT_PACKETRECIEVEERR) {
    Serial.println("Communication error");
    return p;
  } else if (p == FINGERPRINT_BADLOCATION) {
    Serial.println("Could not store in that location");
    return p;
  } else if (p == FINGERPRINT_FLASHERR) {
    Serial.println("Error writing to flash");
    return p;
  } else {
    Serial.println("Unknown error");
    return p;
  }
  return true;
}
//지문 등록 함수



//인터럽트 동작 플래그
void enroll()
{
  enroll_flag=1;
}
void door_open()
{
  pir_flag = 1;
}
//인터럽트 동작 플래그




//도어락용 서보 모터 동작
void servo_play(int servo)
{ 
  for(int i=544;i<m_max;i++){
   digitalWrite(servoPin, HIGH);  
   delayMicroseconds(i);     
   digitalWrite(servoPin, LOW);   
   delayMicroseconds(m_max-i);    
  }
  delay(1000);

  for(int i=m_max;i>544;i--){
   digitalWrite(servoPin, HIGH);  
   delayMicroseconds(i);     
   digitalWrite(servoPin, LOW);   
   delayMicroseconds(m_max-i);    
  }
  delay(1000);
}
//도어락용 서보 모터 동작




//Wifi 연결
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
//Wifi 연결



void setup()
{
  Serial.begin(57600);
  Serial2.begin(115200);
  pinMode(servoPin, OUTPUT);
  //Wifi
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
  connections();
  delay(500);
  //Wifi end
  attachInterrupt(digitalPinToInterrupt(14),enroll,RISING);		//switch
  attachInterrupt(digitalPinToInterrupt(27),door_open,RISING);	//pir
  while (!Serial); // For Yun/Leo/Micro/Zero/...
  delay(100);
  Serial.println("\n\nAdafruit Fingerprint sensor enrollment");
  
  // set the data rate for the sensor serial port
  finger.begin(57600);
  
  if (finger.verifyPassword()) {
  Serial.println("Found fingerprint sensor!");
  } else {
  Serial.println("Did not find fingerprint sensor :(");
  while (1) { delay(1); }
  }
  Serial.println(F("Reading sensor parameters"));
  finger.getParameters();
  Serial.print(F("Status: 0x")); Serial.println(finger.status_reg, HEX);
  Serial.print(F("Sys ID: 0x")); Serial.println(finger.system_id, HEX);
  Serial.print(F("Capacity: ")); Serial.println(finger.capacity);
  Serial.print(F("Security level: ")); Serial.println(finger.security_level);
  Serial.print(F("Device address: ")); Serial.println(finger.device_addr, HEX);
  Serial.print(F("Packet len: ")); Serial.println(finger.packet_len);
  Serial.print(F("Baud rate: ")); Serial.println(finger.baud_rate);

  finger.getTemplateCount();

  if (finger.templateCount == 0) {
    Serial.print("Sensor doesn't contain any fingerprint data. Please run the 'enroll' example.");
  }
  else {
    Serial.println("Waiting for valid finger...");
      Serial.print("Sensor contains "); Serial.print(finger.templateCount); Serial.println(" templates");
  }
  connections();
  
}





void loop()
{
  int Finger_ID_Divide=0;
  int count=0;
  int security=0;
  char *socket_msg;
  
  if(enroll_flag ==1)
  {
    Serial.println("Ready to enroll a fingerprint!");
    id = readnumber();
    if (id == 0) {// ID #0 not allowed, try again!
      return;
    }
    Serial.print("Enrolling ID #");
    Serial.println(id);
    
    while (!  getFingerprintEnroll() );
    enroll_flag=0;
    pir_flag =0;
  }
  if(pir_flag ==1)
  {
    while(1)
    {
      Finger_ID_Divide=getFingerprintID();
      if(Finger_ID_Divide==1)
      {
        Serial.println("OK");
        servo_play(servoPin);
        count=0;
        pir_flag =0;
        enroll_flag=0;
        break;
      }
      if(Finger_ID_Divide==3)
      {
        count++;
        if(count>=3)
        {
          security=2;
          Serial.println("NO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
          sprintf(msg, "ESP:%d", security);
          security=0;
          socket_msg=msg;
          client.println(socket_msg);
          count=0;
          pir_flag =0;
          enroll_flag=0;
          break;
        }
      }
    }
  }
}
 
