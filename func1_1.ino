#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);
byte command;
const int LED1 = 12;
const int LED2 = 13;

void setup() {
  mySerial.begin(9600);
  Serial.begin(9600);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT); 
}
void loop() {

  if (Serial.available()) {
      command = Serial.read(); //명령 수신
       if (command == 'S') { // Start 명령 수신 시
      delay(100); // 임의의 지연 시간

      // 두 번째 아두이노로부터 초음파 센서 값 수신
       if (Serial.available()) {
        String Values = Serial.readStringUntil('\n');
        int distance1 = Values.substring(0, Values.indexOf(',')).toInt();
        int distance2 = Values.substring(Values.indexOf(',') + 1).toInt();

        // LED 제어 
        if (distance1 <= 30) {
          digitalWrite(LED1, HIGH); 
        } else {
          digitalWrite(LED1, LOW); 
        }

        if (distance2 <= 30) {
          digitalWrite(LED2, HIGH); 
        } else {
          digitalWrite(LED2, LOW); 
        }
      }
    } else if (command == 'E') { // Stop 명령 수신
      digitalWrite(LED1, LOW); 
      digitalWrite(LED2, LOW); 
    }
    Serial.print('\n');  //mySerial
    delay(500);
  }
}
