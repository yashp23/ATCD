#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

// Function declarations
int isKeyword(const char* str);
int isDelimiter(char ch);
int isOperator(char ch);
int validIdentifier(const char* str);
int isConstant(const char* str);
int isFunction(const char* str);
int isIdentifier(const char* str);
int isPreprocessorDirective(const char* str);

FILE *fptr_input;
FILE *fptr_output;

// Function to check if a string is a keyword
int isKeyword(const char* str) {
    const char* keywords[] = {
        "if", "else", "while", "do", "break", "continue", "int",
        "double", "float", "return", "char", "case", "sizeof",
        "long", "short", "typedef", "switch", "unsigned", "void",
        "static", "struct", "goto", "fopen"
    };
    size_t keywordCount = sizeof(keywords) / sizeof(keywords[0]);

    for (size_t i = 0; i < keywordCount; i++) {
        if (strcmp(str, keywords[i]) == 0) {
            return 1; // true
        }
    }
    return 0; // false
}

// Function to check if a character is a delimiter
int isDelimiter(char ch) {
    const char delimiters[] = " +-*/;,><=()[]{}#$!@|\"\n\t";
    return strchr(delimiters, ch) != NULL;
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return strchr("+-*/><=", ch) != NULL;
}

// Function to check if a string is a valid identifier
int validIdentifier(const char* str) {
    // Identifier cannot start with a digit
    if (str[0] >= '0' && str[0] <= '9') {
        return 0; // false
    }
    // Identifier cannot start with a delimiter
    if (isDelimiter(str[0])) {
        return 0; // false
    }
    return 1; // true
}

// Function to check if a string is a constant (numeric literal)
int isConstant(const char* str) {
    // Check if the string is a valid number (integer or floating-point)
    char* endptr;
    strtod(str, &endptr); // Try to convert the string to a double

    return (*endptr == '\0'); // If the whole string is a number, it is a valid constant
}

// Function to check if a string is a function name
int isFunction(const char* str) {
    return strchr(str, '(') != NULL && strchr(str, ')') != NULL;
}

// Function to check if a string is an identifier
int isIdentifier(const char* str) {
    // An identifier must not be a keyword, a function name, or start with a delimiter
    return validIdentifier(str) && !isKeyword(str) && !isFunction(str);
}

// Function to check if the string is a preprocessor directive
int isPreprocessorDirective(const char* str) {
    return str[0] == '#'; // Checks if the string starts with #
}

// Main function
int main() {
int j=0;
    // Open the input file
    fptr_input = fopen("input.txt", "r");
    if (fptr_input == NULL) {
        fprintf(stderr, "Error: Cannot open input file 'input.txt'.\n");
        return 1;
    }

    // Open the output file
    fptr_output = fopen("output.txt", "w");
    if (fptr_output == NULL) {
        fprintf(stderr, "Error: Cannot open output file 'output.txt'.\n");
        fclose(fptr_input);
        return 1;
    }

    char FileContent[1000];
    
    // Arrays to store tokens for each category
    char keywords[100][100];     // Array for keywords
    char identifiers[100][100];   // Array for identifiers
    char constants[100][100];     // Array for constants

    int keywordCount = 0;
    int identifierCount = 0;
    int constantCount = 0;

    // Read and parse the input file line by line
    while (fgets(FileContent, sizeof(FileContent), fptr_input) != NULL) {
	int i = 0;
	int j=0;
	char token[100]; // To store the current token
	int tokenIndex = 0;

	// Process each character in the line
	while (FileContent[i] != '\0') {
	    // Ignore preprocessor directives
	    if (isPreprocessorDirective(&FileContent[i])) {
		break; // Skip the rest of the line if it's a preprocessor directive
	    }

	    if (isDelimiter(FileContent[i])) {
		// If a delimiter is found, process the token before it
		if (tokenIndex > 0) {
		    token[tokenIndex] = '\0';

		    // Check if the token is a keyword, constant, or identifier and store it accordingly
		    if (isKeyword(token)) {
			strcpy(keywords[keywordCount++], token);
		    } else if (isConstant(token)) {
			strcpy(constants[constantCount++], token);
		    } else if (isIdentifier(token)) {
			strcpy(identifiers[identifierCount++], token);
		    }
		    tokenIndex = 0; // Reset token
		}

		// Check if the delimiter itself is meaningful (operator)
		if (!isspace(FileContent[i])) {
		    if (isOperator(FileContent[i])) {
			fprintf(fptr_output, "Operator: %c\n", FileContent[i]);
		    }
		}
	    } else {
		// If not a delimiter, add character to token
		token[tokenIndex++] = FileContent[i];
	    }
	    i++;
	}

	// Process the last token in the line if it exists
	if (tokenIndex > 0) {
	    token[tokenIndex] = '\0';
	    if (isKeyword(token)) {
		strcpy(keywords[keywordCount++], token);
	    } else if (isConstant(token)) {
		strcpy(constants[constantCount++], token);
	    } else if (isIdentifier(token)) {
		strcpy(identifiers[identifierCount++], token);
	    }
	}
    }

    // Write results to output file in grouped order: Keywords -> Identifiers -> Constants

    fprintf(fptr_output, "Keywords:\n");
    for ( j = 0; j < keywordCount; j++) {
	fprintf(fptr_output, "%s\n", keywords[j]);
    }

    fprintf(fptr_output, "\nIdentifiers:\n");
    for ( j = 0; j < identifierCount; j++) {
	fprintf(fptr_output, "%s\n", identifiers[j]);
    }

    fprintf(fptr_output, "\nConstants:\n");
    for ( j = 0; j < constantCount; j++) {
	fprintf(fptr_output, "%s\n", constants[j]);
    }

    // Close files
    fclose(fptr_input);
    fclose(fptr_output);

    printf("Parsing complete. Results written to 'output.txt'.\n");
getchar();
    return 0;
}