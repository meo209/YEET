//
// Created by meo209 on 25.06.24.
//

#ifndef WIDGETS_H
#define WIDGETS_H

#include <Arduino.h>
#include <vector>

class Widget {
public:
    int x, y, width, height;
    bool enabled = true;

    virtual void draw() = 0;

    virtual bool contains(int touchX, int touchY);
    virtual void onTouch(int touchX, int touchY);
    virtual void onRelease();
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

    void onTouch(int touchX, int touchY) override;
    void onRelease() override;
};

class List : public Widget {
public:
    std::vector<String> content;
    uint8_t textSize;
    int lastTouchY, scrollOffset;
    bool isScrolling;

    List(int x, int y, int width, int height, uint8_t textSize, std::vector<String> content);

    void draw() override;

    void onTouch(int touchX, int touchY) override;
    void onRelease() override;
};

#endif
