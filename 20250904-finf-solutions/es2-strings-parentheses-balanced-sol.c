#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 20

int string_equals(char* a, char* b);
void print_string(char *a);

/*
Realizzare una funzione `par_balanced(s)` che controlla se la stringa contiene parentesi correttamente bilanciate.
Esempi di corrispondenza input/output da ottenere:
Input: [{()}] -> Output: true
Input: [()()]{} -> Output: true
Input: (] -> Output: false
Input: ([{]}) -> Output: false

NOTE GENERALI:
*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
*) E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno. 
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
modalità di verifica di competenze (ad es., prove orali) siano attuate.
*/

// STUDENT-SOLUTION-START
int par_balanced(char *s) {
    char stack[MAX_STRING_LENGTH];
    int top = -1;
    for (int i = 0; s[i] != '\0'; i++) {
        char c = s[i];
        if (c == '(' || c == '[' || c == '{') {
            if (top >= MAX_STRING_LENGTH - 1) return 0; // stack overflow
            stack[++top] = c;
        } else if (c == ')' || c == ']' || c == '}') {
            if (top < 0) return 0; // stack underflow
            char open = stack[top--];
            if ((c == ')' && open != '(') ||
                (c == ']' && open != '[') ||
                (c == '}' && open != '{')) {
                return 0; // mismatch
            }
        }
    }
    return top == -1; // true if stack is empty
}

// STUDENT-SOLUTION-END

int ntot = 0, npassed = 0;
int check(char *s, int expected) {
    ntot++;
    int result = par_balanced(s);
    int correct = result == expected;
    printf("Test %s: input=\"%s\", expected=%s, got=%s\n",
           correct ? "PASSED" : "FAILED", s, expected ? "TRUE" : "FALSE", result ? "TRUE" : "FALSE");
    if(correct) npassed++;
    return correct;
}

void test() {
    check("[]", 1);
    check("()", 1);
    check("{}", 1);
    check("[()]", 1);
    check("{[]}", 1);
    check("({[]})", 1);
    check("[{()}]", 1);
    check("[()()]{}", 1);
    check("[(a+b)*c]", 1);
    check("a+(b*c)-{d/e}", 1);
    check("a+((b*c)-{d/e})", 1);
    check("a+[(b*c)-{d/e}]", 1);
    check("", 1);
    check("abc", 1);

    check("[", 0);
    check("]", 0);
    check("(", 0);
    check("}", 0);
    check("(]", 0);
    check("[)", 0);
    check("(}", 0);
    check("([)]", 0);
    check("({)}", 0);
    check("{(})", 0);
    check("([{}])]", 0);
    check("[({})", 0);
    check("((a+b)", 0);
    check("(a+b))", 0);
}

int string_equals(char* a, char* b) {
    if(a!=b && (a == NULL || b == NULL)) return 0;
    return strcmp(a, b) == 0;
}
 

void print_string(char *a) {
    printf("%s\n", a);
}

int main() {
    test();
    printf("Passed %d/%d tests.\n", npassed, ntot);
    return 0;
}
