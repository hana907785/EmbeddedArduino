#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11);

int LED[2] = {12, 13};
char command;
char readCom;

void setup()
{
  mySerial.begin(9600);
  Serial.begin(9600);
  for(int i = 0;i < 2;i++)
      pinMode(LED[i], OUTPUT);
}

void reception(char r) {
  switch (readCom){
    case 'n':
      digitalWrite(led[0], LOW);
    break;
    case 'y':
      digitalWrite(led[0], HIGH);
    break;
    case 'N':
      digitalWrite(led[1], LOW);
    break;
    case 'Y':
      digitalWrite(led[1], HIGH);
    break;
  }
}

void loop() {
  if(Serial.available()){
    command = Serial.read();
    mySerial.write(c);
  }
  if(mySerial.available()){
    readCom = mySerial.read();
    reception(r);
   }
}
