#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>
// Define states for both DFAs
#define Q0 0 // Start state
#define Q1 1 // After reading first 'a'
#define Q2 2 // After reading (a|b)* part
#define Q3 3 // After reading 'ab', the accept state

// Function to print DFA table for a(a|b)*ab
void printDFATable1() {
    printf("\nDFA Table for a(a|b)*ab:\n");
    printf("+---------+-------+-------+\n");
    printf("| State   |   a   |   b   |\n");
    printf("+---------+-------+-------+\n");
    for (int state = Q0; state <= Q3; state++) {
	printf("|   Q%d    ", state);
	if (state == Q0)
	    printf("|   Q1   |   Q0   |\n"); // Q0 -> Q1 for 'a', stays at Q0 for others
	else if (state == Q1)
	    printf("|   Q2   |   Q2   |\n"); // Q1 -> Q2 for 'a' or 'b'
	else if (state == Q2)
	    printf("|   Q2   |   Q3   |\n"); // Q2 -> Q2 for (a|b)*, Q2 -> Q3 for 'b'
	else
	    printf("|   Q3   |   Q3   |\n"); // Q3 is a final accepting state
    }
    printf("+---------+-------+-------+\n");
}

// Function to print DFA table for digit(digit)*(.digit(digit)*|ε)
void printDFATable2() {
    printf("\nDFA Table for digit(digit)*(.digit(digit)*|ε):\n");
    printf("+---------+------------+------------+\n");
    printf("| State   |   digit    |     .      |\n");
    printf("+---------+------------+------------+\n");
    for (int state = Q0; state <= Q3; state++) {
	printf("|   Q%d    ", state);
	if (state == Q0)
	    printf("|   Q1     |     -      |\n"); // Q0 -> Q1 for 'digit', no transition for '.'
	else if (state == Q1)
	    printf("|   Q1     |   Q2      |\n"); // Q1 -> Q1 for more digits, Q1 -> Q2 for '.'
	else if (state == Q2)
	    printf("|   Q3     |     -      |\n"); // Q2 -> Q3 for more digits after '.' (decimal)
	else
	    printf("|   Q3     |     -      |\n"); // Q3 stays at Q3 (accepting state for decimal part)
    }
    printf("+---------+------------+------------+\n");
}

// DFA 1: For a(a|b)*ab
int simulateDFA1(char *input) {
    int currentState = Q0;
    int len = strlen(input);

    // Process each character of the input string
    for (int i = 0; i < len; i++) {
	char symbol = input[i];

	switch (currentState) {
	    case Q0: // Start state
		if (symbol == 'a') {
		    currentState = Q1; // Move to Q1 after 'a'
		} else {
		    currentState = Q0; // Stay at Q0 if not 'a'
		}
		break;
	    case Q1: // After 'a'
		if (symbol == 'a' || symbol == 'b') {
		    currentState = Q2; // Move to Q2 after (a|b)
		}
		break;
	    case Q2: // After (a|b)*
		if (symbol == 'a' || symbol == 'b') {
		    currentState = Q2; // Stay in Q2 for (a|b)*
		} else if (symbol == 'b') {
		    currentState = Q3; // Move to final accepting state Q3 when we get 'ab'
		}
		break;
	    case Q3: // Accepting state
		currentState = Q3; // Stay in Q3 for 'ab' transition
		break;
	}
    }

    return currentState == Q3; // Accept if we end at Q3 (final state)
}

// Function to simulate DFA for digit(digit)*(.digit(digit)*|ε)
int simulateDFA2(char *input) {
    int currentState = Q0;
    int len = strlen(input);

    // Process each character of the input string
    for (int i = 0; i < len; i++) {
	char symbol = input[i];

	switch (currentState) {
	    case Q0: // Start state, expect digit
		if (isdigit(symbol)) {
		    currentState = Q1; // Move to Q1 if digit
		} else {
		    return 0; // Reject if not a digit
		}
		break;
	    case Q1: // Integer part, expect digit or '.'
		if (isdigit(symbol)) {
		    currentState = Q1; // Stay in Q1 for more digits
		} else if (symbol == '.') {
		    currentState = Q2; // Transition to decimal point state
		} else {
		    return 0; // Reject if not a digit or '.'
		}
		break;
	    case Q2: // After '.', expect digit
		if (isdigit(symbol)) {
		    currentState = Q3; // Move to Q3 after decimal part
		} else {
		    return 0; // Reject if not a digit after '.'
		}
		break;
	    case Q3: // After decimal point, expect digit
		if (isdigit(symbol)) {
		    currentState = Q3; // Stay in Q3 for more decimal digits
		} else {
		    return 0; // Reject if not a digit
		}
		break;
	}
    }

    // Accept if we end in Q1 (integer) or Q3 (decimal)
    return currentState == Q1 || currentState == Q3;
}

int main() {
    char input[100];
    int choice;

    // Prompt user for choice of DFA
    printf("Choose which DFA to simulate:\n");
    printf("1. a(a|b)*ab\n");
    printf("2. digit(digit)*(.digit(digit)*|ε)\n");
    printf("Enter your choice (1 or 2): ");
    scanf("%d", &choice);

    // Print the DFA table
    if (choice == 1)
	printDFATable1();
    else if (choice == 2)
	printDFATable2();
    else {
	printf("Invalid choice! Please select either 1 or 2.\n");
	return 0;
    }

    // Prompt for input string
    printf("\nEnter the input string: ");
    scanf("%s", input);

    // Simulate based on user's choice
    if (choice == 1) {
	if (simulateDFA1(input))
	    printf("Input matches R.E. a(a|b)*ab\n");
	else
	    printf("Input does NOT match R.E. a(a|b)*ab\n");
    } else if (choice == 2) {
	if (simulateDFA2(input))
	    printf("Input matches R.E. digit(digit)*(.digit(digit)*|ε)\n");
	else
	    printf("Input does NOT match R.E. digit(digit)*(.digit(digit)*|ε)\n");
    }
	 getch();
    return 0;
}
