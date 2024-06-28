//
// Created by meo209 on 25.06.24.
//

#include "Screen.h"
#include <TFT_eSPI.h>

#include <utility>

#include "ScreenManager.h"
#include "Widgets.h"
#include "screen/home/HomeScreen.h"

extern TFT_eSPI tft;
extern ScreenManager screen_manager;

Screen::Screen(std::string name) : name(std::move(name)), last_touch_x(0), last_touch_y(0) {

}

Widget* Screen::addWidget(Widget* widget) {
    widget->parent = this;
    widgets.push_back(widget);
    return widget;
}

void Screen::defaultWidgets() {
    auto* main_label = new Label(this, 10, 10, 2, 2, name.c_str());

    auto* back_button = new Button(this, tft.width() - 10 - 75, 10, 75, 37, 2, 2, "Home", []{
        screen_manager.switchTo(HomeScreen());
    });

    addWidget(main_label);
    addWidget(back_button);
}

void Screen::draw() {
    tft.fillScreen(TFT_BLACK);
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->draw();
        }
    }
}

void Screen::update() {
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->update();
        }
    }
}

void Screen::updateAndDraw() {
    update();
    draw();
}

void Screen::handleTouch(const int touch_x, const int touch_y) {
    last_touch_x = touch_x;
    last_touch_y = touch_y;
    for (Widget* widget : widgets) {
        if (widget->enabled == true) {
            widget->onTouchSimple(touch_x, touch_y);

            if (widget->contains(touch_x, touch_y)) {
                widget->onTouch(touch_x, touch_y);
            }
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