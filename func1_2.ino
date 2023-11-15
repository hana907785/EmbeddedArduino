#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

const int pinTrig1 = 2;
const int pinEcho1 = 3; 

const int pinTrig2 = 6;
const int pinEcho2 = 7; 
long duration1, distance1, duration2, distance2;



void setup() {
  mySerial.begin(9600); // 시리얼 통신 시작
  Serial.begin(9600); 
  
  pinMode(pinTrig1, OUTPUT);
  pinMode(pinEcho1, INPUT);
  
  pinMode(pinTrig2, OUTPUT);
  pinMode(pinEcho2, INPUT);
}

void loop() {

  // 초음파센서1 측정
  digitalWrite(pinTrig1, LOW); delayMicroseconds(2);
  digitalWrite(pinTrig1, HIGH);delayMicroseconds(10);
  digitalWrite(pinTrig1, LOW);
  
  duration1 = pulseIn(pinEcho1, HIGH);
  distance1 = duration1 * 0.034 / 2;

  // 초음파센서2 측정
  digitalWrite(pinTrig2, LOW);delayMicroseconds(2);
  digitalWrite(pinTrig2, HIGH);delayMicroseconds(10);
  digitalWrite(pinTrig2, LOW);
  
  duration2 = pulseIn(pinEcho2, HIGH);
  distance2 = duration2 * 0.034 / 2;

  // 결과를 첫 번째 아두이노로 전송
  Serial.print(distance1);
  Serial.print(',');
  Serial.println(distance2);

  delay(500);
}
