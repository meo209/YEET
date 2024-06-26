//
// Created by meo209 on 25.06.24.
//

#include <Arduino.h>
#include <SPI.h>
#include <XPT2046_Touchscreen.h>
#include <TFT_eSPI.h>

#include "Screen.h"
#include "ScreenManager.h"
#include "Widgets.h"
#include "modules/WiFiModule.h"

#define XPT2046_IRQ 36
#define XPT2046_MOSI 32
#define XPT2046_MISO 39
#define XPT2046_CLK 25
#define XPT2046_CS 33

SPIClass mySpi = SPIClass(VSPI);
XPT2046_Touchscreen ts(XPT2046_CS, XPT2046_IRQ);
TFT_eSPI tft = TFT_eSPI();

Screen home_screen("Home");
Screen wifi_screen("WIFI");
Screen settings_screen("Settings");

ScreenManager screen_manager;

void addLabel(Screen& screen, int x, int y, int fontSize, const char* text) {
    Label* label = new Label(x, y, fontSize, text);
    screen.addWidget(label);
}

void setupHomeScreen() {
    Label* main_label = new Label(10, 10, 2, "YEET - v0.0.1");

    Button* wifi_button = new Button(10, 50, tft.width() - 20, 37, 2, "WIFI", []{
        screen_manager.switchTo(wifi_screen);
    });

    Button* settings_button = new Button(10, 50 + 37 + 5, tft.width() - 20, 37, 2, "Settings", []{
        screen_manager.switchTo(settings_screen);
    });

    home_screen.addWidget(main_label);
    home_screen.addWidget(wifi_button);
    home_screen.addWidget(settings_button);
}

void defualtWidgets(Screen& screen) {
    Label* main_label = new Label(10, 10, 2, screen.name.c_str());

    Button* back_button = new Button(tft.width() - 10 - 75, 10, 75, 37, 2, "Home", []{
        screen_manager.switchTo(home_screen);
    });

    screen.addWidget(main_label);
    screen.addWidget(back_button);
}

void wifiScanTask(void *parameter) {
    Serial.println("Scanning for wifi's...");
    for (const String& ssid : WifiModule::scanWifis()) {
        Serial.printf("%s", ssid.c_str());
        Serial.println();
    }
    vTaskDelete(nullptr); // Delete the task when done
}

void setupWIFIScreen() {
    defualtWidgets(wifi_screen);

    Button* scan_button = new Button(10, 50, tft.width() - 20, 37, 2, "Scan", []{
        xTaskCreate(
            wifiScanTask,       // Task function
            "WiFi Scan Task",   // Name of the task (for debugging)
            2048,               // Stack size (bytes)
            nullptr,               // Parameter to pass to the task
            1,                  // Task priority
            nullptr                // Task handle (not needed)
        );
    });

    wifi_screen.addWidget(scan_button);
}

void setupSettingsScreen() {
    defualtWidgets(settings_screen);
}

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

    setupHomeScreen();
    setupWIFIScreen();
    setupSettingsScreen();

    screen_manager.switchTo(home_screen);
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
