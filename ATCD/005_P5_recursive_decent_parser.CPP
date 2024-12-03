#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>  // Include this header to use exit()
#include <conio.h>

const char *input;  // Input string
int index = 0;      // Current index in input

// Function prototypes
void P();
void E();
void T();
void S();
void F();
void D();
void match(char expected);
void error(const char *msg);
void printAction(const char *action);

// Function to print the parsing action
void printAction(const char *action) {
    printf("%s\n", action);
}

// Function to check if the current character matches the expected character
void match(char expected) {
    if (input[index] == expected) {
	printf("Matched '%c'\n", expected);
	index++;
    } else {
	error("Unexpected character");
    }
}

// Error handling function
void error(const char *msg) {
    printf("Error: %s at '%c'\n", msg, input[index]);
    exit(1);  // Properly exit the program on error
}

// P -> E '#'
void P() {
    printAction("P -> E #");
    E();
    match('#'); // Match the end symbol '#'
}

// E -> T E'
void E() {
    printAction("E -> T E'");
    T();
    while (input[index] == '+' || input[index] == '-') {
	if (input[index] == '+') {
	    printAction("E' -> + T E'");
	    match('+');
	    T();
	} else {
	    printAction("E' -> - T E'");
	    match('-');
	    T();
	}
    }
}

// T -> S T'
void T() {
    printAction("T -> S T'");
    S();
    while (input[index] == '*' || input[index] == '/') {
	if (input[index] == '*') {
	    printAction("T' -> * S T'");
	    match('*');
	    S();
	} else {
	    printAction("T' -> / S T'");
	    match('/');
	    S();
	}
    }
}

// S -> F '^' S | F
void S() {
    printAction("S -> F");
    F();
    if (input[index] == '^') {
	printAction("S -> F ^ S");
	match('^');
	S();
    }
}

// F -> D | '(' E ')'
void F() {
    if (isdigit(input[index])) { // Check for digits
	printAction("F -> D");
	D();
    } else if (input[index] == '(') { // Check for '('
	printAction("F -> ( E )");
	match('(');
	E();
	match(')');
    } else {
	error("Expected digit or '('");
    }
}

// D -> 0 | 1 | ... | 9
void D() {
    if (isdigit(input[index])) {
	printAction("D -> digit");
	match(input[index]); // Match the digit
    } else {
	error("Expected digit");
    }
}

int main() {
    printf("Enter the string: ");
    char str[100];
    scanf("%s", str);

    input = str; // Set input string

    printf("\nParsing actions:\n");

    // Start parsing from the start symbol P
    P();  // Start parsing with P

    if (input[index] == '\0') { // Check if the entire string has been consumed
	printf("\nString is successfully parsed.\n");
    } else {
	error("Extra input after parsing");
    }
     getch();
    return 0;
}
