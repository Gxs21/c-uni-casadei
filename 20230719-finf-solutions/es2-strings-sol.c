#include <stdio.h>

#define NUM_LETTERS 26


/**
 * Si realizzi una funzione `most_frequent_letter` che, data in ingresso una stringa qualsiasi
 * ne individui la lettera (A-Z) più frequente.
 * In particolare, la funzione restituisce un SINGOLO carattere, ossia la versione maiuscola della
 * lettera più frequente all'interno della stringa in ingresso.
 * Ai fini del conteggio, lettere maiuscole e miuniscole contribuiscono ugualmente, 
 * e caratteri diversi dalle lettere non vanno conteggiati.
 * In caso di pareggio (due o più lettere sono ugualmente frequenti), la funzione restituisce
 * la lettera più frequente che viene prima in ordine alfabetico.
 * 
 * Quindi, ad esempio, per la stringa "aAa,bbb!!!!!", funzione deve restituire 'A', in quanto:
 * - ci sono 3 occorrenze di 'A'
 * - ci sono 3 occorrenze di 'B' (ma 'B' viene dopo 'A', in ordine alfabetico)
 * - c'è una occorrenza di ',' (che di sicuro non è il carattere più frequente)
 * - ci sono 5 occorrenze di '!' (ma stiamo considerando solo le lettere)
 * 
 * Suggerimenti e vincoli:
 * - non è necessario, seppure sia possibile, usare funzioni di libreria 
 * 
 * - la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
 *   `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
 *   Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 * 
 * - è possibile ed anche consigliato realizzare funzioni ausiliarie, purche comprese tra la coppia di commenti suddetti
 * 
 * - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine 
 *   di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
 *   Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
 *   modalità di verifica di competenze (ad es., prove orali) siano attuate. 
 */
char most_frequent_letter(const char* string);
char test_most_frequent_letter(char* input, char expected);
void count_letters_in_string(const char* string, int *letters);
int find_max(int *array, int *max_value);

// STUDENT-SOLUTION-START
void count_letters_in_string(const char* string, int *letters) {
    for (int i = 0; string[i] != '\0'; i++) {
        char current = string[i];
        if (current >= 'a' && current <= 'z') {
            letters[current - 'a']++;
        } else if (current >= 'A' && current <= 'Z') {
            letters[current - 'A']++;
        }
    }
}

int find_max(int *array, int *max_value) {
    int max_index = 0;
    *max_value = array[0];
    for (int i = 1; i < NUM_LETTERS; i++) {
        if (array[i] > *max_value) {
            *max_value = array[i];
            max_index = i;
        }
    }
    return max_index;
}

char most_frequent_letter(const char* string) {
    int letters[NUM_LETTERS] = {0};
    count_letters_in_string(string, letters);
    int frequency;
    char letter = 'A' + find_max(letters, &frequency);
    if (frequency == 0) {
        return '\0';
    }
    return letter;
}
// STUDENT-SOLUTION-START

int main() {
    int status = 0;
    status |= test_most_frequent_letter("", '\0');
    status |= test_most_frequent_letter("aaa,bb", 'A');
    status |= test_most_frequent_letter("Abracadabra", 'A');
    status |= test_most_frequent_letter("Hello world", 'L');
    status |= test_most_frequent_letter("ciao!!!!!!!!", 'A');
    return status;
}

char test_most_frequent_letter(char* input, char expected) {
    printf("Most frequent character in `%s`:\n", input);
    if (expected == '\0') {
        printf("\texpected: \\0\n");
    } else {
        printf("\texpected: `%c`\n", expected);
    }
    char actual = most_frequent_letter(input);
    if (expected == '\0') {
        printf("\tactual: \\0\n");
    } else {
        printf("\tactual: `%c`\n", actual);
    }
    if (expected == actual) {
        printf("\tOK!\n");
        return 0;
    } else {
        printf("\tERROR: unexpected result!\n");
        return 1;
    }
}
