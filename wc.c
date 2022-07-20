#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 128


int numBytes(int argc, char* argv[], int index) {
//finding the number of bytes
    off_t size = 0;
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    size = lseek(fd, 0, SEEK_END);
    if (size == -1) perror("lseek");
    return size;
} //numBytes

int numWords(int argc, char* argv[], int index) {
    int num_words = 0;
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    int n;
    char buffer[BUFFSIZE];
    while((n = read(fd, buffer, BUFFSIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if ((buffer[i] ==  ' ') || (buffer[i] == '\n')) {
                num_words++;
            } //if
        } //for
    } //while
    return num_words;
} //numWords

int numLines(int argc, char* argv[], int index) {
    int num_lines = 0;
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    int n;
    char buffer[BUFFSIZE];
    while((n = read(fd, buffer, BUFFSIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            if (buffer[i] ==  '\n') {
                num_lines++;
            } //if
        } //for
    } //while
    return num_lines;
} //numLines


void print (int argc, char* argv[]) {
    int x;
    int cflag = 0;
    int lflag = 0;
    int wflag = 0;
    int clwflag = 0;

    if (argc == 1) {
        int num_lines = 0;
        int size = 0;
        int num_words = 0;
        char buf[BUFFSIZE];
        int y;
        while ((y = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
            for (int i = 0; i < y; i++) {
                if (buf[i] == '\n') {
                    num_lines++;
                } //if
                if ((buf[i] == '\n') || (buf[i] == ' ')) {
                    num_words++;
                } //if
                size++;
            } //for
        } // while
        printf("%d  %d  %d\n", num_lines, num_words, size);
    } //if

    while ((x = getopt(argc, argv, "clw")) != -1) {
            switch (x)
            {
            case 'c':
                cflag = 1;
                break;
            case 'l':
                lflag = 1;
                break;
            case 'w':
                wflag = 1;
                break;
            default:
                clwflag = 1;
            } //switch
        } //while

        for (int j = optind; j < argc; j++) {
            int size = 0;
            int num_words = 0;
            int num_lines = 0;
            int fd = 0;
            char* filename = argv[j];
            fd = open(filename, O_RDONLY);
            if (fd == -1) {
                char buf[BUFFSIZE];
                int y;
                while ((y = read(STDIN_FILENO, buf, BUFFSIZE)) > 0) {
                    for (int i = 0; i < y; i++) {
                        if (buf[i] == '\n') {
                            num_lines++;
                        } //if
                        if (buf[i] =='\n' || buf[i] == ' ') {
                            num_words++;
                        } //if
                        size++;
                    } //for
                } //while
                if (lflag == 1) {
                    printf("%d  ", num_lines);
                } //if
                if (wflag == 1) {
                   printf("%d  ", num_words);
                } //if
                if (cflag == 1) {
                   printf("%d  ", size);
                } //if
                if (clwflag == 1) {
                    printf("%d  ", num_lines);
                    printf("%d  ", num_words);
                    printf("%d  ", size);
                } //if
                if (lflag == 0 && wflag == 0 && cflag == 0 && clwflag == 0) {
                    printf("%d  ", num_lines);
                    printf("%d  ", num_words);
                    printf("%d  ", size);
                } //if
                printf("\n");
            } else {
                if (lflag == 1) {
                    printf(" %d  ", (numLines(argc, argv, j)));
                } //if
                if (wflag == 1) {
                    printf(" %d  ", (numWords(argc, argv, j)));
                } //if
                if (cflag == 1) {
                    printf(" %d  ", (numBytes(argc, argv, j)));
                } //if
                if (clwflag == 1) {
                    printf(" %d  ", (numLines(argc, argv, j)));
                    printf(" %d  ", (numWords(argc, argv, j)));
                    printf(" %d  ", (numBytes(argc, argv, j)));
                } //if
            if (lflag == 0 && wflag == 0 && cflag == 0 && clwflag == 0) {
                printf(" %d  ", (numLines(argc, argv, j)));
                printf(" %d  ", (numWords(argc, argv, j)));
                printf(" %d  ", (numBytes(argc, argv, j)));
            } //if
            printf("\n");
            } //for
        } //if
} //print

int main(int argc, char* argv[]) {
    print(argc, argv);
} //main
