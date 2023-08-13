#include "ApplicationWindow.h"
ApplicationWindow ApplicationWindow::W{};

#include <thread>
#include <iostream>
#include <printf.h>
#include <pty.h>
#include <unistd.h>

int main(void) {
    std::string tesst = "12305";

    std::cout << stoi(tesst) << std::endl;

    ApplicationWindow::W.Start();

    return 0;
}
