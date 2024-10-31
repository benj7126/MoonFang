#pragma once

#include "SubToken.h"

class UTF8 : public SubToken{
private:
    int expectedSize = 0;
public:
    UTF8(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue)
        : SubToken(chars, savedValues, curSaveValue) {};
    bool AddChar(char c) override;
    bool IsDone() override;
    
};
