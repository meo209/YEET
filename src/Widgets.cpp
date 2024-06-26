//
// Created by meo209 on 25.06.24.
//

#include "Widgets.h"
#include <TFT_eSPI.h>

#include <utility>

extern TFT_eSPI tft;

bool Widget::contains(const int touchX, const int touchY) {
    return (touchX >= x && touchX <= x + width && touchY >= y && touchY <= y + height);
}

void Widget::onTouch(int touchX, int touchY) {
    // Default implementation, can be overridden in subclasses
}

void Widget::onRelease() {
    // Default implementation, can be overridden in subclasses
}

Label::Label(const int x, const int y, const int textSize, const String& text) {
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

Button::Button(const int x, const int y, const int width, const int height, const uint8_t textSize, String label, std::function<void()> onClick) : pressed(false) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->label = std::move(label);
    this->textSize = textSize;
    this->onClick = onClick;
}

void Button::draw() {
    tft.drawRect(x, y, width, height, TFT_DARKGREY);
    const int16_t textX = x + (width - tft.textWidth(label, textSize)) / 2;
    const int16_t textY = y + (height - tft.fontHeight(textSize)) / 2;
    tft.setTextSize(textSize);
    tft.setTextColor(TFT_WHITE, TFT_BLACK);
    tft.drawString(label, textX, textY, 2);
}

void Button::onTouch(int touchX, int touchY) {
    pressed = true;
}

void Button::onRelease() {
    if (pressed) {
        pressed = false;

        onClick();
    }
}

List::List(const int x, const int y, const int width, const int height, const uint8_t textSize, std::vector<String> content) : content(std::move(content)), lastTouchY(0), isScrolling(false), scrollOffset(0) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->textSize = textSize;
}

void List::draw() {
    tft.fillRect(x, y, width, height, TFT_BLACK); // Clear the list area
    tft.drawRect(x, y, width, height, TFT_DARKGREY);

    int yPosIndex = y - scrollOffset;
    for (const String& ctn : content) {
        if (yPosIndex > y + height) break; // Stop drawing if we go outside the list area

        if (yPosIndex >= y) { // Only draw visible items
            auto* label = new Label(x, yPosIndex, textSize, ctn);
            label->draw();
            delete label;
        }
        yPosIndex += tft.fontHeight(textSize);
    }
}

void List::onTouch(int touchX, int touchY) {
    if (contains(touchX, touchY)) {
        if (!isScrolling) {
            isScrolling = true;
            lastTouchY = touchY;
        } else {
            int delta = touchY - lastTouchY;
            lastTouchY = touchY;

            scrollOffset -= delta;
            if (scrollOffset < 0) scrollOffset = 0;

            int maxOffset = content.size() * tft.fontHeight(textSize) - height;
            if (scrollOffset > maxOffset) scrollOffset = maxOffset;

            draw(); // Redraw the list with new offset
        }
    }
}

void List::onRelease() {
    isScrolling = false;
}
