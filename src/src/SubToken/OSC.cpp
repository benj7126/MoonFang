#include "SubToken/OSC.h"

#include <iostream>

void OSC::AddChar(char c){
    chars.push_back(c);
}

bool OSC::IsDone(){
    return chars.back() == 0x07;
}
