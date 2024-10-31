#include "SubToken/OSC.h"

#include <iostream>

bool OSC::IsDone(){
    if (chars.size() == 0)
        return false;

    return stage == 2;
}

bool stageP = false;
bool OSC::AddChar(char c){
    chars.push_back(c);

    if (c == (char)0x07 || c == (char)0x9C)
        std::cout << "stage: " << stage << std::endl;

    if (stageP && c == (char)0x5C){
        stage = 2;
        return false;
    }

    stageP = false;

    switch (stage){
        case 0:
            if (c == ';')
                stage = 1;
            break;
        case 1:
            if (c == (char)0x07 || c == (char)0x9C)
                stage = 2;
            if (c == (char)0x1B)
                stageP = true;
            break;
    }

    return false;
}

bool OSC::Activate(){

    SplitCommand command = GetSplitCommand();
    switch (command.getArgument(0).getValue(-1)){
        case 0:
            std::cout << "Set title to '" << command.getArgument(1).text << "'" << std::endl;
            return false;
        defaul:
            std::cout << "missing of type: " << command.type << " | osc ";
            std::cout << command.trueArgCount() << " - ";

            /* for (Argument a : command.arguments) { */
            /*     std::cout << a.getValue(-1) << "|" << a.text << " "; */
            /* } */
            for (int i = 0; i < command.trueArgCount(); i++) {
                std::cout << ((command.getArgument(i).getValue(-999) == -999) ? "#" : "" + command.getArgument(i).getValue(-1)) << "|_" << command.getArgument(i).text << "_ ";
            }

            std::cout << std::endl;
            return false;
    }
    
    return false;
}
