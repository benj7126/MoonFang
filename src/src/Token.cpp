#include "Token.h"

#include <iostream>

#include "SubToken/CSI.h"
#include "SubToken/UTF8.h"

bool CheckLastCharWithin(std::vector<char> Cs, int min, int max) {
    return (int) Cs.back() >= min && (int) Cs.back() <= max;
}

Token::Token() = default;

// return weather char was used or not
void Token::AddChar(char c) {
    std::cout << "adding char to chars pre len: " << chars.size() << std::endl;
    if (st != nullptr) {
        st->AddChar(c);
        return;
    }

    if (chars.size() == 0) {
        std::cout << c << " <";
        if (c == 0x1B) {
            std::cout << " ansi >";
            type = ANSI_T;
        } else {
            std::cout << " utf8 >";
            type = UTF8_T;
        }
        std::cout << std::endl;
        printf("%02hhX\n", c);
        printf("%02hhX\n", (char)0x1B);
    }

    switch (type) {
        case ANSI_T: {
            st = std::make_shared<CSI>(chars, savedValues, curSaveValue);
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
