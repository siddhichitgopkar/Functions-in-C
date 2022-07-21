#include <stdio.h>

/**
 * This is the main methof that contains the code for the env function. This function replicates
 * the features of the env function on odin and outputs information about the environment the user
 * is in.
 * @param argc is the number of arguements.
 * @param argv is the array containing the arguments.
 * @param envp is the array contianing information about the environment.
 * @return int to see if it has been successful (does this automatically by default).
 */


int main(int argc, char* argv[], char* envp[])
{
	char* seperator = "************************\n"; //separator to help with formatting output
	printf(seperator);
    //prints all contents about the environment with seperator between so it is more organized
	for (int i = 0; i < argc; i++) printf("%s\n", argv[i]);
	printf(seperator);
	for (int i = 0; argv[i] != NULL; i++) printf("%s\n", argv[i]);
	printf(seperator);
	for (int i = 0; envp[i] != NULL; i++) printf("%s\n", envp[i]);
} // main
