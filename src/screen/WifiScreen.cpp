//
// Created by meo209 on 26.06.24.
//

#include "WifiScreen.h"

#include "src/ScreenManager.h"
#include "src/modules/WiFiModule.h"

extern TFT_eSPI tft;

WifiScreen::WifiScreen() : Screen("Wifi") {
    Button* scan_button = new Button(10, 50, tft.width() - 20, 37, 2, "Scan", []{
        Serial.println("Scanning for wifi's...");
        for (const String& ssid : WifiModule::scanWifis()) {
            Serial.printf("%s", ssid.c_str());
            Serial.println();
        }
    });

    defaultWidgets();

    addWidget(scan_button);
}