#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <conio.h>

#define MAX 10

char productions[MAX][MAX], firstSets[MAX][MAX][MAX];
int numProductions;

int isTerminal(char symbol) {
    return !(symbol >= 'A' && symbol <= 'Z');
}

int containsEpsilon(char set[MAX][MAX]) {
    for (int i = 0; set[i][0] != '\0'; i++) {
	if (strcmp(set[i], "null") == 0) return 1;
    }
    return 0;
}

void addToFirstSet(char nonTerminal, char *symbol) {
    for (int i = 0; i < MAX; i++) {
	if (firstSets[nonTerminal - 'A'][i][0] == '\0') {
	    strcpy(firstSets[nonTerminal - 'A'][i], symbol);
	    break;
	}
	if (strcmp(firstSets[nonTerminal - 'A'][i], symbol) == 0) break;
    }
}

void mergeFirstSets(char target, char source[MAX][MAX]) {
    for (int i = 0; source[i][0] != '\0'; i++) {
	addToFirstSet(target, source[i]);
    }
}

void findFirst(char symbol) {
    if (isTerminal(symbol)) return;

    for (int i = 0; i < numProductions; i++) {
	if (productions[i][0] == symbol) {
	    char *rhs = productions[i] + 3;
	    if (isTerminal(rhs[0])) {
		char str[2] = {rhs[0], '\0'};
		addToFirstSet(symbol, str);
	    } else {
		findFirst(rhs[0]);
		mergeFirstSets(symbol, firstSets[rhs[0] - 'A']);
		int j = 0;
		while (rhs[j] != '\0' && containsEpsilon(firstSets[rhs[j] - 'A'])) {
		    j++;
		    if (rhs[j] == '\0') {
			addToFirstSet(symbol, "null");
		    } else if (isTerminal(rhs[j])) {
			char str[2] = {rhs[j], '\0'};
			addToFirstSet(symbol, str);
			break;
		    } else {
			findFirst(rhs[j]);
			mergeFirstSets(symbol, firstSets[rhs[j] - 'A']);
		    }
		}
	    }
	}
    }
}

int main() {
    int i, j;
    char nonTerminals[MAX], input[MAX];
    int visitedNonTerminals[MAX] = {0};
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    printf("Enter the productions (format A->B, null for epsilon):\n");
    for (i = 0; i < numProductions; i++) {
	scanf("%s", productions[i]);
	nonTerminals[i] = productions[i][0];
    }

    for (i = 0; i < numProductions; i++) {
	if (!visitedNonTerminals[nonTerminals[i] - 'A']) {
	    findFirst(nonTerminals[i]);
	    visitedNonTerminals[nonTerminals[i] - 'A'] = 1;
	}
    }

    printf("\nFirst sets for all non-terminals:\n");
    for (i = 0; i < numProductions; i++) {
	char nonTerminal = nonTerminals[i];
	if (visitedNonTerminals[nonTerminal - 'A']) {
	    printf("First(%c) = { ", nonTerminal);
	    for (j = 0; firstSets[nonTerminal - 'A'][j][0] != '\0'; j++) {
		printf("%s ", firstSets[nonTerminal - 'A'][j]);
	    }
	    printf("}\n");
	    visitedNonTerminals[nonTerminal - 'A'] = 0;
	}
    }
    getch();
    return 0;
}
