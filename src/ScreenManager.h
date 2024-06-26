//
// Created by meo209 on 26.06.24.
//

#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H
#include "Screen.h"

class ScreenManager {
public:
    Screen current;

    ScreenManager();

    virtual void switchTo(Screen other);
};

#endif //SCREENMANAGER_H
