#pragma once

#include "SubToken.h"

class UTF8 : public SubToken{
public:
    void AddChar(char c) override;
    bool IsDone() override;
    
};
