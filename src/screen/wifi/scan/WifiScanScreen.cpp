//
// Created by meo209 on 26.06.24.
//

#include "WifiScanScreen.h"

#include <memory>
#include <TFT_eSPI.h>

#include "src/ScreenManager.h"
#include "src/Widgets.h"
#include "src/modules/WiFiModule.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

WifiScanScreen::WifiScanScreen() : Screen("Wifi - Scan") {

    auto ssids = std::make_shared<std::vector<String>>();

    Label* status_label = new Label(this, 10, tft.height() - 10, 1, 1, "Ready to scan.");
    List* wifi_list = new List(this, 10, 100, tft.width() - 20, tft.height() - 115, 2, 1, *ssids);

    Button* scan_button = new Button(this, 10, 50, tft.width() / 2 - 20, 37, 2, 1, "Scan", [this, status_label, ssids, wifi_list] {
        Serial.println("Scanning for wifis...");
        status_label->text = "Scanning...";
        draw(status_label);
        auto scanned_ssids = WifiModule::scanWifis();

        ssids->clear();

        for (const auto& ssid : scanned_ssids) {
            if (ssid.length() > 0) {  // Check if SSID is not empty
                ssids->push_back(ssid);
            }
        }

        wifi_list->content = *ssids;
        Serial.println("Finished scan for wifis.");
        status_label->text = "Finished.";
        draw(status_label);
        updateAndDraw(wifi_list);
    });

    Button* save_button = new Button(this, tft.width() / 2 + 15, 50, tft.width() / 2 - 25, 37, 2, 1, "Save", [this, status_label, ssids] {
        if (ssids->empty()) {
            Serial.println("Cannot save empty wifi list.");
            // Add your save logic here
            status_label->text = "Cannot save empty wifi list.";
            draw(status_label);
        }
    });

    defaultWidgets();

    addWidget(status_label);
    addWidget(scan_button);
    addWidget(save_button);
    addWidget(wifi_list);

    updateAndDraw();
}