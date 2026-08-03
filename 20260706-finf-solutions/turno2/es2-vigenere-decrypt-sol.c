#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int string_equals(char *a, char *b);

/*
Realizzare una funzione `char *vigenere_decrypt(char *s, char *key)` tale che:

* in input, accetti:
    1. una stringa `s` terminata dal carattere `\0` contenente il messaggio da decifrare
    2. una stringa `key` terminata dal carattere `\0` contenente la chiave del cifrario
* in output, restituisca:
    * Un puntatore ad una nuova stringa ottenuta decifrando `s` con il cifrario di Vigenere.

Il cifrario di Vigenere funziona in modo simile a un cifrario di Cesare (cioè uno dove ogni lettera del messaggio è sostituita 
con la lettera che si trova spostata K posizioni avanti, in modo circolare), dove però lo spostamento e' determinato
da una corrispondente lettera della chiave (che può avere lunghezza diversa dalla lunghezza del messaggio).
In decifratura lo spostamento viene sottratto. La lettera 'A'/'a' della chiave
indica spostamento 0, 'B'/'b' indica spostamento 1, ..., 'Z'/'z' indica spostamento 25.

Si consideri ad esempio il messaggio cifrato "Nqms, xwzhz!" e la chiave "Lime".

La chiave viene ripetuta sulle sole lettere del messaggio, ignorando spazi,
virgole, cifre e altri simboli di punteggiatura:

    testo cifrato: N q m s ,   x w z h z !
    chiave:        L i m e     L i m e L

Gli spostamenti determinati dalla chiave sono:

    L/l -> 11
    I/i -> 8
    M/m -> 12
    E/e -> 4

Applicando la decifratura:

    N con L: N vale 13, L vale 11 -> (13 - 11 + 26) mod 26 = 2  -> C
    q con i: q vale 16, i vale 8  -> (16 - 8 + 26) mod 26 = 8   -> i
    m con m: m vale 12, m vale 12 -> (12 - 12 + 26) mod 26 = 0  -> a
    s con e: s vale 18, e vale 4  -> (18 - 4 + 26) mod 26 = 14  -> o

    la virgola e lo spazio non vengono decifrati e non fanno avanzare la chiave

    x con L: x vale 23, L vale 11 -> (23 - 11 + 26) mod 26 = 12 -> m
    w con i: w vale 22, i vale 8  -> (22 - 8 + 26) mod 26 = 14  -> o
    z con m: z vale 25, m vale 12 -> (25 - 12 + 26) mod 26 = 13 -> n
    h con e: h vale 7,  e vale 4  -> (7 - 4 + 26) mod 26 = 3    -> d
    z con L: z vale 25, L vale 11 -> (25 - 11 + 26) mod 26 = 14 -> o

    il punto esclamativo non viene decifrato e non fa avanzare la chiave

Il risultato della decifratura e':

    "Ciao, mondo!"

Si noti che le lettere maiuscole restano maiuscole e le lettere minuscole
restano minuscole.

REGOLE:
*) Devono essere decifrate solo le lettere alfabetiche.
*) Spazi, cifre e segni di punteggiatura devono essere copiati invariati nella stringa restituita.
*) La chiave deve avanzare solo quando viene decifrata una lettera del messaggio. I caratteri non alfabetici del messaggio
   non consumano caratteri della chiave.
*) Le lettere maiuscole devono restare maiuscole e le lettere minuscole devono restare minuscole.
*) La chiave e' valida solo se contiene almeno un carattere e tutti i suoi caratteri sono lettere alfabetiche.
*) L'input non e' valido se `s` o `key` sono `NULL`, oppure se la chiave non e' valida.
*) Se l'input non e' valido, la funzione deve restituire `NULL`.
*) La stringa restituita, se non `NULL`, deve essere allocata dinamicamente e terminare con il carattere `\0`.

Si consideri il seguente esempio:

   vigenere_decrypt("Nqms, xwzhz!", "LIME")

Ci si attende come valore di ritorno il puntatore alla nuova stringa "Ciao, mondo!".
Si noti che la virgola, lo spazio e il punto esclamativo non vengono decifrati e non fanno avanzare la chiave.

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

int string_length(char *s){
    int n = 0;
    while(s[n] != '\0'){
        n++;
    }
    return n;
}

int check_key(char *key){
    for(int i=0; key[i] != '\0'; i++){
        if(!(key[i] >= 'a' && key[i] <= 'z') && !(key[i] >= 'A' && key[i] <= 'Z')){
            return 0;
        }
    }
    return 1;
}

int key_char_to_offset(char c){
    if(c >= 'a' && c <= 'z'){
        return c - 'a';  
    }else {
        return c - 'A';
    }
}

char *vigenere_decrypt(char *s, char *key) {
    if(s == NULL || key == NULL) {
        return NULL;
    }

    int n = string_length(s);
    int key_n = string_length(key);

    if(key_n <= 0 || !check_key(key)) {
        return NULL;
    }

    char *result = (char *)malloc((n+1) * sizeof(char));

    int j=0;

    for(int i=0; i < n; i++){
        char to_sub = key_char_to_offset(key[j % key_n]);
        if(s[i] >= 'a' && s[i] <= 'z'){
            char offset =  ((s[i] - 'a') - to_sub + 26) % 26;
            j++;
            result[i] = 'a' + offset;
        } else if (s[i] >= 'A' && s[i] <= 'Z'){
            char offset =  ((s[i] - 'A') - to_sub + 26) % 26;
            j++;
            result[i] = 'A' + offset;
        } else{
            result[i] = s[i];
        }
    }
    result[n]='\0';
    return result;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *test_name, char* input, char *key, char* attended_result){
    char* actual_result = vigenere_decrypt(input, key);
    int correct = string_equals(attended_result, actual_result);
    printf("\n### TEST: %s\n\n", test_name);
    printf("Input string: \"%s\"\n", input == NULL ? "NULL" : input);
    printf("Input key: \"%s\"\n", key == NULL ? "NULL" : key);
    printf("Return string: expected = \"%s\", actual = \"%s\"\n", attended_result == NULL ? "NULL" : attended_result, actual_result == NULL ? "NULL" : actual_result);
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

int string_equals(char *a, char *b){
    if(a == NULL || b == NULL) return a == b;
    int i = 0;
    while(a[i] != '\0' && b[i] != '\0'){
        if (a[i] != b[i])
            return FALSE;
        i++;
    }
    return a[i] == b[i];
}

void test(){
    // Test delle istruzioni
    check("Reference example", "Nqms, xwzhz!", "LIME", "Ciao, mondo!");
    check("Reference example with numbers", "Lbfenka ewtq 10!", "LIME", "Attacco alle 10!");
    check("Single-letter key", "BCD yza!", "b", "ABC xyz!");
    check("Mixed-case key", "Jizbe-42", "Key", "Zebra-42");
    check("Longer message", "Qzcsvduoaaqczi lv E", "biomedica", "Programmazione in C");
    check("Empty message", "", "abc", "");
    check("Invalid key with digit", "Nqms", "A1", NULL);
    check("Invalid empty key", "Nqms", "", NULL);
    check("Invalid NULL message", NULL, "abc", NULL);
    check("Invalid NULL key", "Nqms", NULL, NULL);

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}
