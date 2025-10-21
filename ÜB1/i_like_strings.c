#include <stdlib.h>
#include <stdio.h>

int main(int argc, char** argv){
	if (argc != 2) {
		printf("I really need you to provide a single parameter, like this: %s <the parameter comes here>\n", argv[0]);
		return 1;
	}
    char* secret = "secret_api_key_12345";
	(void) secret;
	printf("Wow, thanks! This is my favorite string! Let me repeat it:\n");
	printf(argv[1]);
	printf("\nNice!\n");
	return 0;
}

