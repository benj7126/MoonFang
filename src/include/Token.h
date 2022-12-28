#pragma once

#include "SubToken.h"

#include <vector>
#include <string>
#include <memory>

enum TokenType{
    NONE,
    ANSI,
    UTF8,
};

class Token{
private:
    std::vector<char> chars;
    std::shared_ptr<SubToken> st;
    
public:
    TokenType type = NONE;
    std::vector<int> savedValues;
    std::string curSaveValue;

    Token();
    void AddChar(char c);
    void Clear();
    bool IsEnded();
    
};
