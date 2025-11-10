#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool laughed = false;

char *laugh(int laugh_length) {
	// "ha" * laugh_length + '\0' byte
	char *ptr = (char *) malloc(sizeof(char) * 2 * laugh_length + 1); 
	for (int i = 0; i < 2 * laugh_length; i+=2) {
		ptr[i] = 'h';
		ptr[i+1] = 'a';
		ptr[i+2] = '\0';//wird übershrieben
	}
	laughed = true;
	return ptr;
}

int main() {
	puts("Press enter to make me laugh!");
	char *laugh_str = NULL;
	int laughs = 1;
	
	while (fgetc(stdin) != -1) {
		laugh_str = laugh(laughs++);
		printf("%s", laugh_str);
		free(laugh_str);
	}
	printf("\n");
	return 0;
}
