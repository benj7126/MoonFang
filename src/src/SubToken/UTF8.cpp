#include "SubToken/UTF8.h"

#include <iostream>

bool UTF8::AddChar(char c){
    if (expectedSize == 0) {
        if (!((unsigned char)c >> 7))
            expectedSize = 1;
        else if ((unsigned char)c >> 5 == 0b110)
            expectedSize = 2;
        else if ((unsigned char)c >> 4 == 0b1110)
            expectedSize = 3;
        else if ((unsigned char)c >> 3 == 0b11110)
            expectedSize = 4;
    }

    if (expectedSize != 0)
        curSaveValue += c;
    else
        std::cout << "Ignored character " << c << " | " << (int)c << " as it didnt act as expected UTF8" << std::endl;

    return false; // dont do default add
}

// should prolly make this (its actiavte) do the char adding instead of what i do rn...

bool UTF8::IsDone(){
    if (expectedSize == 0)
        return false;

    if (curSaveValue.size() == expectedSize){
        for (int i = 0; i < 4-expectedSize; i++){
            curSaveValue = (char)0 + curSaveValue;
        }

        return true;
    }

    if (curSaveValue.size() > expectedSize+1)
        throw "Error in UTF8";

    return false;
}
