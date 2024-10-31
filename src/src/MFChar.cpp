#include "MFChar.h"

MFChar::MFChar(XftChar32 chars) : value{chars}, foregroundColor{MFCursor::cursor -> foregroundColor} {
    if (MFCursor::cursor -> useBackground){
        useBackground = true;
        backgroundColor = MFCursor::cursor -> backgroundColor;
    }
}

MFChar::MFChar() : foregroundColor{MFCursor::cursor -> foregroundColor} {
    if (MFCursor::cursor -> useBackground){
        useBackground = true;
        backgroundColor = MFCursor::cursor -> backgroundColor;
    }
}
