//
// Created by meo209 on 25.06.24.
//

#ifndef SCREEN_H
#define SCREEN_H

#include "Widgets.h"

class Screen {
public:
    static const int maxWidgets = 10;
    Widget* widgets[maxWidgets]{};
    int widgetCount;

    Screen();

    void addWidget(Widget* widget);

    void draw() const;

    void handleTouch(int touchX, int touchY) const;
    void handleNonTouch() const;
};

#endif
