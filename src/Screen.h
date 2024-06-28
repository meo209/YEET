//
// Created by meo209 on 25.06.24.
//

#ifndef SCREEN_H
#define SCREEN_H

#include <string>
#include <vector>

#include "Screen.h"

class Widget;

class Screen {
public:
    std::string name;
    std::vector<Widget*> widgets;

    int last_touch_x;
    int last_touch_y;

    explicit Screen(std::string name);

    Widget* addWidget(Widget* widget);
    void defaultWidgets();

    void update();
    void update(Widget* widget);
    void draw();
    void draw(Widget* widget);
    void updateAndDraw();
    void updateAndDraw(Widget* widget);

    void handleTouch(int touch_x, int touch_y);
    void handleNonTouch() const;
};

#endif
