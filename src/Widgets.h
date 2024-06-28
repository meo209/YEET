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
    std::vector<Widget*> children;
    int x, y, width, height;
    bool enabled = true;

    virtual void draw() = 0;
    virtual void update();

    virtual void drawChildren();

    virtual bool contains(int x, int y);
    virtual bool contains(int x, int y, int width, int height);
    virtual bool contains(Widget* widget, int x, int y);
    virtual bool contains(Widget* widget);
    virtual void onTouch(int touch_x, int touch_y);
    virtual void onTouchSimple(int touch_x, int touch_y);
    virtual void onRelease(int last_touch_x, int last_touch_y);
};

class Label : public Widget {
public:
    String text;
    int text_size, font;
    bool centered;

    Label(Screen* parent, int x, int y, int textSize, int font, const String& text);
    Label(Screen* parent, int x, int y, int textSize, int font, bool centered, const String& text);

    void draw() override;
};

class Button : public Widget {
public:
    Label* label;
    bool pressed;
    std::function<void()> onClick;

    Button(Screen* parent, int x, int y, int width, int height, uint8_t textSize, uint8_t font, String text, std::function<void()> onClick);

    void draw() override;

    void onTouch(int touch_x, int touch_y) override;
    void onRelease(int last_touch_x, int last_touch_y) override;
};

class List : public Widget {
public:
    std::vector<String> content;
    uint8_t textSize;
    int font;
    int scroll_offset, last_touch_y;
    bool is_scrolling;

    List(Screen* parent, int x, int y, int width, int height, uint8_t textSize, int font, std::vector<String> content);

    void update() override;
    void draw() override;

    void onTouch(int touch_x, int touch_y) override;
    void onTouchSimple(int touch_x, int touch_y) override;
    void onRelease(int last_touch_x, int last_touch_y) override;
};

#endif
