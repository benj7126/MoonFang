#pragma once

#include "SubToken.h"

class OSC : public SubToken {
public:
    OSC(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue)
        : SubToken(chars, savedValues, curSaveValue) {};
    bool IsDone() override;
    bool AddChar(char c) override;
    void Activate() override;

    int counter = 0;
};
