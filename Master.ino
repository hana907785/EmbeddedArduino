#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
#include <SPI.h>
const int S1 = 8;
const int S2 = 9;
const int ledPins[] = {2, 3, 4, 5, 6};

//정류장 인덱스
int spaces[] = {11, 12, 21, 22, 31};
int arrive = 0;
byte s;
//현재 버스 인덱스
int currentBusIndex = 0;
int currentStop = spaces[currentBusIndex];
int stop;
void setup() {
  mySerial.begin(9600);
    SPI.begin();
    pinMode(S1, OUTPUT);
    pinMode(S2, OUTPUT);
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    SPI.setClockDivider(SPI_CLOCK_DIV16);
    for (int i = 0; i < 5; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
    Serial.begin(9600);
}

byte transferAndWait(const byte what) {
  byte a = SPI.transfer(what);
  delayMicroseconds(20);
  return a;
}

void loop() {
  digitalWrite(S1, LOW);

  transferAndWait('s');
  transferAndWait(0);
  s = transferAndWait(0);
  digitalWrite(S1, HIGH);
  Serial.println(s);
  
  
  if (Departure()) {
    // 다음으로 이동
    moveStop();
    Serial.println(currentBusIndex);
    //현재 LED다 끔
    turnOffAllLEDs();

   //현재 정류장 LED킴
    digitalWrite(ledPins[currentBusIndex], HIGH);
  }
  Arrive();
  mySerial.write(arrive);
  delay(1000);
}
void Arrive() {
  if (s - currentBusIndex == 1) {
    arrive = 1;
  }
  else if(s - currentBusIndex != 1) {
    arrive = 0;
  }
}
void moveStop() {
    if (currentBusIndex == 4) {
        while (currentBusIndex > 0) {
            currentBusIndex--;
        }
    } else {
        currentBusIndex++;
    }
}

//"출발"입력 감지
bool Departure() {
  if (Serial.available() > 0) {
    String message = Serial.readStringUntil('\n');
    return message.equals("ㅁ");
  }
  return false;
}

//모든 LED끔
void turnOffAllLEDs() {
  for (int i = 0; i < 5; i++) {
    digitalWrite(ledPins[i], LOW);
  }
}
