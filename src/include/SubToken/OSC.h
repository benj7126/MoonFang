#pragma once

#include "SubToken.h"

class OSC : public SubToken {
public:
    OSC(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue)
        : SubToken(chars, savedValues, curSaveValue) {};
    void AddChar(char c) override;
    bool IsDone() override;
};
