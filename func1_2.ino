#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int pinTrig[2] = {2, 6};
int pinEcho[2] = {3, 7};
char command;
int distance[2] = {0,0};
int TData;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0;i<2;i++)
    pinMode(pinTrig[i], OUTPUT);
  for(int i = 0;i<2;i++)
    pinMode(pinEcho[i], INPUT);
}


void loop() {
  if (mySerial.available()){  //mySerial
    command = mySerial.read();  //mySerial
    while (command =='g'){ //터치스크린 대신 일단 시리얼 모니터
      for (int i = 0; i<2;i++){ //초음파 센서 측정
        digitalWrite(pinTrig[i], LOW); delayMicroseconds(2);
        digitalWrite(pinTrig[i], HIGH); delayMicroseconds(10);
        digitalWrite(pinTrig[i], LOW);

        TData = pulseIn(pinEcho[i], HIGH);

        distance[i] = TData/58.82;

        if ( i == 0 ) { //첫번째 초음파센서
          if (distance[0] < 20) {
            mySerial.write('n');

          }
          else if (distance[0] >= 20){
            mySerial.write('y');
          }
        }

        else if ( i == 1 ) { //두번째 초음파센서
          if (L[1] < 20) {
            mySerial.write('N');
          }
          else if (distance[1] >= 20){
            mySerial.write('Y');
          }
        }
     }
     Serial.print('\n');

     if (command != 'e'){
      break;
     }
     delay(1000);
     }
   }
}
