#include <Keyboard.h>
#include <Mouse.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>

#define WHITE SSD1306_WHITE
#define BLACK SSD1306_BLACK

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define SCREEN_ADDRESS 0x3c

#define SDA 26
#define SCL 27

#define LEFT_CTRL 0x80
#define CTRL 0x80
#define LEFT_SHIFT 0x81

//KEY_LEFT_ALT
#define OPTION 0X82
#define CMD 0x83
#define RIGHT_CTRL 0x84
#define RIGHT_SHIFT 0x85
#define TAB 0xB3
#define CAPS_LOCK 0xC1
#define BACKSPACE 0xB2
#define RETURN 0xB0
#define PAGE_UP 0xD3
#define PAGE_DOWN 0xD6

//ARROW KEYS
#define UP_ARROW 0xDA
#define DOWN_ARROW 0xD9
#define LEFT_ARROW 0xD8
#define RIGHT_ARROW 0xD7


Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

int currMode = 0;
int modes = 2;


class btnComplex{
  int btnPin;
  int action[2][5][5];
  public: btnComplex(int pin, int actions[2][5][5]){
    btnPin = pin;
    pinMode(btnPin, INPUT_PULLUP);

    for(int a=0;a<2;a++){
      for(int b=0;b<5;b++){
        for(int c=0;c<5;c++){
          action[a][b][c] = actions[a][b][c];
          }
        }
      }
    }

    void checkButtons(){
      if(digitalRead(btnPin) != HIGH){
        pressButtons();
        while(digitalRead(btnPin) != HIGH){}
        }
      }
    void pressButtons(){
      int currKey;
        for(int i = 0; i < sizeof(action[currMode])/sizeof(action[currMode][i]); i++){
          for(int x = 0; x < sizeof(action[currMode][i])/sizeof(action[currMode][i][x]); x++){
            currKey =  action[currMode][i][x];
            if(currKey != 0 && x != 5){
                Keyboard.press(currKey);
                } 
              }
             Keyboard.releaseAll(); 
             delay(action[currMode][i][4]);
            }
          }
  };

class btnSimple{
  int btnPin;
  int action[10];
  public: btnSimple(int pin, int actions[10]){
    btnPin = pin;
    pinMode(btnPin, INPUT_PULLUP);
    
    for(int i=0; i<10; i++){
      action[i] = actions[i];
      }
    }
   void checkButtons(int* checker){
    if(*checker == btnPin){return;}
    if(digitalRead(btnPin) != HIGH){
      pressButtons();
      *checker = btnPin;
      while(digitalRead(btnPin) != HIGH){}
      }
    }
    
    void pressButtons(){
      int currKey;
      for(int i=0; i<sizeof(action)/sizeof(action[i]); i++){
        currKey = action[i];
        if(currKey != 0){
          Keyboard.press(currKey);
          }
        }
      Keyboard.releaseAll();
      }
};



int values1[2][5][5] = {
    {
    {0x83, 0x81, 0x63, 0, 500}, {0x83, 0x77, 0, 0, 450}, {0x83, 0x74, 0, 0, 450}, {0xB0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}
    }, 
    {
    {22, 7, 9, 10, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}, {0, 0, 0, 0, 0}
    }};
btnComplex btn1(2, values1);

int leftHalf[10] = {CTRL, OPTION, LEFT_ARROW, 0, 0, 0, 0, 0, 0, 0};
btnSimple btnS1(3, leftHalf);

int rightHalf[10] = {CTRL, OPTION, RIGHT_ARROW, 0, 0, 0, 0, 0, 0, 0};
btnSimple btnS2(4, rightHalf);

int upperHalf[10] = {CTRL, OPTION, UP_ARROW, 0, 0, 0, 0, 0, 0, 0};
btnSimple btnS3(5, upperHalf);

int lowerHalf[10] = {CTRL, OPTION, DOWN_ARROW, 0, 0, 0, 0, 0, 0, 0};
btnSimple btnS8(9, lowerHalf);

int bothMaj[10] = {CTRL, OPTION, 0x65, 0, 0, 0, 0, 0, 0, 0};
btnSimple btnS6(7, bothMaj);

//placeholder value for lastBtn pressed pointer
int lastBtn;

//void nightSky(Adafruit_SSD1306 screen);

void setup() {
  // put your setup code here, to run once:
  Keyboard.begin();
  Wire1.setSDA(SDA);
  Wire1.setSCL(SCL);
  Wire1.begin();
  Serial.begin(9600);
  if(!oled.begin(SSD1306_SWITCHCAPVCC, 0x3D)){
    Serial.println("not detected");
  }
  oled.clearDisplay();
  oled.fillScreen(WHITE);
  oled.display();
}

btnSimple arr[5] = {btnS1, btnS2, btnS3, btnS6, btnS8};

void loop() {
  btn1.checkButtons();
  for(int i = 0; i <= sizeof(arr)/sizeof(arr[0])-1; i++){
    arr[i].checkButtons(&lastBtn);
  }
}
