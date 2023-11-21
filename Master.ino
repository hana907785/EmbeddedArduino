#include <SoftwareSerial.h>
SoftwareSerial mySerial(8, 9);
#include <SPI.h>
const int S1 = 10;
const int S2 = 9;
const int ledPins[] = {2, 3, 4, 5, 6};

//정류장 인덱스
int spaces[] = {11, 12, 13, 21, 22};


byte s;
//현재 버스 인덱스
int currentBusIndex = 0;
boolean arrive;
int currentStop = spaces[currentBusIndex];

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

int old = 99; // 걍 쓰레기값

void loop() {
  digitalWrite(S1, LOW);

  transferAndWait('s');
  transferAndWait(0);
  s = transferAndWait(0);
  digitalWrite(S1, HIGH);
  Serial.println(s);
  Arrive();

  /* 버튼에서 값을 연속으로 보내서 서진이한테도 무한으로 보내는 문제 발생
   *  이 문제를 해결하기 위해 전에 받았던 값을 저장하고 다음에 받은 값을 비교하여 무한으로 신호를 보내는 문제를 해걀하려고 함
   *  통신 spi로 바꿔도 될 것 같음 근데 아직 거기까진 생각을 안 함
   */
  if (old != s ) {
    currentBusIndex = 0;
    mySerial.write(arrive);
    /*digitalWrite(S2, LOW);
    SPI.transfer(arrive);
    digitalWrite(S2, HIGH);*/
  }
  old = s;

  
  if (Departure()) {
    // 다음으로 이동
    moveStop();

    //현재 LED다 끔
    turnOffAllLEDs();

   //현재 정류장 LED킴
    digitalWrite(ledPins[currentBusIndex], HIGH);
  }
  
  digitalWrite(S1, LOW);
  SPI.transfer(currentBusIndex);
  digitalWrite(S1, HIGH);

  delay(1000);
}

void Arrive() {
  if (currentBusIndex - s == 1) {
    arrive = 1;
  }
  else {
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
