//
// Created by meo209 on 25.06.24.
//

#include <Arduino.h>
#include <memory>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

#include "Screen.h"
#include "ScreenManager.h"
#include "modules/WiFiModule.h"
#include "screen/HomeScreen.h"
#include "screen/WifiScreen.h"

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

ScreenManager screen_manager = ScreenManager();

void setup() {
    Serial.begin(115200);

    mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    if (!ts.begin(mySpi)) {
        Serial.println("Failed to initialize touchscreen.");
        while (true);
    }
    ts.setRotation(0);  // Ensure the rotation matches the display

    tft.init();
    tft.setRotation(0); // Ensure the rotation matches the touchscreen
    tft.fillScreen(TFT_BLACK);

    screen_manager.switchTo(HomeScreen());
}

void loop() {
    if (ts.tirqTouched() && ts.touched()) {
        TS_Point p = ts.getPoint();
        const long touchX = map(p.x, 0, 4095, 0, tft.width());
        const long touchY = map(p.y, 0, 4095, 0, tft.height());
        
        screen_manager.current.handleTouch(touchX, touchY);
        delay(50);
    } else {
        screen_manager.current.handleNonTouch();
    }
}
