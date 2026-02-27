#include <stdio.h>
#include <stdbool.h>
#include <string.h>

void myPrint(char *string, void (*print)(const char *)) { // Define a function that takes a string and a function
	(*print)(string); // Call the passed function on the passed string pointer
}

void nPrint(const char *string){
	printf("%s\n", string); // Use normal printf
}

void sPrint(const char *string){
	printf("%s\n", (string+6)); // Print only a portion of te string (second word 'World' in this case)
}

int main(int argc, char *argv[]) {

	char *myString = "Hello World!"; // String variable
	bool f, s = false;

	if (argc > 1 && !strcmp(argv[1], "-f")) { // If the option is -d for descending order
		printf("-f detected\n");
		f = true;
	} else if (argc > 1 && !strcmp(argv[1], "-s")) {
		printf("-s detected\n");
		s = true;
	} else {
		printf("Usage: ./func-pointers [-d] [-a] ; For ascending or descending order\n");
		return 0;
	}

	// Print with either full (f) or selective (s) print function based on flags
	myPrint(myString, (s ? sPrint : nPrint));
	
}


