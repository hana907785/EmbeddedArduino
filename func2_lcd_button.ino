#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 20, 4);

const int buttonPinK2 = 2;  // K2 버튼 핀 번호
const int buttonPinK3 = 3;  // K3 버튼 핀 번호
const int buttonPinK6 = 4;  // K6 버튼 핀 번호
const int buttonPinK7 = 5;  // K7 버튼 핀 번호

int digit1 = 0; // 첫 번째 자리의 숫자
int digit2 = 0; // 두 번째 자리의 숫자
bool oddPress = true; // 홀수 번째 버튼 눌림 여부를 나타내는 변수
int spaces[] = {11, 12, 21, 22, 31};

volatile byte command = 0;
volatile byte data = 0;

byte a[8] = { //이
  B00001,
  B01001,
  B10101,
  B10101,
  B10101,
  B10101,
  B01001,
  B00001
};
byte b[8] = { //번
  B00001,
  B10101,
  B11111,
  B10101,
  B11101,
  B00001,
  B01000,
  B01111,
};
byte c[8] = { //역
  B00001,
  B01011,
  B10101,
  B10111,
  B01001,
  B00000,
  B01111,
  B00001,
};
byte d[8] = { //은
  B00000,
  B00000,
  B00000,
  B11111,
  B00000,
  B00000,
  B00000,
  B00000,
};
byte e[8] = {  //ㅇ
  B00000,
  B00010,
  B00101,
  B00101,
  B00101,
  B00101,
  B00010,
  B00000
};
byte f[8] = {  //ㅖ
  B01010,
  B01010,
  B11010,
  B01010,
  B11010,
  B01010,
  B01010,
  B01010
};
byte g[8] = {  //약
  B01010,
  B10111,
  B10110,
  B10111,
  B01010,
  B00000,
  B11111,
  B00001
};
byte h[8] = {  //0
  B00000,
  B00110,
  B01001,
  B01001,
  B01001,
  B01001,
  B00110,
  B00000
};

void setup() {
  Serial.begin(9600);
  pinMode(buttonPinK2, INPUT);
  pinMode(buttonPinK3, INPUT);
  pinMode(buttonPinK6, INPUT);
  pinMode(buttonPinK7, INPUT);

  lcd.init();
  lcd.backlight();
  
  lcd.createChar(0, a);
  lcd.createChar(1, b);
  lcd.createChar(2, c);
  lcd.createChar(3, d);
  lcd.createChar(4, e);
  lcd.createChar(5, f);
  lcd.createChar(6, g);
  lcd.createChar(7, h);
  lcd.begin(16, 2);
/*
  lcd.setCursor(0, 0); lcd.write((byte)0);  //이
  lcd.setCursor(1, 0); lcd.write((byte)1);  //번
  lcd.setCursor(2, 0); lcd.write((byte)2);  //역
  lcd.setCursor(3, 0); lcd.write((byte)3);  //은

  lcd.setCursor(5, 0); lcd.print(11); //이번역 번호 표시
  lcd.setCursor(7, 0); lcd.write((byte)1);  //번
*/
  //예약된 역 번호 표시
  for (int i = 1; i < 19; i++) {
    lcd.setCursor(i, 0);
    lcd.write((byte)3);
  }
  for (int i = 1; i < 19; i++) {
    lcd.setCursor(i, 2);
    lcd.write((byte)3);
  }
  
  lcd.setCursor(8, 1); lcd.write((byte)1); //번

  lcd.setCursor(10, 1); lcd.write((byte)4); //ㅇ
  lcd.setCursor(11, 1); lcd.write((byte)5); //ㅖ
  lcd.setCursor(12, 1); lcd.write((byte)6); //약
  lcd.setCursor(13, 1); lcd.write((byte)7); //0

  pinMode(MISO, OUTPUT);
  SPCR |= _BV(SPE);
  SPCR &= ~_BV(MSTR);
  SPCR |= _BV(SPIE);
}

ISR(SPI_STC_vect) {
  byte c = SPDR;
  switch (command) {
    case 0:
    command = c;
    SPDR = 0; 
    break;
 
  case 's':
    SPDR = data;
    break; 
  }
}

void loop() {
  if (digitalRead(buttonPinK2) == HIGH) { //1번 버튼
    if (oddPress) {
      digit1 = 1;
      Serial.print(digit1);
      delay(200);
    } else {
      digit2 = 1;
      Serial.print(digit2);
      delay(200);
    }
    oddPress = !oddPress;
  } else if (digitalRead(buttonPinK3) == HIGH) {  //2번 버튼
    if (oddPress) {
      digit1 = 2;
      Serial.print(digit1);
      delay(200);
    } else {
      digit2 = 2;
      Serial.print(digit2);
      delay(200);
    }
    oddPress = !oddPress;
  } else if (digitalRead(buttonPinK6) == HIGH) {  //3번 버튼
    if (oddPress) {
      digit1 = 3;
      Serial.print(digit1);
      delay(200);
    } else {
      digit2 = 3;
      Serial.print(digit2);
      delay(200);
    }
    oddPress = !oddPress;
  }

  if (digitalRead(buttonPinK7) == HIGH) { //확인 버튼, 마지막 입력 숫자 2개 출력
    if (digit1 != 0 && digit2 != 0 && oddPress == true) {
      lcd.setCursor(6, 1); lcd.print(digit1);
      lcd.setCursor(7, 1); lcd.print(digit2);
      delay(200);
    } else if (digit1 != 0 && digit2 != 0 && oddPress == false) {
      lcd.setCursor(6, 1); lcd.print(digit1);
      lcd.setCursor(7, 1); lcd.print(digit2);
      delay(200);
    }
    for (int i = 0; i < 6; i++) {
      if (digit1*10+digit2 == spaces[i]) {
        data = (byte)i;
      }
    }
    if (digitalRead(SS) == HIGH)
        command = 0;
    digit1 = 0; digit2 = 0; oddPress = true;
  }
}
