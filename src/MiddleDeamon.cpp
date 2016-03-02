//
// Created by lenfien on 15/12/10.
//
#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/resource.h>

static void demonlize() {
    if (fork() != 0)
        exit(0);

    setsid();

    if (fork())
        exit(0);

    for (int index = 0; index < 125; index ++ )
        close (index);

    chdir ("/tmp");
}

int main(int argc, const char **args) {
    demonlize();
}