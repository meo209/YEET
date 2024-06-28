//
// Created by meo209 on 28.06.24.
//

#include "DeviceScreen.h"

#include <TFT_eSPI.h>

#include "src/ScreenManager.h"
#include "src/Widgets.h"


extern TFT_eSPI tft;
extern ScreenManager screen_manager;

DeviceScreen::DeviceScreen() : Screen("Device") {
    Button* restart_button = new Button(this, 10, 50, tft.width() - 20, 37, 2, 1, "Restart", [] {
        ESP.restart();
    });

    defaultWidgets();

    addWidget(restart_button);

    updateAndDraw();
}