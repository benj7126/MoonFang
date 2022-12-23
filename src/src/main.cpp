#include "ApplicationWindow.h"

#include <thread>
#include <iostream>
#include <printf.h>
#include <pty.h>
#include <unistd.h>

int main(void) {
    ApplicationWindow ap{};
    ap.Start();

    return 0;
}
