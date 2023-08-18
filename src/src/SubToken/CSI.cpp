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
        case('m'):
            // send (args) to cursor so that it can set some value, text color, back color, and italic boldness all such nonsense...
            break;
        case('H'):
            // send (args) to cursor as well, sets cursor position, 1, 1 is top left corner...
            break;
        default:
            std::cout << "missing of type: " << command.type << " | csi" << std::endl;
            break;

    }
}
