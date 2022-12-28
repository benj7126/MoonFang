#include "SubToken/UTF8.h"

#include <iostream>

void UTF8::AddChar(char c){
    chars.push_back(c);
}

bool UTF8::IsDone(){
    return true;
}
