#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>

#define MAX 100

// Precedence table
char precedenceTable[5][5] = {
    {'>', '>', '<', '<', '>'}, // +
    {'>', '>', '<', '<', '>'}, // -
    {'>', '>', '>', '>', '>'}, // *
    {'<', '<', '<', '<', '='}, // /
    {'>', '>', '>', '>', '>'}, // $
};

char operators[] = "+-*/$"; // Operators in order of precedence

// Get the precedence relationship between two operators
char getPrecedence(char stackTop, char current) {
    int row = strchr(operators, stackTop) - operators;
    int col = strchr(operators, current) - operators;
    return precedenceTable[row][col];
}

// Check if a character is an operator
int isOperator(char c) {
    return strchr(operators, c) != NULL;
}

// Operator Precedence Parsing
void operatorPrecedenceParsing(char *input) {
    char stack[MAX];
    int top = -1;
    int i = 0;

    // Add the start and end markers
    stack[++top] = '$';
    strcat(input, "$");

    printf("Parsing steps:\n");
    printf("%-20s %-20s\n", "Stack", "Input");

    while (1) {
	printf("%-20s %-20s\n", stack, input + i);

	char topOperator = stack[top];
	char currentChar = input[i];

	if (topOperator == '$' && currentChar == '$') {
	    printf("Accepted!\n");
	    break;
	}

	if (!isOperator(currentChar)) {
	    // Push operand directly onto stack
	    stack[++top] = currentChar;
	    i++;
	} else {
	    char precedence = getPrecedence(topOperator, currentChar);

	    if (precedence == '<' || precedence == '=') {
		// Push operator onto stack
		stack[++top] = currentChar;
		i++;
	    } else if (precedence == '>') {
		// Reduce the stack
		while (top > 0 && isOperator(stack[top])) {
		    top--;
		}
		stack[top] = 'E'; // Replace with non-terminal E (expression)
	    } else {
		printf("Error in parsing!\n");
		return;
	    }
	}
    }
}

int main() {
    char input[MAX];
    printf("Enter an expression (only single-digit operands and operators +, -, *, /): ");
    scanf("%s", input);

    operatorPrecedenceParsing(input);
	    getch();
    return 0;
}
