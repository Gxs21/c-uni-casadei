#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 20

int string_equals(char* a, char* b);
void print_string(char *a);

/*
Realizzare una funzione `check_pattern(s,template)` che controlla se la stringa è conforme a una stringa template.
La stringa template può contenere caratteri normali, e due caratteri speciali:
- il carattere '?' che può essere sostituito da un qualsiasi carattere
- il carattere '*' che può essere sostituito da una sequenza (anche vuota) di caratteri qualsiasi

Esempi di corrispondenza input/output da ottenere:

Input: "abc", template="a?c" -> Output: true
Input: "abc", template="a*c" -> Output: true
Input: "ac", template="a*c" -> Output: true
Input: "abcbcbc", template="a*bc" -> Output: true
Input: "accc", template="a*c" -> Output: true
Input: "abc", template="a*d" -> Output: false
Input: "abc", template="a?d" -> Output: false

Suggerimento: la parte intricata è la gestione del carattere '*', che può essere sostituito da una sequenza di caratteri di lunghezza qualsiasi.
Si suggerisce di tenere traccia della posizione dell'ultimo '*' incontrato nella template, e della posizione nella stringa che corrisponde a tale '*'.
In questo modo, quando si incontra un carattere che non corrisponde, si può tornare alla posizione successiva a tale '*' nella template,
e alla posizione successiva nella stringa. 

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
int check_pattern(char *s, char *template) {
    return 1; // TODO
}

// STUDENT-SOLUTION-END

int ntot = 0, npassed = 0;
int check(char *s, char *pattern, int expected) {
    ntot++;
    int result = check_pattern(s, pattern);
    int correct = result == expected;
    printf("Test %s: template=\"%s\", input=\"%s\", expected=%s, got=%s\n",
           correct ? "PASSED" : "FAILED", pattern, s, expected ? "TRUE" : "FALSE", result ? "TRUE" : "FALSE");
    if(correct) npassed++;
    return correct;
}

void test() {
    check("abc", "a?c", 1);
    check("abc", "a*c", 1);
    check("ac", "a*c", 1);
    check("abbc", "a*c", 1);
    check("abbbc", "a*b?", 1);
    check("accc", "a*c", 1);
    check("ac", "a*c", 1);
    check("abc", "a*d", 0);
    check("abcbcbc", "a*bc", 1);
    check("abc", "a?d", 0);
    check("abcd", "", 0);
    check("", "*", 1);
    check("", "?", 0);
    check("a", "*", 1);
    check("a", "?", 1);
    check("ab", "*", 1);
    check("ab", "??", 1);
    check("ab", "?*", 1);
    // other false examples
    check("abc", "????", 0);
    check("abc", "a??d", 0);
    check("abc", "a*d*c", 0);
    check("abc", "a*c*d", 0);
    check("abc", "a?*d", 0);
    check("abcd", "a*c", 0);
    check("abcd", "a?c", 0);
    check("abcd", "a?*c", 0);
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
