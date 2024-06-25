//
// Created by meo209 on 25.06.24.
//

#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>
#include "Screen.h"
#include "Widgets.h"

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

Screen mainScreen;

Screen homeScreen;
Screen settingScreen;

void setup() {
    Serial.begin(115200);

    mySpi.begin(XPT2046_CLK, XPT2046_MISO, XPT2046_MOSI, XPT2046_CS);
    if (!ts.begin(mySpi)) {
        Serial.println("Failed to initialize touchscreen!");
        while (1);
    }
    ts.setRotation(0);  // Ensure the rotation matches the display

    tft.init();
    tft.setRotation(0); // Ensure the rotation matches the touchscreen
    tft.fillScreen(TFT_BLACK);

    Label* h_label = new Label(10, 10, 2, "YEET.");
    Button* h_button = new Button(10, 50, 100, 35, 2, "Settings", []{
        mainScreen = settingScreen;
        mainScreen.draw();
        Serial.println("Swtiched to settings.");
    });

    homeScreen.addWidget(h_label);
    homeScreen.addWidget(h_button);

    Label* s_label = new Label(10, 10, 2, "Settings");
    Button* s_button = new Button(10, 50, 100, 35, 2, "Back", [] {
        mainScreen = homeScreen;
        mainScreen.draw();
        Serial.println("Swtiched to home.");
    });

    settingScreen.addWidget(s_label);
    settingScreen.addWidget(s_button);

    mainScreen = homeScreen;

    // Draw the screen
    mainScreen.draw();
}

void loop() {
    if (ts.tirqTouched() && ts.touched()) {
        TS_Point p = ts.getPoint();
        int16_t touchX = map(p.x, 0, 4095, 0, tft.width());
        int16_t touchY = map(p.y, 0, 4095, 0, tft.height());
        
        mainScreen.handleTouch(touchX, touchY);
        delay(50);
    } else {
        mainScreen.handleNonTouch();
    }
}
