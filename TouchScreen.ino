// tft lcd
#include <SPFD5408_Adafruit_GFX.h>
#include <SPFD5408TFTLCDLib.h> 
#include <SPFD5408_TouchScreen.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define YP A1  // Must be an analog pin, use "An" notation!
#define XM A2  // Must be an analog pin, use "An" notation!
#define YM 7   // Can be a digital pin
#define XP 6   // Can be a digital pin

#define TS_MINX 150
#define TS_MINY 120
#define TS_MAXX 920
#define TS_MAXY 940

#define SENSIBILITY 300
#define MINPRESSURE 10
#define MAXPRESSURE 1000

#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define BLACK   0x0000
#define BLUE    0x001F
#define RED     0xF800
#define GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF

#define BOXSIZE 95
#define PENRADIUS 3

SPFD5408TFTLCDLib tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);
TouchScreen ts = TouchScreen(XP, YP, XM, YM, SENSIBILITY);


void setup() {
  Serial.begin(9600);
  //tft lcd
  tft.reset();
  uint16_t identifier = tft.readID();
  tft.begin(0x9341);
  tft.setRotation(1); //가로모드설정
  tft.fillScreen(WHITE); //배경->흰색으로 설정
  tft.fillRect(0, 0, 400, 40, BLACK);

  
  tft.setTextSize(3);
  tft.setCursor(80, 15);
  tft.setTextColor(GREEN);
  tft.print("BUS STATE");
  
  tft.setTextSize(3);
  tft.setCursor(20, 80);
  tft.setTextColor(BLACK);
  tft.print("Bus : Number 97");

  tft.drawLine(0, 140, 400, 140, BLACK);

  tft.setTextSize(3);
  tft.setCursor(20, 180);
  tft.setTextColor(BLACK);
  tft.print("Bus : Number 111");

  waitOneTouch();
  pinMode(13, OUTPUT);
}



void loop() {
  // tft lcd
  digitalWrite(13, HIGH);
  TSPoint p = ts.getPoint();
  digitalWrite(13, LOW);
  pinMode(YP, OUTPUT); // restore shared pins
  pinMode(XM, OUTPUT);

  if (p.z > MINPRESSURE && p.z < MAXPRESSURE) {
    //좌표확인용 이건 나중에 할 거임
    Serial.print("X = "); Serial.print(p.x);
    Serial.print("\tY = "); Serial.print(p.y);
    Serial.print("\tPressure = "); Serial.println(p.z);

    p.x = map(p.x, TS_MINX, TS_MAXX, 0, tft.width());
    p.y = map(p.y, TS_MINY, TS_MAXY, 0, tft.height());;
    
    if (p.y > 40) {
       if (p.y < 140) { 
         tft.fillRect(0, 40, 400, 100, GREEN); //선택한 버스에 네모 표시
         tft.setTextSize(3);
         tft.setCursor(20, 80);
         tft.setTextColor(BLACK);
         tft.print("Bus : Number 97");
         Serial.println('g');

       } else if (p.y > 140 && p.y < 240) {
         tft.fillRect(0, 140, 400, 100, GREEN); //선택한 버스에 네모 표시
         tft.setTextSize(3);
         tft.setCursor(20, 80);
         tft.setTextColor(BLACK);
         tft.print("Bus : Number 97");
       }
    }

  }
}

TSPoint waitOneTouch() {

  // wait 1 touch to exit function

  TSPoint p;

  do {
    p= ts.getPoint();

    pinMode(XM, OUTPUT); //Pins configures again for TFT control
    pinMode(YP, OUTPUT);

  } while((p.z < MINPRESSURE )|| (p.z > MAXPRESSURE));

  return p;
}

void drawBorder () {

  // Draw a border

  uint16_t width = tft.width() - 1;
  uint16_t height = tft.height() - 1;
  uint8_t border = 10;

  tft.fillScreen(RED);
  tft.fillRect(border, border, (width - border * 2), (height - border * 2), WHITE);

}
