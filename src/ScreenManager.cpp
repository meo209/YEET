//
// Created by meo209 on 26.06.24.
//

#include "ScreenManager.h"

ScreenManager::ScreenManager() : current(Screen("BOOT")) {}


void ScreenManager::switchTo(Screen& other) {
    Serial.printf("Screen switched from %s to %s", current.name.c_str(), other.name.c_str());
    Serial.println();

    current = other;
    current.draw();
}
