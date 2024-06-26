//
// Created by meo209 on 25.06.24.
//

#include "Screen.h"
#include <TFT_eSPI.h>

#include <utility>

extern TFT_eSPI tft;

Screen::Screen(std::string name) : name(std::move(name)),  widgetCount(0) {}

void Screen::addWidget(Widget* widget) {
    if (widgetCount < maxWidgets) {
        widgets[widgetCount++] = widget;
    }
}

void Screen::draw() const {
    tft.fillScreen(TFT_BLACK);
    for (int i = 0; i < widgetCount; i++) {
        widgets[i]->draw();
    }
}

void Screen::handleTouch(const int touchX, const int touchY) const {
    for (int i = 0; i < widgetCount; i++) {
        if (widgets[i]->contains(touchX, touchY)) {
            widgets[i]->onTouch();
            break;
        }
    }
}

void Screen::handleNonTouch() const {
    for (int i = 0; i < widgetCount; i++) {
        widgets[i]->onRelease();
    }
}
