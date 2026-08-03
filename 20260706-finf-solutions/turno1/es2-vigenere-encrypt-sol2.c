#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for strdup
#include <ctype.h> // for isalpha, isupper, islower

#define TRUE 1
#define FALSE 0

int array_equals(char *a, char *b, int sizea, int sizeb);

/*
Realizzare una funzione `char *vigenere_encrypt(char *s, char *key)` tale che:

* in input, accetti:
    1. una stringa  `s` contenente il messaggio da cifrare
    2. una stringa `key` contenente la chiave del cifrario
* in output, restituisca:
    * Un puntatore ad una nuova stringa ottenuta cifrando `s` con il cifrario di Vigenere (o NULL in caso di input non validi).

Il cifrario di Vigenere funziona in modo simile a un cifrario di Cesare (cioè uno dove ogni lettera del messaggio è sostituita 
con la lettera che si trova spostata K posizioni avanti, in modo circolare), dove però lo spostamento e' determinato
da una corrispondente lettera della chiave (che può avere lunghezza diversa dalla lunghezza del messaggio). 
La lettera 'A'/'a' della chiave indica spostamento 0, 'B'/'b' indica spostamento 1, ...,  'Z'/'z' indica spostamento 25.

Si consideri ad esempio il messaggio "Ciao, mondo!" e la chiave "Lime".

La chiave viene ripetuta sulle sole lettere del messaggio, ignorando spazi,
virgole, cifre e altri simboli di punteggiatura:

    testo:   C i a o ,   m o n d o !
    chiave:  L i m e     L i m e L

Gli spostamenti determinati dalla chiave sono:

    L/l -> 11
    I/i -> 8
    M/m -> 12
    E/e -> 4

Applicando il cifrario:

    C con L: C vale 2,  L vale 11  -> (2 + 11) mod 26 = 13 -> N
    i con i: i vale 8,  i vale 8   -> (8 + 8) mod 26 = 16  -> q
    a con m: a vale 0,  m vale 12  -> (0 + 12) mod 26 = 12 -> m
    o con e: o vale 14, e vale 4   -> (14 + 4) mod 26 = 18 -> s

    la virgola e lo spazio non vengono cifrati e non fanno avanzare la chiave

    m con L: m vale 12, L vale 11  -> (12 + 11) mod 26 = 23 -> x
    o con i: o vale 14, i vale 8   -> (14 + 8) mod 26 = 22 -> w
    n con m: n vale 13, m vale 12  -> (13 + 12) mod 26 = 25 -> z
    d con e: d vale 3,  e vale 4   -> (3 + 4) mod 26 = 7   -> h
    o con L: o vale 14, L vale 11  -> (14 + 11) mod 26 = 25 -> z

    il punto esclamativo non viene cifrato e non fa avanzare la chiave

Il risultato della cifratura e':

    "Nqms, xwzhz!"

Si noti che le lettere maiuscole restano maiuscole e le lettere minuscole
restano minuscole.

REGOLE:
*) Devono essere cifrate solo le lettere alfabetiche.
*) Spazi, cifre e segni di punteggiatura devono essere copiati invariati nella stringa restituita.
*) La chiave deve avanzare solo quando viene cifrata una lettera del messaggio. I caratteri non alfabetici del messaggio
   non consumano caratteri della chiave.
*) Le lettere maiuscole devono restare maiuscole e le lettere minuscole devono restare minuscole.
*) La chiave e' valida solo se contiene almeno un carattere e tutti i suoi caratteri sono lettere alfabetiche.
*) Se la chiave non e' valida, la funzione deve restituire una nuova stringa vuota e scrivere 0 in `size_result`.
*) La stringa restituita deve essere allocata dinamicamente e terminare con il carattere `\0`.

Si consideri il seguente esempio:

   vigenere_encrypt("Ciao, mondo!", "LIME")

Ci si attende come valore di ritorno il puntatore alla nuova stringa "Nqms, xwzhz!" e come valore di `size_result` il numero 12.
Si noti che la virgola, lo spazio e il punto esclamativo non vengono cifrati e non fanno avanzare la chiave.

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
char *vigenere_encrypt(char *s, char *key) {
    if(s == NULL || key == NULL || !key[0]) return strdup(""); // Check for NULL input
    int key_n = strlen(key);
    char *result = (char *)malloc((strlen(s) + 1) * sizeof(char));
    int i = 0; // index for output string
    int j = 0; // index for the key
    if (result == NULL) return NULL; // Check for memory allocation failure
    for(; s[i]; i++) {
        if(!isalpha(key[j % key_n])) {
            break;
        }
        int key_index = j % key_n;
        if(isalpha(s[i])) {
            int key_shift = tolower(key[key_index]) - 'a';
            int letter_index = tolower(s[i]) - 'a';
            int new_index = (letter_index + key_shift) % 26;
            int alphabet_offset = isupper(s[i]) ? 'A' : 'a';
            result[i] = alphabet_offset + new_index;
            j++;
        } else {
            result[i] = s[i];
        }
    }
    result[i] = '\0'; // Null-terminate the string
    return result;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char* input, char *key, char* attended_result){
    printf("\n### TEST: %s\n\n", test_name);
    fflush(stdout);
    int size_result = strlen(attended_result);
    char* actual_result = vigenere_encrypt(input, key);
    int correct = array_equals(attended_result, actual_result, size_result, size_result);
    printf("Input string: \"%s\"\n", input);
    printf("Input key: \"%s\"\n", key);
    printf("Return string: expected = \"%s\" (%d chars), actual = \"%s\"\n", attended_result, size_result, actual_result == NULL ? "NULL" : actual_result);
    if (correct) {
        printf("TEST PASSED\n");
        tests_success++;
    } else {
        printf("TEST FAILED\n");
    }
    puts("");
    if(actual_result != NULL) free(actual_result);
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
    check("Reference example", "Ciao, mondo!", "LIME", "Nqms, xwzhz!");
    check("Reference example with numbers", "Attacco alle 10!", "LIME", "Lbfenka ewtq 10!");
    check("Single-letter key", "ABC xyz!", "b", "BCD yza!");
    check("Mixed-case key", "Zebra-42", "Key", "Jizbe-42");
    check("Longer message", "Programmazione in C", "biomedica", "Qzcsvduoaaqczi lv E");
    check("Empty message", "", "abc", "");
    check("Invalid key with digit", "Ciao", "A1", "");
    check("Invalid empty key", "Ciao", "", "");

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}
