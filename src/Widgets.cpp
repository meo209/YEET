//
// Created by meo209 on 25.06.24.
//

#include "Widgets.h"
#include <TFT_eSPI.h>

#include <utility>

extern TFT_eSPI tft;

bool Widget::contains(const int touch_x, const int touch_y) {
    return (touch_x >= x && touch_x <= x + width && touch_y >= y && touch_y <= y + height);
}

void Widget::onTouch(const int touch_x, const int touch_y) {
    // Default implementation, can be overridden in subclasses
}

void Widget::onRelease(const int touch_x, const int touch_y) {
    // Default implementation, can be overridden in subclasses
}

Label::Label(Screen* parent, const int x, const int y, const int textSize, const String& text) : Widget() {
    this->parent = parent;
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

Button::Button(Screen* parent, const int x, const int y, const int width, const int height, const uint8_t textSize, String label, std::function<void()> onClick) : pressed(false) {
    this->parent = parent;
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

void Button::onTouch(int touch_x, int touch_y) {
    pressed = true;
}

void Button::onRelease(int last_tocu, int touch_y) {
    if (pressed) {
        pressed = false;

        onClick();
    }
}

List::List(Screen* parent, const int x, const int y, const int width, const int height, const uint8_t textSize, std::vector<String> content) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->textSize = textSize;
    this->content = content;

    int yPosIndex = y - tft.fontHeight(2);
    for (const String& string : content) {
        Label* label = new Label(parent, x, y ,textSize, string);
        parent->addWidget(label);
        labels.push_back(label);
        yPosIndex += tft.fontHeight(textSize);
    }
}

void List::draw() {
    tft.fillRect(x, y, width, height, TFT_BLACK); // Clear the list area
    tft.drawRect(x, y, width, height, TFT_DARKGREY);
}

void List::onTouch(int touch_x, int touch_y) {

}

void List::onRelease(int last_touch_x, int last_touch_y) {

}
