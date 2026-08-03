#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(char *a, char *b, int sizea, int sizeb);

/*
Realizzare una funzione `char *decompress_string(char *s, int n, int *size_result)` tale che:

* in input, accetti:
    1. un array `s` di `n` caratteri contenente una stringa compressa
    2. un puntatore a intero `size_result` (passato per riferimento) in cui scrivere la dimensione della stringa restituita
* in output, restituisca 
    * Un puntatore ad una nuova stringa ottenuta decomprimendo le sequenze compresse.
      Una sequenza compressa è scritta come carattere seguito da una cifra numerica.
      Il carattere va quindi ripetuto tante volte quanto indicato dalla cifra.
      I caratteri non seguiti da una cifra restano invariati.
    * Riempire `size_result` con la dimensione della stringa restituita.

Si consideri il seguente esempio:

   decompress_string("a3bbc", 5, &size_result)

Ci si attende come valore di ritorno il puntatore alla nuova stringa "aaabbc" e come valore di `size_result` il numero 6, che è la lunghezza della stringa restituita.


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
char *decompress_string(char *s, int n, int *size_result) {
    return NULL;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char* input, int n, char* attended_result, int size_attended_result){
    int size_actual_result = 0;
    char* actual_result = decompress_string(input, n, &size_actual_result);
    int correct = array_equals(attended_result, actual_result, size_attended_result, size_actual_result) && size_attended_result == size_actual_result;
    printf("\n### TEST: %s\n\n", test_name);
    printf("Input string: \"%s\"", input);
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
    check("Reference example", "a3bbc", 5, "aaabbc", 6);
    check("Reference example variant", "a3b2c", 5, "aaabbc", 6);
    check("No decompression", "abcd", 4, "abcd", 4);
    check("Empty string", "", 0, "", 0);
    check("All characters the same", "a6", 2, "aaaaaa", 6);

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}