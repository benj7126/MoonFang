#pragma once

#include "SubToken.h"

class CSI : public SubToken{
public:
    void AddChar(char c) override;
    bool IsDone() override;
    
};
