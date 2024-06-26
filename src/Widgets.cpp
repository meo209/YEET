//
// Created by meo209 on 25.06.24.
//

#include "Widgets.h"
#include <TFT_eSPI.h>

#include <utility>

extern TFT_eSPI tft;

bool Widget::contains(int touchX, int touchY) {
    return (touchX >= x && touchX <= x + width && touchY >= y && touchY <= y + height);
}

void Widget::onTouch() {
    // Default implementation, can be overridden in subclasses
}

void Widget::onRelease() {
    // Default implementation, can be overridden in subclasses
}

Label::Label(int x, int y, int textSize, String text) {
    this->x = x;
    this->y = y;
    this->width = tft.textWidth(text);
    this->height = textSize * 8; // Assume height of text size
    this->text = text;
    this->textSize = textSize;
}

void Label::draw() {
    tft.setTextSize(textSize);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(text, x, y);
}

Button::Button(int x, int y, int width, int height, int textSize, String label, void (*onClick)()) : pressed(false) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->label = std::move(label);
    this->textSize = textSize;
    this->onClick = onClick;
}

void Button::draw() {
    tft.drawRect(x, y, width, height, TFT_WHITE);
    int16_t textX = x + (width - tft.textWidth(label, textSize)) / 2;
    int16_t textY = y + (height - tft.fontHeight(textSize)) / 2;
    tft.setTextSize(textSize);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(label, textX, textY);
}

void Button::onTouch() {
    pressed = true;
}

void Button::onRelease() {
    if (pressed) {
        pressed = false;

        onClick();
    }
}