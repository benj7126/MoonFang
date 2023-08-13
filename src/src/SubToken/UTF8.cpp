#include "SubToken/UTF8.h"

bool UTF8::AddChar(char c){
    curSaveValue = c;
    return false; // dont do default add
}

// should prolly make this (its actiavte) do the char adding instead of what i do rn...

bool UTF8::IsDone(){
    return true;
}
