#include "SubToken/CSI.h"

#include <iostream>

void CSI::Activate(){
    // std::cout << "Handeling " << GetCharsAsString() << " for csi..." << std::endl;

    SplitCommand command = GetSplitCommand();
    
    // std::cout << "test: " << command.arguments[0].svalue << " | "<< command.arguments[0].ivalue << std::endl;
    switch(command.type){
        case('h'):
            if (command.arguments[0].svalue == "?2004")
                ApplicationWindow::W.t.MFC.BracketedPasteMode = true;
            break;
        case('l'):
            if (command.arguments[0].svalue == "?2004")
                ApplicationWindow::W.t.MFC.BracketedPasteMode = false;
            break;
        default:
            std::cout << "missing of type: " << command.type << " | csi" << std::endl;
            break;

    }
}
