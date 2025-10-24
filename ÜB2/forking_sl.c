#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    while (1) {
		// Read characters until a newline appears (pressed enter)
		while (1) {
			int c = fgetc(stdin); // Read a character from stdin
			if (c == -1) {
				// On error or End of File, exit
				exit(EXIT_SUCCESS);
			} else if (c == '\n') { // \n is a newline, so the character that is inserted on "Enter"
				break; // if the character was a newline, break out of the inner endless loop and start ls!
			}
			// else: ignore the character
		}
		pid_t pid =fork();
		if (pid == 0)execlp("sl","sl",NULL);
		wait(NULL);
		// TODO fork and exec! Run the sl command and wait for it to finish!
    }

    exit(EXIT_SUCCESS);
}
