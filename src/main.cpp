#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include"config.h"

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

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
    int rightx = 127 - ex - width;
    display.fillRect(rightx, y, width, height, color);
}
void rrleftEye(int x,int y, int width, int height){
  display.fillRoundRect(x,y,width,height,radius,color);
}
void rrrightEye(int x, int y, int width, int height) {
    int rightx = 127 - ex - width;
    display.fillRoundRect(rightx, y, width, height,radius, color);
}

void showEye() {
    cd();
    leftEye(ex,ey,rw,rh);
    rightEye(ex,ey,rw,rh);
    dd();
}
void blinkEyes() {
    // close eyes
    for (int h = 2; h < rh; h += 3) {
        cd();
        int close_open_ey=(ey + h) / 2;
        leftEye(ex, (close_open_ey), rw, rh - h);
        rightEye(ex, (close_open_ey), rw, rh - h);
        dd();
        delay(11);
    }
    // open eyes
    for (int h = rh; h > 3; h -= 2) {
        cd();
        int close_open_ey=(ey + h) / 2;
        leftEye(ex, (close_open_ey), rw, rh - h);
        rightEye(ex, (close_open_ey), rw, rh - h);
        dd();
        delay(12);
    }
}
void rrblinkEyes() {
    // close eyes
    for (int h = 2; h < rh; h += 3) {
        cd();
        int close_open_ey=(ey + h) / 2;
        rrleftEye(ex, (close_open_ey), rw, rh - h);
        rrrightEye(ex, (close_open_ey), rw, rh - h);
        dd();
        delay(11);
    }
    // open eyes
    for (int h = rh; h > 3; h -= 2) {
        cd();
        int close_open_ey=(ey + h) / 2;
        rrleftEye(ex, (close_open_ey), rw, rh - h);
        rrrightEye(ex, (close_open_ey), rw, rh - h);
        dd();
        delay(12);
    }
}


void showJanina() {
    cd();
    leftEye(ex,eyj,rwj,rhj);
    rightEye(ex,eyj,rwj,rhj);
    dd();
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
    delay(1000);
    
}
 