//
// Created by meo209 on 26.06.24.
//

#include "ErrorScreen.h"

#include <TFT_eSPI.h>

#include "src/screen/wifi/WifiScreen.h"
#include "src/ScreenManager.h"
#include "src/Widgets.h"
#include "src/screen/device/DeviceScreen.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

ErrorScreen::ErrorScreen(const String& message) : Screen("Error") {
    Label* main_label = new Label(this, 10, 60, 1, 1, false, "Error: \n" + message);

    defaultWidgets();

    addWidget(main_label);

    updateAndDraw();
}