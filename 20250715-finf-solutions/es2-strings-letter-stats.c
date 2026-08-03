#include <stdio.h>

/*
Si realizzi una funzione `letter_stats(s, pc, n)` che, dati in ingresso 

* una stringa `s` qualsiasi,
* un puntatore a carattere `pc` (che ospiterà un output)
* un puntatore a intero `n` (che ospiterà un altro output)

restituisca come risultati:
 
 - il numero di lettere dell'alfabeto (a-z) che compaiono almeno una volta nella stringa
 - il carattere più frequente (da scrivere nel puntatore `pc`)
 - il numero di occorrenza del carattere più frequente (da scrivere nel puntatore `n`)

Note

- le lettere dell'alfabeto vanno considerate indipendentemente dal "case" (maiuscolo o minuscolo)
- i caratteri diversi dalle lettere non vanno conteggiati
- a parità di frequenza, va data priorità alla lettera che viene *dopo* in ordine alfabetico

Esempio:

- letter_stats("aA,bb,a", &c, &n) deve restituire 2 (per 'A' e 'B'), c = 'A', n = 3 ('A' compare 3 volte)

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
int letter_stats(const char* string, char *pc, int *n) {
    return -1; // DA IMPLEMENTARE
}
// STUDENT-SOLUTION-END

int ntests = 0;
int nsucc_tests = 0;

void test(char *title, char* input, int num_chars_present_exp, char most_freq_char_exp, int most_freq_count_exp) {
    printf("### Test: %s\n", title);
    char most_freq_char_actual = '\0';
    int most_freq_count_actual = 0;
    int num_chars_present = letter_stats(input, &most_freq_char_actual, &most_freq_count_actual);
    printf("Input: `%s`\n", input);
    printf("Expected return: %d. Actual return: %d\n", num_chars_present_exp, num_chars_present);
    printf("Expected most frequent character: `%c`. Actual: `%c`\n", most_freq_char_exp, most_freq_char_actual);
    printf("Expected count: %d. Actual: %d\n", most_freq_count_actual, most_freq_count_actual);
    int success = (num_chars_present == num_chars_present_exp) &&
                  (most_freq_char_actual == most_freq_char_exp) &&
                  (most_freq_count_actual == most_freq_count_exp);
    printf("Success: %s\n\n", success ? "YES" : "NO");    
    ntests++;
    nsucc_tests += success;
}

int main() {
    test("Esempio delle istruzioni", "aA,bb,a", 2, 'A', 3);
    test("Singola lettera ai bordi", "aa...aa", 1, 'A', 4);
    test("Due lettere con frequenza uguale (vince quella che viene dopo)", "aA,bb,cc", 3, 'C', 2);
    test("Tutte le lettere dell'alfabeto", "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", 26, 'Z', 2);
    test("Stringa compless arbitraria", "Hello, World! 1234 @#$%^&*()", 7, 'L', 3);
    test("Nessuna lettera", "1234567890!@#$%^&*()", 0, '\0', 0);
    test("Stringa vuota", "", 0, '\0', 0);
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", nsucc_tests, ntests);
    return 0;
}

