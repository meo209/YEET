//
// Created by meo209 on 25.06.24.
//

#include "Screen.h"
#include <TFT_eSPI.h>

extern TFT_eSPI tft;

Screen::Screen(std::string name) : widgetCount(0), name(name) {}

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

void Screen::handleTouch(int touchX, int touchY) const {
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
