//
// Created by meo209 on 26.06.24.
//

#include "WifiScreen.h"

#include "src/ScreenManager.h"
#include "src/modules/WiFiModule.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

WifiScreen::WifiScreen() : Screen("Wifi") {

    Button* scan_button = new Button(10, 50, tft.width() - 20, 37, 2, "Scan", []{
        Serial.println("Scanning for wifi's...");
        for (const String& ssid : WifiModule::scanWifis()) {
            Serial.printf("%s", ssid.c_str());
            Serial.println();
        }
    });

    Label* text_label = new Label(10, 100, 2, "Hello Text");
    text_label->enabled = false;

    Button* trigger_label_button = new Button(10, 150, tft.width() - 20, 37, 2, "Trigger Label", [=] {
        text_label->enabled = !text_label->enabled;
        update();
    });

    defaultWidgets();

    addWidget(text_label);
    addWidget(trigger_label_button);
    addWidget(scan_button);

    update();
}