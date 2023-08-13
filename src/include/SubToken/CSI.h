#pragma once

#include "SubToken.h"

#include <iostream>

class CSI : public SubToken {
public:
    CSI(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue)
        : SubToken(chars, savedValues, curSaveValue) {
        stages = {{0x30, 0x3F},
                {0x20, 0x2F},
                {0x40, 0x7E}};

        //std::cout << stages.size() << " <- size, of type csi..." << std::endl;
    };

    void Activate() override;
};
