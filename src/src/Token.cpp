#include "Token.h"

#include <iostream>

#include "SubToken/CSI.h"
#include "SubToken/OSC.h"
#include "SubToken/UTF8.h"

Token::Token() = default;

// return weather char was used or not
void Token::AddChar(char c) {
    if (st != nullptr) {
        st->AddChar(c);
        return;
    }

    if (chars.size() == 0) {
        if (c == 0x1B) {
            type = ANSI_T;
        } else {
            type = UTF8_T;
        }
    }

    switch (type) {
        case ANSI_T: {
            if (chars.size() == 1) {
                if (c == ']') {
                    st = std::make_shared<OSC>(chars, savedValues, curSaveValue);
                } else if (c == '['){
                    st = std::make_shared<CSI>(chars, savedValues, curSaveValue);
                } else {
                    std::cout << c << " is missing asci thingy..." << std::endl;
                }
            }
            break;
        }
        case UTF8_T: {
            st = std::make_shared<UTF8>(chars, savedValues, curSaveValue);
            break;
        }
    }

    chars.push_back(c);
}

void Token::Clear() {
    if (type == ANSI_T){
        std::cout << " getting chars(except first size: " << chars.size() << ") > ";
        for (int ccount = 1; ccount < chars.size(); ccount++){
            std::cout << chars.at(ccount);
        }
        std::cout << std::endl;
    }
    type = NONE_T;
    chars.clear();
    st = nullptr;
}

bool Token::IsEnded() {
    if (st != nullptr && st->IsDone())
        return true;
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
