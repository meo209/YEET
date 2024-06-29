//
// Created by meo209 on 29.06.24.
//

#include "SDCardModule.h"

bool SDCardModule::writeFile(fs::FS &fs, const char *path, const char *content) {
    File file = fs.open(path, FILE_WRITE);

    if (!file) {
        Serial.printf("Failed to open file %s for writing.", path);
        Serial.println();
        return false;
    }
    if (!file.print(content)) {
        Serial.printf("Failed writing to file: %s", path);
        Serial.println();
        return false;
    }
    file.close();
    return true;
}
