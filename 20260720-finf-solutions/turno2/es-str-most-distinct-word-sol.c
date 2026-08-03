#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

int array_equals(char *a, char *b, int sizea, int sizeb);

/*
Realizzare una funzione `char *most_distinct_word(char *s)` tale che:

* in input, accetti:
    1. una stringa `s` NULL-terminata contenente una frase composta da parole
       formate da lettere minuscole e separate da un singolo spazio
* in output, restituisca:
    * un puntatore ad una nuova stringa contenente la parola della frase con il
      maggior numero di caratteri distinti

Un carattere deve essere contato una sola volta, indipendentemente dal numero
di volte in cui compare nella stessa parola.

In caso di piu' parole con lo stesso numero massimo di caratteri distinti, deve
essere restituita la prima parola che compare nella frase.

Se la stringa di input e' vuota, la funzione deve restituire una nuova stringa
vuota.

Si consideri il seguente esempio:

   most_distinct_word("casa automobile tetto")

La parola "casa" contiene 3 caratteri distinti (`c`, `a`, `s`), la parola
"automobile" ne contiene 9 e la parola "tetto" ne contiene 3 (`t`, `e`, `o`).

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

void reset_flags(int *flags){
    for(int i = 0; i < 26; i++){
        flags[i]= 0;
    }
}

void copy_in_result(char *s, char *result, int start_i){
    int size = 0;

    for(int i = start_i; s[i] != '\0' && s[i] != ' '; i++){
        result[size] = s[i];
        size++;
    }
    result[size] = '\0';
}

int count_flags(int *flags){
    int count = 0;
    for(int i = 0; i < 26; i++){
        if(flags[i]){
            count++;
        }
    }
    return count; 
}

void print_flags(int *flags){
    for(int i = 0; i < 26; i++){
        printf("%d ", flags[i]);
    }
    printf("\n");
}

char *most_distinct_word(char *s) {
    if(s == NULL || s[0] == '\0'){
        return strdup("");
    } 

    int flags[26] = {0};
    char *result = (char*) malloc(sizeof(char) * (strlen(s) + 1));
    
    int temp_max = -1;
    int word_start = 0;

    for(int i = 0; s[i] != '\0'; i++){
        if(s[i] != ' '){
            flags[s[i] - 'a'] = 1;
        }

        if(s[i] == ' ' || s[i + 1] == '\0'){
            int n_diff_chars = count_flags(flags);
            if(n_diff_chars > temp_max){
                copy_in_result(s, result, word_start);
                temp_max = n_diff_chars;
            }
            word_start = i + 1;
            reset_flags(flags);
        }
    }

    return result;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char *input, char *attended_result){
    char *actual_result = most_distinct_word(input);
    int correct = (actual_result == NULL && attended_result == NULL)
        || (actual_result != NULL && strcmp(actual_result, attended_result) == 0);

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
    check("Reference example", "casa automobile tetto", "automobile");

    // Le ripetizioni dello stesso carattere non aumentano il conteggio
    check("Repeated characters", "aaaa abca banana", "abca");

    // In caso di parita' viene scelta la prima parola
    check("Tie: choose first word", "cane pera luna", "cane");

    // Una parola con tutti i caratteri differenti
    check("All distinct characters", "mamma quadro tetto", "quadro");

    // Una sola parola
    check("Single word", "elettronica", "elettronica");

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
