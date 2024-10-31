#pragma once

#include <poll.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include <chrono>
#include <thread>

#include <iostream>

class PT{ // pseudo terminal
private:
    int master, slave;
    pollfd pfd;

public:
    bool ignore;
    PT();
    char GetPTInput();
    void SendPTChars(char* s, size_t len);
    void ChangeSize(int w, int h);

};
