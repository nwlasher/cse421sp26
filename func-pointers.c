#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

// Configurable function, pass in a valid 'print' style function and any additional config data into aux
void myPrint(char *string, void (*print)(const char *, void *aux), void *aux) { // Define a function that takes a string and a function
	(*print)(string, aux); // Call the passed function on the passed string pointer
}

// Type-safe wrapper for the normal printf function, aux is safely unused here
void nPrint(const char *string, void *aux){
	printf("%s\n", string); // Use normal printf
}

// This is a slightly modified print function, that uses aux as a word offset into the string
// adn prints only that word to the stdout.
void sPrint(const char *string, void *aux){
	// Skip passed aproximately (int)*aux spaces and grab all characters until next space or null
	char *copy = strdup((char *)string);
	char *word = strtok(copy, " ");
    
	// Find (int)aux-1th word (since I called it above)
    for (int i = 0; i < (int)aux-1; i++) {
        word = strtok(NULL, " "); // Call on null uses internal pointer of strtok
    }

    // Print if not NULL
    if (word != NULL) {
        printf("%s\n", word);// Print only a portion of te string (second word 'World' in this case)
    }
}

int main(int argc, char *argv[]) {

	char *myString = "Hello World!"; // String variable
	bool f, s = false;
	int config = 0;

	if (argc > 2 && !strcmp(argv[1], "-f")) { // If the option is -d for descending order
		printf("-f detected, printing entire string\n");
		f = true;
	} else if (argc > 3 && !strcmp(argv[1], "-s")) {
		printf("-s detected, skipping %s words into the string provided\n", argv[2]);
		s = true;
		config = atoi(argv[2]); // Setup config data to be the word offset
	} else {
		printf("Usage: ./func-pointers [-f] <words> <in> <the> <string> [-s] <index> <words> ... <string>\n");
		return 0;
	}
	
	

	// Print with either full (f) or selective (s) print function based on flags
	myPrint(myString, (s ? sPrint : nPrint), (void *)config);
	
}


