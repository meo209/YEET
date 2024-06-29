//
// Created by meo209 on 25.06.24.
//

#include <Arduino.h>
#include <memory>
#include <SD.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

#include "Screen.h"
#include "ScreenManager.h"
#include "modules/WiFiModule.h"
#include "screen/home/HomeScreen.h"

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

    Serial.println();
    Serial.println("---INFO---");
    Serial.printf("MODEL: %s", ESP.getChipModel()); Serial.println();
    Serial.printf("CORES: %d", ESP.getChipCores()); Serial.println();
    Serial.printf("PSRAM SIZE: %d", ESP.getPsramSize()); Serial.println();
    Serial.printf("HEAP SIZE: %d", ESP.getHeapSize()); Serial.println();
    Serial.printf("FLASH SIZE: %d", ESP.getFlashChipSize()); Serial.println();
    Serial.printf("SKETCH SIZE: %d", ESP.getSketchSize()); Serial.println();
    Serial.println("---INFO---");

    mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    if (!ts.begin(mySpi)) {
        Serial.println("Failed to initialize touchscreen.");
        while (true);
    }
    ts.setRotation(0);  // Ensure the rotation matches the display

    tft.init();
    tft.setRotation(0); // Ensure the rotation matches the touchscreen
    tft.fillScreen(TFT_BLACK);

    /*
    if (!SD.begin(SS, mySpi)) {
        Serial.println("SD Card mount failed but is required.");
        tft.drawString("SD Card mount failed but is required.", 0, 0, 1);
        return;
    }
    */

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
