#include "Token.h"

#include <iostream>

#include "SubToken/CSI.h"

bool CheckLastCharWithin(std::vector<char> Cs, int min, int max) {
    return (int) Cs.back() >= min && (int) Cs.back() <= max;
}

Token::Token() = default;

// return weather char was used or not
void Token::AddChar(char c) {
    if (st != nullptr) {
        st->AddChar(c);
        return;
    }

    if (chars.size() == 0) {
        /* printf("%02hhX\n", c); */
        /* printf("%02hhX\n", (char)0x1B); */
        if (c == 0x1B) {
            type = ANSI;
        } else {
            type = UTF8;
        }
        chars.push_back(c);
        return;
    }

    switch (type) {
        case ANSI: {
            st = std::make_shared<CSI>(chars, savedValues, curSaveValue);
            break;
        }
            /* case UTF8: { */
            /*     chars.push_back(c); */
            /*     break; */
            /* } */
    }

    chars.push_back(c);
}

void Token::Clear() {
    type = NONE;
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
