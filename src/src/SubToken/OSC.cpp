#include "SubToken/OSC.h"

#include <iostream>

bool OSC::IsDone(){
    if (chars.size() == 0)
        return false;

    return chars.back() == 0x07;
}

bool OSC::AddChar(char c){
    if (stage == 2 && c != 0x07)
        curSaveValue += c;

    if (c == '0' || c == ';')
        stage++;

    return true;
}

void OSC::Activate(){
    if (stage == 2) // idk what else this should be able to do...
        std::cout << "Set window title to " << curSaveValue << std::endl;
    //         ApplicationWindow::window
}
