//
// Created by meo209 on 25.06.24.
//

#include "Widgets.h"
#include <TFT_eSPI.h>
#include "Config.h"

extern TFT_eSPI tft;

bool Widget::contains(const int x, const int y) {
    return x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height;
}

bool Widget::contains(const int x, const int y, const int width, const int height) {
    return x >= this->x && x <= this->x + width && y >= this->y && y <= this->y + height;
}

bool Widget::contains(Widget *widget, const int x, const int y) {
    return x >= widget->x && x <= widget->x + widget->width && y >= widget->y && y <= widget->y + widget->height;
}

bool Widget::contains(Widget *widget) {
    return this->x >= widget->x && this->x <= widget->x + widget->width && this->y >= widget->y && this->y <= widget->y
           + widget->height;
}

void Widget::drawChildren() {
    for (Widget *child: children)
        child->draw();
}

void Widget::onTouch(const int touch_x, const int touch_y) {
    // Default implementation, can be overridden in subclasses
}

void Widget::onTouchSimple(const int touch_x, const int touch_y) {
    // Default implementation, can be overridden in subclasses
}

void Widget::onRelease(const int touch_x, const int touch_y) {
    // Default implementation, can be overridden in subclasses
}

void Widget::update() {
    // Default implementation, can be overridden in subclasses
}

Label::Label(Screen *parent, const int x, const int y, const int textSize, const int font,
             const String &text) : Widget(), centered(false) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->width = tft.textWidth(text);
    this->height = tft.fontHeight(font);
    this->text_size = textSize;
    this->font = font;
    this->text = text;
}

Label::Label(Screen *parent, const int x, const int y, const int textSize, const int font, const bool centered,
             const String &text) : Widget(), centered(centered) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->width = tft.textWidth(text, font);
    this->height = tft.fontHeight(font);
    this->text_size = textSize;
    this->font = font;
    this->text = text;
}

void Label::draw() {
    String display_text = text;
    int text_width = tft.textWidth(text, font);

    if (text_width > width) {
        int ellipsis_width = tft.textWidth("...", font);
        int max_width = width - ellipsis_width;
        int lenght = text.length();

        while (text_width > max_width && lenght > 0) {
            display_text = text.substring(0, --lenght);
            text_width = tft.textWidth(display_text, font);
        }

        display_text += "...";
    }

    tft.fillRect(x, y, width, height, TFT_BLACK);
    tft.setTextSize(text_size);
    tft.setTextColor(TFT_WHITE, TFT_BLACK); // Set text color

    if (centered) {
        int centered_x = x + (width) / 2;
        int centered_y = y + (height - tft.fontHeight(font)) / 2;
        tft.drawCentreString(display_text, centered_x, centered_y, font);
    } else {
        tft.drawString(display_text, x, y); // Draw the text at the top-left corner of the label
    }
#ifdef DEBUG_UI
    tft.drawRect(x, y, width, height, TFT_RED); // Draw the bounding box
#endif
}

Button::Button(Screen *parent, const int x, const int y, const int width, const int height, const uint8_t textSize,
               const uint8_t font, String text, std::function<void()> onClick) : pressed(false) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;

    int labelX = x + (width - tft.textWidth(text, font)) / 2;
    int labelY = y + (height - tft.fontHeight(font)) / 2;

    this->label = new Label(parent, labelX, labelY, textSize, font, true, text);
    children.push_back(label);

    this->onClick = onClick;
}

void Button::draw() {
    tft.drawRect(x, y, width, height, TFT_DARKGREY);
    drawChildren();
}

void Button::onTouch(int touch_x, int touch_y) {
    pressed = true;
}

void Button::onRelease(const int last_touch_x, const int last_touch_y) {
    if (pressed && contains(last_touch_x, last_touch_y)) {
        pressed = false;
        onClick();
    }
}

List::List(Screen *parent, const int x, const int y, const int width, const int height, const uint8_t textSize,
           const int font, std::vector<String> content) {
    this->parent = parent;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->textSize = textSize;
    this->font = font;
    this->content = content;
    this->scroll_offset = 0;
    this->is_scrolling = false;
    this->last_touch_y = 0;
}

void List::update() {
    int yPosIndex = y;
    for (const String &string: content) {
        Label *label = new Label(parent, x + 1, yPosIndex, textSize, font, string);
        label->width = width;
        children.push_back(label);
        yPosIndex += tft.fontHeight(textSize);
    }
}


void List::draw() {
    tft.fillRect(x, y, width, height, TFT_BLACK); // Clear the list area
    tft.drawRect(x, y, width, height, TFT_DARKGREY); // Draw the list boundary

    for (Widget *child: children) {
        int childBottom = child->y + child->height;
        if (child->y >= y && childBottom <= y + height) {
            // Only draw if within visible area
            child->draw();
        }
    }
}

void List::onTouch(const int touch_x, const int touch_y) {
    is_scrolling = true;
    last_touch_y = touch_y;
}

void List::onTouchSimple(const int touch_x, const int touch_y) {
    if (is_scrolling) {
        int delta = touch_y - last_touch_y;
        last_touch_y = touch_y;

        scroll_offset -= delta;
        if (scroll_offset < 0) scroll_offset = 0;

        const int max_offset = content.size() * tft.fontHeight(font);
        if (scroll_offset > max_offset)
            scroll_offset = max_offset;

        int yPosIndex = y - scroll_offset;
        for (Widget *child: children) {
            child->y = yPosIndex;
            yPosIndex += tft.fontHeight(font) / 2;
        }

        draw();
    }
}

void List::onRelease(int last_touch_x, int last_touch_y) {
    is_scrolling = false;
}
