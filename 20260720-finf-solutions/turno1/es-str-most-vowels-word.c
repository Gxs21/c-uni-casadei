#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int array_equals(char *a, char *b, int sizea, int sizeb);

/*
Realizzare una funzione `char *most_vowels_word(char *s)` tale che:

* in input, accetti:
    1. una stringa `s`  NULL-terminata contenente una frase composta da parole
       formate da lettere minuscole e separate da un singolo spazio
* in output, restituisca:
    * un puntatore ad una nuova stringa contenente la parola della frase con il
      maggior numero totale di vocali

Le vocali sono i caratteri `a`, `e`, `i`, `o`, `u`. Occorrenze ripetute della
stessa vocale devono essere contate piu' volte.

In caso di piu' parole con lo stesso numero massimo di vocali, deve essere
restituita la prima parola che compare nella frase.

Se la stringa di input e' vuota, la funzione deve restituire una nuova stringa
vuota.

Si consideri il seguente esempio:

   most_vowels_word("casa automobile treno")

La parola "casa" contiene 2 vocali, "automobile" ne contiene 6 e "treno" ne
contiene 2.

Ci si attende quindi come valore di ritorno la nuova stringa "automobile".


NOTE GENERALI:
*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sara' considerato durante la valutazione.
*) E' possibile definire piu' funzioni ausiliarie qualora lo si ritenga opportuno.
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verra' confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo e' resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarita' importanti, e' possibile che la prova possa venire annullata, e che ulteriori
modalita' di verifica di competenze (ad es., prove orali) siano attuate.
*/
// STUDENT-SOLUTION-START

char *most_vowels_word(char *s) {
    return NULL; // TODO: implement the function
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char *input, char *attended_result){
    char *actual_result = most_vowels_word(input);
    int correct = (actual_result==NULL && attended_result==NULL) || (actual_result != NULL && strcmp(actual_result, attended_result) == 0);

    printf("\n### TEST: %s\n\n", test_name);
    printf("Input string: \"%s\"\n", input);
    printf("Return string: expected = \"%s\", actual = \"%s\"\n",
        attended_result, actual_result == NULL ? "NULL" : actual_result);

    if (correct) {
        printf("TEST PASSED\n");
        tests_success++;
    } else {
        printf("TEST FAILED\n");
    }

    free(actual_result);
    puts("");
    tests++;
    return correct;
}

int array_equals(char *a, char *b, int sizea, int sizeb){
    if((a == NULL || b == NULL) && a != b) return FALSE;
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}

void test(){
    // Test delle istruzioni
    check("Reference example", "casa automobile treno", "automobile");

    // La stessa vocale viene contata piu' volte
    check("Repeated vowels", "cane banana kiwi", "banana");

    // In caso di parita' viene scelta la prima parola
    check("Tie: choose first word", "mare sole luna", "mare");

    // Parole senza vocali
    check("No vowels", "rhythm gym", "rhythm");

    // Una sola parola
    check("Single word", "informatica", "informatica");

    // Ultima parola è quella con più vocali
    check("Last word has most vowels", "casa treno automobile", "automobile");

    // Stringa vuota
    check("Empty string", "", "");

    // NULL input
    check("NULL input", NULL, "");

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n",
        tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}
