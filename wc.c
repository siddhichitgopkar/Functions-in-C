#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define BUFFSIZE 128

/**
 * This is the numBytes method that calculates the number of bytes in a specific file.
 * @param argc and index are the number of arguments and the index of the file.
 * @param argv is the array that contains the arguments.
 * @return int size which is the number of bytes.
 */

int numBytes(int argc, char* argv[], int index) {
//finding the number of bytes
    off_t size = 0; //variable to return number of bytes
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    //counts the number of characters/bytes
    size = lseek(fd, 0, SEEK_END);
    if (size == -1) perror("lseek");
    return size;
} //numBytes

/**
 * This is the numWords method that calculates the number of words in a specific file.
 * @param argc and index are the number of arguments and the index of the file.
 * @param argv is the array that contains the arguments.
 * @return int num_words is the number of words that have been counted in the file.
 */

int numWords(int argc, char* argv[], int index) {
    int num_words = 0; //variable to return number of words
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    int n;
    char buffer[BUFFSIZE]; //buffer that stores everything being read
    while((n = read(fd, buffer, BUFFSIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            //if the character read is a space or a new line character then it indicates a new word
            if ((buffer[i] ==  ' ') || (buffer[i] == '\n')) {
                num_words++;
            } //if
        } //for
    } //while
    return num_words;
} //numWords

/**
 * This is the numLines method that calculates the number of lines in a specific file.
 * @param argc and index are the number of arguments and the index of the file.
 * @param argv is the array that contains the arguments.
 * @return int num_lines which is the number of lines.
 */

int numLines(int argc, char* argv[], int index) {
    int num_lines = 0; //variable that stores the number of lines
    int fd = 0;
    char* filename = argv[index];
    fd = open(filename, O_RDONLY);
    int n;
    char buffer[BUFFSIZE]; //buffer that stores everything being read
    while((n = read(fd, buffer, BUFFSIZE)) > 0) {
        for (int i = 0; i < n; i++) {
            //if the character read is a new line character, it indicates one more line
            if (buffer[i] ==  '\n') {
                num_lines++;
            } //if
        } //for
    } //while
    return num_lines;
} //numLines

/**
 * This is the print method that goes through the command line arguemnts and calls the appropriate
 * methods. It then prints out the appropriate numbers and messages based on the user input.
 * @param argc is the number of arguments.
 * @param argv is the array that contains the arguments.
 */

void print (int argc, char* argv[]) {
    int x;
    int cflag = 0; //flag for numbytes
    int lflag = 0; //flag for numlines
    int wflag = 0; //flag for numwords
    int clwflag = 0; //floag for default/all three

    //if there is only one argument, then assume that standard input will be read and analyzed
    if (argc == 1) {
        int num_lines = 0;
        int size = 0;
        int num_words = 0;
        char buf[BUFFSIZE];
        int y;
        //goes through each of the characters inputted by the user and counts each variable
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

    //checks to see what specifically the user wants based on the characters they have inputted
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

    //based on flags that have been checked, goes through the rest of the args and outputs result
        for (int j = optind; j < argc; j++) {
            int size = 0;
            int num_words = 0;
            int num_lines = 0;
            int fd = 0;
            char* filename = argv[j];
            fd = open(filename, O_RDONLY);
            //if the file is not valid, then the program goes to user input and allows the user to
            //input text and outputs the appropriate values based on their input and the flags
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
            } else { //if the file is valid then the program continues with the files
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

/**
 * This is the main method that calls the print method, which in turn calls the rest of
 * the methods that need to be used based on the user input.
 * @param argc is the number of arguments inputted by the user.
 * @param argv is the array that contains the arguments.
 * @return int based on the success of the program - will print out success by default.
 */

int main(int argc, char* argv[]) {
    print(argc, argv);
} //main
