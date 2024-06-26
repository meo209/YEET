//
// Created by meo209 on 26.06.24.
//

#include "HomeScreen.h"

#include "WifiScreen.h"
#include "src/ScreenManager.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

HomeScreen::HomeScreen() : Screen("Home") {
    Label* main_label = new Label(10, 10, 2, "YEET - v0.0.1");

    Button* wifi_button = new Button(10, 50, tft.width() - 20, 37, 2, "Wifi", [] {
        screen_manager.switchTo(WifiScreen());
    });

    addWidget(main_label);
    addWidget(wifi_button);
}