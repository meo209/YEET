//
// Created by meo209 on 25.06.24.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "Widgets.h"

class Screen {
public:
    std::string name;
    static constexpr int maxWidgets = 10;
    Widget* widgets[maxWidgets]{};
    int widgetCount;

    explicit Screen(std::string name);

    void addWidget(Widget* widget);

    void draw() const;

    void handleTouch(int touchX, int touchY) const;
    void handleNonTouch() const;
};

#endif
