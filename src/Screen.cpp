//
// Created by meo209 on 25.06.24.
//

#include "Screen.h"
#include <TFT_eSPI.h>

#include <utility>

#include "ScreenManager.h"
#include "screen/HomeScreen.h"
#include "Widgets.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

Screen::Screen(std::string name) : name(std::move(name)), last_touch_x(0), last_touch_y(0) {

}

template <typename T>
T* Screen::addWidget(T* widget) {
    widget->parent = this;
    widgets.push_back(static_cast<Widget*>(widget));
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

void Screen::handleTouch(const int touch_x, const int touch_y) {
    last_touch_x = touch_x;
    last_touch_y = touch_x;
    for (Widget* widget : widgets) {
        if (widget->enabled == true && widget->contains(touch_x, touch_y)) {
            widget->onTouch(touch_x, touch_y);
        }
    }
}

void Screen::handleNonTouch() const {
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->onRelease(last_touch_x, last_touch_y);
        }
    }
}