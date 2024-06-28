//
// Created by meo209 on 26.06.24.
//

#include "WiFiModule.h"

#include <WiFi.h>

/*
 * Scan for nerby WiFi networks and return a list of SSID's.
 */
std::vector<String> WifiModule::scanWifis() {
    WiFi.mode(WIFI_STA);
    WiFi.disconnect();

    const int n = WiFi.scanNetworks();
    std::vector<String> ssids;
    for (int i = 0; i < n; i++) {
        ssids.push_back(WiFi.SSID(i));
    }
    return ssids;
}
