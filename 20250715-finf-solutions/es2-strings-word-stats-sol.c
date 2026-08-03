#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
Si realizzi una funzione `word_stats(s, longest_str)` che, dati in ingresso 

* una stringa `s` qualsiasi,
* un puntatore di puntatore carattere `longest_str` (che ospiterà il puntatore a una stringa in output)

restituisca come risultati:
 
 - il numero di "parole" contenute nella stringa (dove una "parola" è intesa come sequenza di lettere separata da caratteri non lettera)
 - la parola più lunga (da allocare e restituire mediante il puntatore `longest_str`)

Note

- a parità di lunghezza, va data priorità alla stringa che viene *dopo* nella stringa

Esempio:

- word_stats("ecco una stringa", &ls) deve restituire 3 (in quanto ci sono tre parole "ecco", "una" e "stringa") e
 ls deve puntare a una copia stringa "stringa" (che è la più lunga), allocata dinamicamente all'interno della funzione.

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
int is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}   

int letter_stats(const char* string, char **longest_str) {
    int num_words = 0;
    int max_length = 0;
    char *longest_word = NULL;

    int wstart = -1;
    int wend = -1;
    for (int i = 0; string[i] != '\0'; i++) {
        if (is_letter(string[i])) {
            // we might be in a new word or the current word
            if(wend == -1 || wend < i-1) { // new word
                wstart = i; // start of a new word
            }
            wend = i;
        }
        if(!is_letter(string[i]) || string[i+1] == '\0') {
            printf("[%d]", i);
            // we might be at the end of a word or within a non-letter sequence
            if(i == 0 || (i > 0 && !is_letter(string[i-1]))) {
                continue; // still in non-letter sequence
            } else {
                // we are at the end of a word
                if (wstart != -1 && wend != -1) {
                    int word_length = wend - wstart + 1;
                    num_words++;
                    if (word_length >= max_length) {
                        max_length = word_length;
                        if (longest_word != NULL) {
                            free(longest_word);
                        }
                        longest_word = (char*)malloc(word_length + 1);
                        strncpy(longest_word, &string[wstart], word_length);
                        longest_word[word_length] = '\0'; // null-terminate the string
                    } 
                }
                wstart = -1; // reset for next word
                wend = -1; // reset for next word
            }
        }
    }

    *longest_str = longest_word;
    return num_words;
}
// STUDENT-SOLUTION-END

int ntests = 0;
int nsucc_tests = 0;

void test(char *title, char* input, int num_words_exp, char* longest_str_exp) {
    printf("### Test: %s\n", title);
    char* longest_str_actual = '\0';
    int num_words_present = letter_stats(input, &longest_str_actual);
    printf("Input: `%s`\n", input);
    printf("Expected return: %d. Actual return: %d\n", num_words_exp, num_words_present);
    printf("Expected longest string: \"%s\". Actual: \"%s\"\n", longest_str_exp, longest_str_actual);
    int success = (num_words_present == num_words_exp) &&
                  ((longest_str_actual != NULL && longest_str_exp != NULL && strcmp(longest_str_actual, longest_str_exp) == 0) || 
                    (longest_str_actual == NULL && longest_str_exp == NULL));
    printf("Success: %s\n\n", success ? "YES" : "NO");    
    ntests++;
    nsucc_tests += success;
    if(longest_str_actual != NULL) {
        free(longest_str_actual);
    }
}

int main() {
    test("Esempio delle istruzioni", "ecco una stringa", 3, "stringa");
    test("Singola parola", "parola", 1, "parola");
    test("Due parole di stessa lunghezza (vince la seconda)", "foo bar", 2, "bar");  
    test("Con caratteri non-lettere attorno alla stringa", ".foo bar baz!", 3, "baz");  
    test("Altro esempio", "Michelangelo-Leonardo", 2, "Michelangelo");
    test("Nessuna parola", "1234567890!@#$%^&*()", 0, NULL);
    test("Stringa vuota", "", 0, NULL);
    test("Caratteri speciali spaziati", "!!! @@@ ### $$$", 0, NULL);
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", nsucc_tests, ntests);
    return 0;
}

