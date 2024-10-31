#include "ApplicationWindow.h"
ApplicationWindow ApplicationWindow::W{};

#include "Terminal.h"
Terminal Terminal::term = {};

#include <thread>
#include <iostream>
#include <printf.h>
#include <pty.h>
#include <unistd.h>

#include "Cursor.h"

int main(void) {
    std::string tesst = "12305";

    MFCursor::SetCursorBuffer(true);

    std::cout << stoi(tesst) << std::endl;

    ApplicationWindow::W.Start();

    return 0;
}
