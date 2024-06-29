//
// Created by meo209 on 26.06.24.
//

#ifndef ERRORSCREEN_H
#define ERRORSCREEN_H

#include <WString.h>

#include "src/Screen.h"

class ErrorScreen : public Screen {
public:
    explicit ErrorScreen(const String& message);
};

#endif //ERRORSCREEN_H
