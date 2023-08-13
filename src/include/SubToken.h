#pragma once

#include <string>
#include <vector>

#include <array>

#include "ApplicationWindow.h"

struct between {
    char start;
    char end;
};

struct Argument{
    int ivalue;
    std::string svalue;
};

struct SplitCommand{
    std::vector<Argument> arguments;
    char type;
};

class SubToken {
private:
    bool CharBetween(char& c, int min, int max) {
        return (int)c >= min && (int)c <= max;
    };

protected:
    const std::array<char, 10> IntChars{'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};

    std::string GetCharsAsString();

    int stage = 0;
    std::vector<between> stages{};

    std::vector<char> &chars;

    std::vector<std::string> &savedValues;
    std::string &curSaveValue;

public:
    SplitCommand GetSplitCommand();
    void InternalAddChar(char c);

    SubToken(std::vector<char> &chars, std::vector<std::string> &savedValues, std::string &curSaveValue);
    virtual bool AddChar(char c) { return true; } // if it returns true, it adds the char automatically
    virtual bool IsDone() {
        return stages.size() == stage;
    };
    virtual void Activate(){};
};
