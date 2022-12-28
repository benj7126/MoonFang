#pragma once

#include "SubToken.h"

class CSI : public SubToken {
public:
    CSI(std::vector<char> &chars, std::vector<int> &savedValues, std::string &curSaveValue)
        : SubToken(chars, savedValues, curSaveValue) {};
    void AddChar(char c) override;
    bool IsDone() override;
};
