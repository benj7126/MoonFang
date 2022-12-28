#pragma once

#include <vector>
#include <string>

class SubToken{
protected:
    int stage = 0;

    std::vector<char>& chars;

    std::vector<int>& savedValues;
    std::string& curSaveValue;

    bool isActive = false;

public:
    SubToken(std::vector<char>& chars, std::vector<int>& savedValues, std::string& curSaveValue);
    virtual void AddChar(char c) = 0;
    virtual bool IsDone() = 0;

};
