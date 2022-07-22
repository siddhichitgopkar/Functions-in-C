#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFFSIZE 10

// method declarations for main program
void readFile(int i, char* argv[]);
void commandLine();

// global variables manipulated in multiple functions
int lines = 10;
int bytes = BUFFSIZE;
int status = 0;

/**
 * The program copies input files to standard output, with the option
 * to specify how many lines or how many bytes to output. If there
 * is no specificer, the program outputs the last 10 lines.
 *
 * @return whether program completed successfully or not
 * @param argc number of command-line arguments
 * @param argv pointer to array of the command-line arguments
 */
int main(int argc, char* argv[]) {
    int specifier = 1;
    // Check if argv[1] is -c or -n and change lines or bytes variable accordingly
    if(argc == 1) {
        commandLine();
    } // if
    if(strcmp(argv[1], "-n") == 0) {
        int num = atoi(argv[2]);
        lines = num;
        specifier = 3;
    } else if(strcmp(argv[1], "-c") == 0) {
        int num = atoi(argv[2]);
        bytes = num;
        specifier = 3;
        status = 1;
    } // if
    // reads from standard input if there is no argument
    if(specifier == 3 && argc == 3) {
        commandLine();
    } else {
    // reads each command-line argument, skipping the specificer if there is one
        for(int i = specifier; i < argc; i++) {
            if(*argv[i] == '-') {
                if(argc > 4) {
                    setbuf(stdout, NULL);
                    if(i != specifier) {
                        printf("\n");
                    } // if
                    printf("==> standard input <==\n");
                } // if
                commandLine();
            } else {
                if(argc > 4 || ((specifier == 1) && (argc > 2))) {
                    setbuf(stdout, NULL);
                    if(i != specifier) {
                        printf("\n");
                    } // if
                    printf("==> %s <==\n", argv[i]);
                } // if
                readFile(i, argv);
            } // if
        } // for
    } // if
} // main

/**
 * Reads the input given in standard input and writes it back to
 * standard output until an error occurs or ctrl-d is pressed.
 */
void commandLine() {
    int n;
    char buffer[bytes];
    char* fullChar = calloc(1000000, sizeof(char));
    int byteCount = 0;
    if(status) {
        // reads standard input and writes it back from bottom for specified char length
        while((n = read(STDIN_FILENO, buffer, 1)) > 0) {
            fullChar[byteCount] = buffer[0];
            byteCount++;
        } // while
        int byteLoc = byteCount - bytes;
        char writeArray[bytes];
        for(int i = 0; i < bytes; i++) {
            writeArray[i] = fullChar[byteLoc];
            byteLoc++;
        } // for
        if(write(STDOUT_FILENO, writeArray, bytes) != bytes) {
            perror("write");
        } // if
        // checks for errors with reading from standard input
        if(n == -1) {
            perror("read");
        } // if
    } else {
        // reads and writes standard input back from bottom with specified line number
        while((n = read(STDIN_FILENO, buffer, 1)) > 0) {
            fullChar[byteCount] = buffer[0];
            byteCount++;
        } // while
        int inc1 = 0;
        int countLines = 0;
        while(fullChar[inc1] != '\0') {
            if (fullChar[inc1] == '\n') {
                countLines++;
            } // if
            inc1++;
        } // while
        int linesWrite = countLines - lines;
        int lineCheck = 0;
        int inc2 = 0;
        while(lineCheck < linesWrite) {
            if(fullChar[inc2] == '\n') {
                lineCheck++;
            } // if
            inc2++;
        } // while
        int writeBytes = inc1 - inc2;
        char writeArray[writeBytes];
        int inc3 = 0;
        while(fullChar[inc2] != '\0') {
            writeArray[inc3] = fullChar[inc2];
            inc3++;
            inc2++;
        } // while
        write(STDOUT_FILENO, writeArray, writeBytes);
        // checks for errors with reading from standard input
        if(n == -1) {
            perror("read");
        } // if
    } // if
    free(fullChar);
} // commandLine

/**
 * Reads a file supplied to the command-line argument and writes
 * it back to standard output.
 *
 * @param i number command-line argument of the file being read
 * @param argv pointer to array of command-line arguments
 */
void readFile(int i, char* argv[]) {
    // opens the file from the command-line argument
    char* filename = argv[i];
    int fd = open(filename, O_RDONLY);
    // checks if an error occured opening the file
    if(fd == -1) {
        perror("open");
    } // if
    int n;
    char* buffer = calloc(1000000, sizeof(char));
    // reads and writes the file back from bottom with specified char length
    if(status) {
        n = read(fd, buffer, 1000000);
        int increment = 0;
        while(buffer[increment] != '\0') {
            increment++;
        } // while
        int bytesWrite = increment - bytes;
        char writeArray[bytes];
        for(int j = 0; j < bytes; j++) {
            writeArray[j] = buffer[bytesWrite];
            bytesWrite++;
        } // for
        write(STDOUT_FILENO, writeArray, bytes);
    } else {
        // reads and writes the file back from bottom with specified line number
        n = read(fd, buffer, 1000000);
        int inc1 = 0;
        int countLines = 0;
        while(buffer[inc1] != '\0') {
            if (buffer[inc1] == '\n') {
                countLines++;
            } // if
            inc1++;
        } // while
        int linesWrite = countLines - lines;
        int lineCheck = 0;
        int inc2 = 0;
        while(lineCheck < linesWrite) {
            if(buffer[inc2] == '\n') {
                lineCheck++;
            } // if
            inc2++;
        } // while
        int writeBytes = inc1 - inc2;
        char writeArray[writeBytes];
        int inc3 = 0;
        while(buffer[inc2] != '\0') {
            writeArray[inc3] = buffer[inc2];
            inc3++;
            inc2++;
        } // while
        write(STDOUT_FILENO, writeArray, writeBytes);
    } // if
    close(fd);
    free(buffer);
    // checks for errors while reading and writing the file
    if(n == -1) {
        close(fd);
    } // if
} // readFile
