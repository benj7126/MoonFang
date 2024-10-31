#include "SubToken/CSI.h"

#include "Graphics/XFTColors.h"

#include <iostream>
#include <Cursor.h>

#include "Terminal.h"

#include <algorithm>

bool CSI::Activate() {
    // std::cout << "Handeling " << GetCharsAsString() << " for csi..." << std::endl;

    SplitCommand command = GetSplitCommand();

    // std::cout << command.type << std::endl;

    switch (command.type) {
        case ('h'):
            {
                std::string val = command.getArgument(0).text;
                if (val == "?2004"){
                    MFCursor::cursor -> BracketedPasteMode = true;
                } else if (val == "?1049"){
                    Terminal::term.SetBuffer(true);
                    Terminal::term.ClearFromLineToLine(0, Terminal::term.lineCount);
                    MFCursor::cursor -> set(0, 0);
                }
                else
                    std::cout << "missing h: " << val << std::endl;
            }
            return false;
        case ('l'):
            {
                std::string val = command.getArgument(0).text;
                if (val == "?2004"){
                    MFCursor::cursor -> BracketedPasteMode = false;
                } else if (val == "?1049"){
                    Terminal::term.SetBuffer(false);
                    MFCursor::cursor -> set(0, 0);
                    return true;
                }
                else
                    std::cout << "missing l: " << val << std::endl;
            }
            return false;
        case ('m'):
            // send (args) to cursor so that it can set some value, text color, back color, and italic boldness all such nonsense...
            if (command.getArgument(0).getValue() <= 47 && command.getArgument(0).getValue() >= 40){
                std::cout << "Found " << command.getArgument(0).getValue() << " so like... yeah..." << std::endl;
            }

            if (command.getArgument(0).getValue() == 38 || command.getArgument(0).getValue() == 48) {
                XftColor c = {0, 0, 0, 0};
                unsigned int colorReturn = 0;

                if (command.getArgument(1).getValue() == 5){
                    int color = command.getArgument(2).getValue();

                    // std::cout << color << " try get with " << command.getArgument(0).getValue() << std::endl;

                    if (color <= 15){
                        colorReturn = color;
                    } else if (color <= 231) {
                        color -= 16;
                        int b = color % 6;
                        color /= 6;
                        int g = color % 6;
                        color /= 6;
                        int r = color & 6;
                        colorReturn = Graphics::XFTColors::GetColor((unsigned char)(r * (255.0 / 5.0)), (unsigned char)(g * (255.0 / 5.0)), (unsigned char)(b * 255.0 / 5.0), 255);
                    } else {
                        color -= 232;
                        color = (int)((double)color / 24.0 * 255.0);
                        colorReturn = Graphics::XFTColors::GetColor((unsigned char)color, (unsigned char)color, (unsigned char)color, 255);
                    }
                }

                if (command.getArgument(1).getValue() == 2)
                    colorReturn = Graphics::XFTColors::GetColor((unsigned char) command.getArgument(2).getValue(), (unsigned char) command.getArgument(3).getValue(), (unsigned char) command.getArgument(4).getValue(), 255);

                if (command.getArgument(0).getValue() == 38)
                    MFCursor::cursor -> foregroundColor = colorReturn;
                else {
                    // std::cout << colorReturn << " set bg" << std::endl;
                    MFCursor::cursor -> useBackground   = true;
                    MFCursor::cursor -> backgroundColor = colorReturn;
                }
            } else if (command.getArgument(0).getValue() == 39) {
                MFCursor::cursor -> foregroundColor = MFCursor::cursor -> defaultForegroundColor;

                if (command.trueArgCount() > 1){
                    MFCursor::cursor -> useBackground = false;
                }
            } else if (command.getArgument(0).getValue() == 49) {
                MFCursor::cursor -> useBackground = false;

                if (command.trueArgCount() > 1){
                    MFCursor::cursor -> foregroundColor = MFCursor::cursor -> defaultForegroundColor;
                }
            } else {
                int fColor = 0;
                int bColor = 0;

                if (command.trueArgCount() == 2) {
                    // std::cout << "C: " << command.getArgument(0).getValue() << " - " << command.getArgument(1).getValue()<< std::endl;
                    if (command.getArgument(0).getValue() == 1){
                       int color = command.getArgument(1).getValue();

                        if (color < 40)
                            // FGround
                            fColor = color + 60;
                        else
                            // BGround
                            bColor = color - 10 + 60;
                    } else {
                        fColor = command.getArgument(0).getValue();
                        bColor = command.getArgument(1).getValue() - 10;
                    }
                } else {
                    int color = command.getArgument(0).getValue();

                    if (color < 40)
                        // FGround
                        fColor = color;
                    else
                        // BGround
                        bColor = color - 10;
                }

                if (fColor >= 90)
                    fColor -= (60 - 8);

                if (bColor >= 90)
                    bColor -= (60 - 8);

                if (fColor >= 30 && fColor <= 45)
                    MFCursor::cursor -> foregroundColor = fColor - 30;

                if (bColor >= 30 && bColor <= 45)
                {
                    MFCursor::cursor -> backgroundColor = bColor - 30;
                    MFCursor::cursor -> useBackground = true;
                }
                
                /*
                if (bColor != 0)
                    std::cout << "bColor -> " << bColor << std::endl;

                if (fColor != 0)
                    std::cout << "fColor -> " << fColor << std::endl;
                */

                if (fColor == 0 && bColor == 0){
                    MFCursor::cursor -> foregroundColor = MFCursor::cursor -> defaultForegroundColor;
                    MFCursor::cursor -> useBackground = false;
                }
                // colors[i]
            }

            return false;
        case ('H'):
            // send (args) to cursor as well, sets cursor position, 1, 1 is top left corner...
            {
                int y = command.getArgument(0).getValue(1);
                int x = command.getArgument(1).getValue(1);
                
                MFCursor::set(x - 1, y - 1);
            }
            return false;
        case ('A'):
            MFCursor::setY(MFCursor::getY() - command.getArgument(0).getValue(1));
            return false;
        case ('B'):
            MFCursor::setY(MFCursor::getY() + command.getArgument(0).getValue(1));
            return false;
        case ('C'):
            MFCursor::setX(MFCursor::getX() + command.getArgument(0).getValue(1));
            return false;
        case ('D'):
            MFCursor::setX(MFCursor::getX() - command.getArgument(0).getValue(1));
            return false;
        case ('E'):
            MFCursor::set(0, MFCursor::getY() + command.getArgument(0).getValue(1));
            return false;
        case ('F'):
            MFCursor::set(0, MFCursor::getY() - command.getArgument(0).getValue(1));
            return false;
        case ('G'):
            MFCursor::setX(command.getArgument(0).getValue(0));
            return false;
        case ('s'):
            MFCursor::savePosition();
            return false;
        case ('u'):
            MFCursor::loadPosition();
            return false;
        case ('X'):
            Terminal::term.ClearInLineFromCharToChar(MFCursor::getY(), MFCursor::getX(), MFCursor::getX() + command.getArgument(0).getValue(1));
            return false;
        case ('P'):
            Terminal::term.DeleteInLineFromCharToChar(MFCursor::getY(), MFCursor::getX(), MFCursor::getX() + command.getArgument(0).getValue(1));
            return false;
        case ('K'):
            {
                int v = command.getArgument(0).getValue(0);

                if (v == 0){
                    Terminal::term.ClearInLineFromCharToChar(MFCursor::getY(), MFCursor::getX(), Terminal::term.charactersPerLine);
                } else if (v == 1){
                    Terminal::term.ClearInLineFromCharToChar(MFCursor::getY(), MFCursor::getX(), Terminal::term.charactersPerLine);
                } else if (v == 2){
                    Terminal::term.ClearFromLineToLine(MFCursor::getY(), MFCursor::getLY());
                }
            }
            return true;
        case ('J'):
            switch(command.getArgument(0).getValue()){
                case (0):
                    Terminal::term.ClearInLineFromCharToChar(MFCursor::getY(), MFCursor::getX(), Terminal::term.charactersPerLine);
                    Terminal::term.ClearFromLineToLine(MFCursor::getY(), Terminal::term.lineCount);
                    break;
                case (1):
                    Terminal::term.ClearInLineFromCharToChar(MFCursor::getY(), 0, MFCursor::getX());
                    Terminal::term.ClearFromLineToLine(0, MFCursor::getY());
                    break;
                case (2): case (3):
                    Terminal::term.ClearFromLineToLine(0, Terminal::term.lineCount);
                    break;
            }
            return true;
        default:
            std::cout << "missing of type: " << command.type << " | csi ";
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
}
