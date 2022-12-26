#pragma once

#include <poll.h>

class PT{ // pseudo terminal
private:
    int master, slave;
    pollfd pfd;

public:
    bool ignore;
    PT();
    char GetPTInput();
    
};
