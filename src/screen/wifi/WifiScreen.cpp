//
// Created by meo209 on 26.06.24.
//

#include "WifiScreen.h"

#include <memory>
#include <TFT_eSPI.h>

#include "src/ScreenManager.h"
#include "src/Widgets.h"
#include "src/modules/WiFiModule.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

WifiScreen::WifiScreen() : Screen("Wifi") {

    auto ssids = std::make_shared<std::vector<String>>();

    Label* status_label = new Label(this, 10, tft.height() - 10, 1, 1, "Ready to scan.");
    List* wifi_list = new List(this, 10, 100, tft.width() - 20, tft.height() - 115, 2, 2, *ssids);

    Button* scan_button = new Button(this, 10, 50, tft.width() - 20, 37, 2, 2, "Scan", [this, status_label, ssids, wifi_list] {
        Serial.println("Scanning for wifi's...");
        status_label->text = "Scanning...";
        status_label->draw();
        auto scanned_ssids = WifiModule::scanWifis();

        ssids->clear();

        for (const auto& ssid : scanned_ssids) {
            if (ssid.length() > 0) {  // Check if SSID is not empty
                ssids->push_back(ssid);
            }
        }

        wifi_list->content = *ssids;
        status_label->text = "Finished.";
        updateAndDraw();
    });

    defaultWidgets();

    addWidget(status_label);
    addWidget(scan_button);
    addWidget(wifi_list);

    updateAndDraw();
}