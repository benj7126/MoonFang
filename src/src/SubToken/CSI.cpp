#include "SubToken/CSI.h"

#include <iostream>

void CSI::AddChar(char c){
    chars.push_back(c);
}

bool CSI::IsDone(){
    return false;
}
