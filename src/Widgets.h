//
// Created by meo209 on 25.06.24.
//

#ifndef WIDGETS_H
#define WIDGETS_H

#include <Arduino.h>
#include <vector>

#include "Widgets.h"
#include "Screen.h"

class Widget {
public:
    Screen* parent;
    int x, y, width, height;
    bool enabled = true;

    virtual void draw() = 0;

    virtual bool contains(int touch_x, int touch_y);
    virtual void onTouch(int touch_x, int touch_y);
    virtual void onRelease(int last_touch_x, int last_touch_y);
};

class Label : public Widget {
public:
    String text;
    int textSize;

    Label(int x, int y, int textSize, const String& text);

    void draw() override;
};

class Button : public Widget {
public:
    String label;
    uint8_t textSize;
    bool pressed;
    std::function<void()> onClick;

    Button(int x, int y, int width, int height, uint8_t textSize, String label, std::function<void()> onClick);

    void draw() override;

    void onTouch(int touch_x, int touch_y) override;
    void onRelease(int last_touch_x, int last_touch_y) override;
};

class List : public Widget {
public:
    std::vector<String> content;
    std::vector<Label*> labels;
    uint8_t textSize;

    List(int x, int y, int width, int height, uint8_t textSize, std::vector<String> content);

    void draw() override;

    void onTouch(int touch_x, int touch_y) override;
    void onRelease(int last_touch_x, int last_touch_y) override;
};

#endif
