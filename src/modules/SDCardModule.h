//
// Created by meo209 on 29.06.24.
//

#ifndef SDCARDMODULE_H
#define SDCARDMODULE_H
#include <FS.h>

class SDCardModule {
public:
    static bool writeFile(fs::FS &fs, const char* path, const char* content);
};

#endif //SDCARDMODULE_H
