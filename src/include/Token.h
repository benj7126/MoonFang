#pragma once

#include "SubToken.h"

#include <vector>
#include <string>
#include <memory>

enum TokenType{
    NONE_T,
    ANSI_T,
    UTF8_T,
};

class Token{
private:
    std::vector<char> chars;
    std::shared_ptr<SubToken> st;
    
public:
    TokenType type = NONE_T;
    std::vector<int> savedValues;
    std::string curSaveValue;

    Token();
    void AddChar(char c);
    void Clear();
    bool IsEnded();
    
};
