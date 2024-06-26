//
// Created by meo209 on 25.06.24.
//

#include "Screen.h"
#include <TFT_eSPI.h>

#include <utility>

#include "ScreenManager.h"
#include "screen/HomeScreen.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

Screen::Screen(std::string name) : name(std::move(name)) {}

Widget* Screen::addWidget(Widget* widget) {
    widgets.push_back(widget);
    return widget;
}

void Screen::defaultWidgets() {
    auto* main_label = new Label(10, 10, 2, name.c_str());

    auto* back_button = new Button(tft.width() - 10 - 75, 10, 75, 37, 2, "Home", []{
        screen_manager.switchTo(HomeScreen());
    });

    addWidget(main_label);
    addWidget(back_button);
}

void Screen::update() {
    tft.fillScreen(TFT_BLACK);
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->draw();
        }
    }
}

void Screen::handleTouch(const int touchX, const int touchY) const {
    for (Widget* widget : widgets) {
        if (widget->enabled == true && widget->contains(touchX, touchY)) {
            widget->onTouch(touchX, touchY);
        }
    }
}

void Screen::handleNonTouch() const {
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->onRelease();
        }
    }
}