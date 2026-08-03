#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(char *a, char *b, int sizea, int sizeb);

/*
Realizzare una funzione `char *compress_string(char *s, int n, int value, int *size_result)` tale che:

* in input, accetti:
    1. un array `s` di `n` caratteri 
    2. un intero `value` che indica il numero minimo di occorrenze consecutive di un carattere per essere compresso
    3. un puntatore a intero `size_result` (passato per riferimento) in cui scrivere la dimensione della stringa restituita
* in output, restituisca 
    * Un puntatore ad una nuova stringa ottenuta comprimendo solo le sequenze consecutive dello stesso carattere lunghe almeno value. 
      Una sequenza compressa va scritta come carattere seguito dal numero di occorrenze. 
      Le sequenze piu' corte restano invariate.
    * Riempire `size_result` con la dimensione della stringa restituita.
    * ATTENZIONE: Si assuma che le sequenze di caratteri da comprimere non superino le 9 occorrenze.

Si consideri il seguente esempio:

   compress_string("aaabbc", 6, 3, &size_result)

Ci si attende come valore di ritorno il puntatore alla nuova stringa "a3bbc" e come valore di `size_result` il numero 5, 
che è la lunghezza della stringa restituita.
Si noti che la sequenza "aaa" è stata compressa in "a3" perché ha una lunghezza di 3, che è maggiore o uguale a `value`, 
mentre la sequenza "bb" è rimasta invariata perché ha una lunghezza di 2, che è inferiore a `value`.

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
char *compress_string(char *s, int n, int value, int *size_result) {
    return NULL;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char* input, int n, int value, char* attended_result, int size_attended_result){
    int size_actual_result = 0;
    char* actual_result = compress_string(input, n, value, &size_actual_result);
    int correct = array_equals(attended_result, actual_result, size_attended_result, size_actual_result) && size_attended_result == size_actual_result;
    printf("\n### TEST: %s\n\n", test_name);
    printf("Input value: %d\n", value);
    printf("Input string: \"%s\"\n", input);
    printf("Return string: expected = \"%s\", actual = \"%s\"\n", attended_result, actual_result);
    printf("Return string size: expected = %d, actual = %d\n", size_attended_result, size_actual_result);
    if (correct) {
        printf("TEST PASSED\n");
        tests_success++;
    } else {
        printf("TEST FAILED\n");
    }
    puts("");
    tests++;
    return correct;
}

int array_equals(char *a, char *b, int sizea, int sizeb){
    if((a == NULL || b == NULL) && a!=b) return FALSE;
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}


void test(){
    // Test delle istruzioni
    check("Reference example", "aaabbc", 6, 3, "a3bbc", 5);
    check("Reference example variant", "aaabbc", 6, 2, "a3b2c", 5);
    check("No compression", "abcd", 4, 2, "abcd", 4);
    check("Empty string", "", 0, 2, "", 0);
    check("All characters the same", "aaaaaa", 6, 2, "a6", 2);

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}