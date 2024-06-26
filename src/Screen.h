//
// Created by meo209 on 25.06.24.
//

#ifndef SCREEN_H
#define SCREEN_H

#include <vector>

#include "Widgets.h"

class Screen {
public:
    std::string name;
    std::vector<Widget*> widgets;

    explicit Screen(std::string name);

    Widget* addWidget(Widget* widget);
    void defaultWidgets();

    void draw() const;

    void handleTouch(int touchX, int touchY) const;
    void handleNonTouch() const;
};

#endif
