#include "MFChar.h"

MFChar::MFChar(std::string chars, MFCursor &cursor) : text{chars}, foregroundColor{cursor.foregroundColor}, backgroundColor{cursor.backgroundColor} {}

void MFChar::Draw(std::shared_ptr<Graphics::Canvas> CV, int x, int y){
    CV->SetColor(foregroundColor);
    CV->DrawText(x, y, text);
}
