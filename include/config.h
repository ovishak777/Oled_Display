#ifndef CONFIG_H
#define CONFIG_H
#include<Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_RESET -1
#define OLED_ADDRESS 0x3C

// Change these if your board uses different I2C pins
#define SDA_PIN 8
#define SCL_PIN 9


#define ex 32//basic eyes x axis distance
#define ey 11//basic eyes y axis distance
#define rh 28//basic eyes height
#define rw 23//basic eyes width

#define Move_X_Range 21
#define Move_Y_Range 16

//to show janina effect
#define rhj 3//janina height
#define eyj 23//janina y axis distance
#define rwj 23//janina width
#define radius 3//radius for the round rectangle

const uint16_t color=SSD1306_WHITE;//color of the eye


#endif