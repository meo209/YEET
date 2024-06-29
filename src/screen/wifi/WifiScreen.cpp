//
// Created by meo209 on 28.06.24.
//

#include "WifiScreen.h"

#include <TFT_eSPI.h>

#include "scan/WifiScanScreen.h"
#include "src/ScreenManager.h"
#include "src/Widgets.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

WifiScreen::WifiScreen() : Screen("Wifi") {

    Button* scan_select_button = new Button(this, 10, 50, tft.width() - 20, 37, 2, 1, "Scan + Save", [] {
        screen_manager.switchTo(WifiScanScreen());
    });

    defaultWidgets();

    addWidget(scan_select_button);

    updateAndDraw();
}