#include "SubToken/CSI.h"

#include <iostream>

bool CharBetween(std::vector<char> Cs, int min, int max) {
    return (int) Cs.back() >= min && (int) Cs.back() <= max;
}

void CSI::AddChar(char c){
    chars.push_back(c);
}

bool CSI::IsDone(){
    return chars.size() > 2 && CharBetween(chars, 0x40, 0x7E);
}
