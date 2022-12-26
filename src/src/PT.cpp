#include "PT.h"

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/ioctl.h>

#include <iostream>

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
    if (p == 0){ // child process
        close(master);
        setsid();
        ioctl(slave, TIOCSCTTY, NULL);

        dup2(slave, 0);
        dup2(slave, 1);
        dup2(slave, 2);
        close(slave);

        execle("/bin/bash", "/bin/bash", (char*)NULL);
        exit(1);
        return;
    }
    else if (p > 0){ // parent process
        close(slave);
    }

    pfd.fd = master;
    pfd.events = POLLIN;
}

char PT::GetPTInput(){
    std::cout<<"inp"<<std::endl;
    char buf;
    if (poll(&pfd, 1, 0)){
        read(master, &buf, 1);
        std::cout << "buf: " << buf << std::endl;
        return buf;
    }

    ignore = true;
    return 'o'; // for now... idk...
}
