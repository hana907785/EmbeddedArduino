#include <SPI.h>
#include <SoftwareSerial.h>

const int ledPin = 8;
const int buzzerPin = 9;  // 부저의 핀 번호
const int vibrationMotorPin = 10;  // 진동 센서의 핀 번호
const int duration = 1000;  // 동작 지속 시간 (1초)

char buf[100];
volatile byte pos = 0; 
volatile boolean done = false;

SoftwareSerial mySerial(6, 7);

int c;

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  pinMode(vibrationMotorPin, OUTPUT);
  Serial.begin(9600);
  mySerial.begin(9600);
}

int count = 0;

void loop() {
  if (mySerial.available()) {
      c = mySerial.read();
      Serial.print(c);
      if (c != 0)
        count++;
    }
    
  if (c != 0) {
   if (count == 1) {
      for (int i = 0; i < 2; ++i) {  // 3번 반복
        digitalWrite(ledPin, HIGH);
        digitalWrite(buzzerPin, HIGH); 
        digitalWrite(vibrationMotorPin, HIGH);

        delay(duration);
        
        digitalWrite(ledPin, LOW);
        digitalWrite(buzzerPin, LOW);  // 부저를 끄기
        digitalWrite(vibrationMotorPin, LOW);  // 진동 센서가 아닌 진동 센서 정지

        delay(duration);
      }
   }  
  }
}
