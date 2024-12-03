#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_LENGTH 100
#define MAX_OPERATORS 50 // Maximum number of operators to store

// Function to check if the character is an operator
int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/' ||
            c == '%' || c == '=' || c == '<' || c == '>' ||
            c == '&' || c == '|' || c == '!');
}

// Function to check if the operator is arithmetic
int isArithmeticOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

// Function to check if the operator is relational
int isRelationalOperator(char c) {
    return (c == '<' || c == '>' || c == '=');
}

// Function to check if the operator is logical
int isLogicalOperator(char c) {
    return (c == '&' || c == '|');
}

int main() {
    FILE *fptr_input = fopen("input.txt", "r");
    FILE *fptr_output = fopen("output.txt", "w");
    char line[MAX_LENGTH];

    // Arrays to store operators
    char arithmeticOperators[MAX_OPERATORS];
    char relationalOperators[MAX_OPERATORS];
    char logicalOperators[MAX_OPERATORS];
	     int i=0;
    int arithmeticCount = 0, relationalCount = 0, logicalCount = 0;

    if (!fptr_input) {
	fprintf(stderr, "Error: Cannot open input file.\n");
	return 1;
    }

    // Read each line from the input file
    while (fgets(line, sizeof(line), fptr_input)) {
	// Check each character in the line
	for (int i = 0; i < strlen(line); i++) {
	    if (isOperator(line[i])) {
		if (isArithmeticOperator(line[i])) {
		    if (arithmeticCount < MAX_OPERATORS) {
			arithmeticOperators[arithmeticCount++] = line[i];
		    }
		} else if (isRelationalOperator(line[i])) {
		    if (relationalCount < MAX_OPERATORS) {
			relationalOperators[relationalCount++] = line[i];
		    }
		} else if (isLogicalOperator(line[i])) {
		    if (logicalCount < MAX_OPERATORS) {
			logicalOperators[logicalCount++] = line[i];
		    }
		}
	    }
	}
    }

    fclose(fptr_input);

    // Write results to output file
    fprintf(fptr_output, "Arithmetic Operators:\n");
    for ( i = 0; i < arithmeticCount; i++) {
	fprintf(fptr_output, "%c ", arithmeticOperators[i]);
    }
    fprintf(fptr_output, "\n\nRelational Operators:\n");
    for ( i = 0; i < relationalCount; i++) {
	fprintf(fptr_output, "%c ", relationalOperators[i]);
    }
    fprintf(fptr_output, "\n\nLogical Operators:\n");
    for ( i = 0; i < logicalCount; i++) {
	fprintf(fptr_output, "%c ", logicalOperators[i]);
    }

    fclose(fptr_output);

    printf("Lexical analysis complete. Results written to 'output.txt'.\n");
	 getchar();
    return 0;
}