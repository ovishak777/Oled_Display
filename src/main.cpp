#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include"config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
int curOffsetX = 0;
int curOffsetY = 0;
int targetOffsetX = 0;
int targetOffsetY = 0;

//shorcut for the clearDisplay function
void cd() {
    display.clearDisplay();
}
//shortcut for display.display
void dd() {
    display.display();
}

//basic left eye
void leftEye(int x, int y, int width, int height) {
    display.fillRect(x, y, width, height, color);
}
//basic right eye
void rightEye(int x, int y, int width, int height) {
    int rightx = (127 - ex - width) + curOffsetX;
    display.fillRect(rightx, y, width, height, color);
}
// rounded left eye
void rrleftEye(int x,int y, int width, int height){
  display.fillRoundRect(x,y,width,height,radius,color);
}
// rounded right eye
void rrrightEye(int x, int y, int width, int height) {
    int rightx = (127 - ex - width) + curOffsetX;
    display.fillRoundRect(rightx, y, width, height,radius, color);
}
//show eyes(normal rectangle eyes)
void showEye() {
    cd();
    leftEye(ex+curOffsetX, ey+curOffsetY, rw, rh);
    rightEye(ex+curOffsetX, ey+curOffsetY, rw, rh);
    dd();
}
void showrrEye(){
    cd();
    rrleftEye(ex+curOffsetX, ey+curOffsetY, rw, rh);
    rrrightEye(ex+curOffsetX, ey+curOffsetY, rw, rh);
    dd();
}
//core coding of the blinking eyes
void blinkEyes() {
    // close eyes
    for (int h = 2; h <= rh; h += 3) {
        cd();
        int close_open_ey = ey+curOffsetY + h/2;
        leftEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        rightEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        dd();
        delay(11);
    }
    // open eyes
    for (int h = rh; h >= 3; h -= 2) {
        cd();
        int close_open_ey = ey+curOffsetY + h/2;
        leftEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        rightEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        dd();
        delay(12);
    }
}
void rrblinkEyes() {
    // close eyes
    for (int h = 0; h <= rh; h += 3) {
        cd();
        int close_open_ey = ey+curOffsetY + h/2;
        rrleftEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        rrrightEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        dd();
        delay(11);
    }
    // open eyes
    for (int h = rh; h >= 0; h -= 2) {
        cd();
        int close_open_ey = ey+curOffsetY + h/2;
        rrleftEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        rrrightEye(ex+curOffsetX, (close_open_ey), rw, rh - h);
        dd();
        delay(12);
    }
}


void showJanina() {
    cd();
    leftEye(ex, eyj, rwj, rhj);
    rightEye(ex, eyj, rwj, rhj);
    dd();
}

enum EyeState{center,left,right,rightup,leftup,down,rightdown,leftdown};
int startoffsetX = 0;
int startoffsetY = 0;
float t=0.0;
float dt=0.09;
void setEyeTarget(EyeState pos){
startoffsetX = curOffsetX;
startoffsetY = curOffsetY;
t=0.0;
switch(pos){
    case center:
        targetOffsetX = 0;
        targetOffsetY = 0;
        break;
    case left:
        targetOffsetX = -Move_X_Range;
        targetOffsetY = 0;
        break;
    case right:
        targetOffsetX = Move_X_Range;
        targetOffsetY = 0;
        break;
    case rightup:
        targetOffsetX= Move_X_Range;
        targetOffsetY= -Move_Y_Range;
        break;
    case leftup:
        targetOffsetX= -Move_X_Range;
        targetOffsetY= -Move_Y_Range;
        break;
    case down:
        targetOffsetX= 0;
        targetOffsetY= Move_Y_Range;
        break;
    case rightdown:
        targetOffsetX= Move_X_Range;
        targetOffsetY= Move_Y_Range;
        break;
    case leftdown:
        targetOffsetX= -Move_X_Range;
        targetOffsetY= Move_Y_Range;
        break;
}
}
float smoothStep(float x){
    return x*x*(3.0 - 2.0*x);
}

void moveEyes(){
    if (t<1.0){
        t+=dt;
        if(t>1.0){
            t=1.0;
        }
        float tEased=smoothStep(t);
        curOffsetX = startoffsetX + (targetOffsetX - startoffsetX) * tEased;
        curOffsetY = startoffsetY + (targetOffsetY - startoffsetY) * tEased;

    }
    
}
 
void moveRREyesTo(EyeState pos,int stepDelay){
    setEyeTarget(pos);
    while(t<1.0){
        moveEyes();
        showrrEye();
        delay(stepDelay);
    }
}

 
void setup() {
    Serial.begin(115200);
 
    // Initialize I2C
    Wire.begin(SDA_PIN, SCL_PIN);
 
    // Initialize OLED
    if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
        Serial.println("SSD1306 initialization failed!");
        while (true);
    }
    
 
    Serial.println("OLED Test Complete!");
}

void loop() {
    rrblinkEyes();
    delay(500);
    moveRREyesTo(center,28);


    
}