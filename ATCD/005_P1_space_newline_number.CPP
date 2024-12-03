#include <stdio.h>
						 //PRACTICAL1
int main() {
    FILE *fptr_input, *fptr_output;
    int space_count = 0, tab_count = 0, newline_count = 0;
    char filename[100];
    char c;

    // Prompt user for input file name
    printf("Enter the input file name: ");
    scanf("%s", filename);

    // Open the input file for reading
    fptr_input = fopen(filename, "r");
    if (fptr_input == NULL) {
        fprintf(stderr, "Error: Cannot open input file '%s'.\n", filename);
        return 1;
    }

    // Read characters from the input file and count spaces, tabs, and newlines
    while ((c = fgetc(fptr_input)) != EOF) {
        if (c == ' ') {
            space_count++;
        } else if (c == '\t') {
            tab_count++;
        } else if (c == '\n') {
            newline_count++;
        }
    }

    // Close the input file
    fclose(fptr_input);

    // Open the output file for writing
    fptr_output = fopen("output.txt", "w");
    if (fptr_output == NULL) {
        fprintf(stderr, "Error: Cannot open output file 'output.txt'.\n");
        return 1;
    }

    // Write the counts to the output file
    fprintf(fptr_output, "Number of spaces: %d\n", space_count);
    fprintf(fptr_output, "Number of tabs: %d\n", tab_count);
    fprintf(fptr_output, "Number of newlines: %d\n", newline_count);

    // Close the output file
    fclose(fptr_output);

    // Confirmation message
    printf("Counting complete. Results written to 'output.txt'.\n");
    
    return 0;
}
