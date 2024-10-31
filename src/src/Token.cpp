#include "Token.h"

#include <iostream>

#include "SubToken/CSI.h"
#include "SubToken/OSC.h"
#include "SubToken/UTF8.h"

Token::Token() = default;

// return weather char was used or not
void Token::AddChar(char c) {
    // std::cout << c << "   test 3" << type << std::endl;
    if (st != nullptr) {
        // std::cout << c << "   test 2" << type << std::endl;
        st->InternalAddChar(c);
        return;
    }

    //type = UTF8_T; // show all, basically...
    //std::cout << c << "   test " << type << std::endl;

    if (type == NONE_T) {
        if (c == 0x1B) {
            type = ANSI_T;
        } else {
            type = UTF8_T;
        }
    }

    switch (type) {
        case ANSI_T: {
            if (c == ']') {
                st = std::make_shared<OSC>(chars, savedValues, curSaveValue);
            } else if (c == '[') {
                st = std::make_shared<CSI>(chars, savedValues, curSaveValue);
            } else {
                // std::cout << c << " | " << (int)c << " | potentially missing ansi type" << std::endl;
            }
            break;
        }
        case UTF8_T: {
            st = std::make_shared<UTF8>(chars, savedValues, curSaveValue);
            st->InternalAddChar(c);
            break;
        }
        case NONE_T:
            break;// not sure yet
    }

    //if (st == nullptr)
    //st->InternalAddChar(c);
    //chars.push_back(c);
}

bool Token::Clear() {
    bool termChange = false;
    if (st != nullptr) {
        termChange = st->Activate();
    }

    type = NONE_T;
    chars.clear();
    curSaveValue.clear();
    savedValues.clear();

    st = nullptr;

    return termChange;
}

bool Token::IsEnded() {
    if (st != nullptr && st->IsDone()){
        return true;
    }
    /* std::cout << type << " | " << chars.size() << std::endl; */
    /* switch (type) { */
    /*     case UTF8: { */
    /*         return true; */
    /*         break; */
    /*     } */
    /*     case ANSI: { */
    /*         std::cout << (int)chars.back() << ": " << 0x40 << " | " << 0x7E <<std::endl; */
    /*         if (CheckLastCharWithin(chars, )) */
    /*         if ((int) chars.back() >= 0x20 && (int) chars.back() <= 0x7E) */
    /*             return true; */
    /*         std::cout << " didnt ret " << std::endl; */
    /*         break; */
    /*     } */
    /* } */

    return false;
}
