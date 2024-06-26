//
// Created by meo209 on 26.06.24.
//

#ifndef WIFIMODULE_H
#define WIFIMODULE_H
#include <vector>
#include <WString.h>

class WifiModule {
public:
    static std::vector<String> scanWifis();
};

#endif //WIFIMODULE_H
