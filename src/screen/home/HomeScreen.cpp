//
// Created by meo209 on 26.06.24.
//

#include "HomeScreen.h"

#include <TFT_eSPI.h>

#include "src/screen/wifi/WifiScreen.h"
#include "src/ScreenManager.h"
#include "src/Widgets.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

HomeScreen::HomeScreen() : Screen("Home") {
    Label* main_label = new Label(this, 10, 10, 2, 2, false, "YEET - v0.0.1");

    Button* wifi_button = new Button(this, 10, 50, tft.width() - 20, 37, 2, 1, "Wifi", [] {
        auto* screen = new WifiScreen();
        screen_manager.switchTo(*screen);
    });

    addWidget(main_label);
    addWidget(wifi_button);

    updateAndDraw();
}