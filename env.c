#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char **argv, char** env) {
    while (*env)
        printf("%s\n", *env++);
    return 0;
} //main
