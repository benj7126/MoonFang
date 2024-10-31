#include "PT.h"
#include <string.h>

// https://man7.org/linux/man-pages/man7/pty.7.html
PT::PT() {
    // openpty(&master, &slave, &slave_name[0], 0, 0);
    char *slave_name;

    master = posix_openpt(O_RDWR | O_NOCTTY);
    grantpt(master);
    unlockpt(master);

    slave_name = ptsname(master);

    slave = open(slave_name, O_RDWR | O_NOCTTY);

    // fork child process:
    pid_t p;

    p = fork();
    if (p == 0) {// child process
        close(master);
        setsid();
        ioctl(slave, TIOCSCTTY, NULL);

        dup2(slave, 0);
        dup2(slave, 1);
        dup2(slave, 2);
        close(slave);

        // std::this_thread::sleep_for(std::chrono::milliseconds(100));

        unsetenv("TERM");
        setenv("TERM", "xterm", true);

        // execl("/bin/nvim", "/bin/nvim", (char *) NULL);
        execl("/bin/bash", "/bin/bash", (char *) NULL);
        exit(1);
        return;
    }

    pfd.fd     = master;
    pfd.events = POLLIN;
}

void PT::SendPTChars(char *s, size_t len) {
    write(master, s, len);
    //(master, &buf, 1);
}

void PT::ChangeSize(int cols, int rows) {
    struct winsize ws;

    ws.ws_row = rows;
    ws.ws_col = cols;
    if (ioctl(slave, TIOCSWINSZ, &ws) < 0)  {
        std::cout << "Failed to window size: " << strerror(errno) << std::endl;
    }
}

char PT::GetPTInput() {
    char buf;
    if (poll(&pfd, 1, 0)) {
        read(master, &buf, 1);
        return buf;
    }

    ignore = true;
    return 'o';// for now... idk...
}
