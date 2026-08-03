#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Si realizzi una funzione `string_fill` che, date in ingresso
 * - una stringa `template`, potenzialmente contenente delle sotto-stringhe di formato "%s"
 * - ed un'altra stringa `word`,
 * restituisca una copia di `template` in cui OGNI occorrenza di "%s" è rimpiazzata
 * da una occorrenza di word.
 * La funzione si occupa di alloacare la *minima* quantità di memoria necessaria a 
 * rappresentare la stringa in uscita
 * 
 * Nel seguito si fa riferimento alla sequenza "%s" come "placeholder" (segnaposto).
 * 
 * Ad esempio:
 * - string_fill("Ciao %s", "mondo") restituisce la stringa "Ciao mondo"
 * - string_fill("%s %s", "ciao") restituisce la stringa "ciao ciao"
 * - string_fill("senza placeholder", "qualunque cosa") restituisce la stringa "senza placeholder"
 * Si faccia riferimento alla funzione main per altri esempi.
 * 
 * Suggerimenti e vincoli:
 * - è vietato usare la funzione di libreria `sprintf`
 * - è possibile usare altre funzioni di libreria, come `strlen`
 * - è possibile (ed anche consigliato) sfruttare le funzioni is_placeholder, count_placeholders, string_overwrite definite sotto
 * 
 * - la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
 *   `// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
 *   Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
 * - ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine 
 *   di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
 *   Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
 *   modalità di verifica di competenze (ad es., prove orali) siano attuate. 
 */
char *string_fill(char *template, char *word);

/**
 * Questa funzione restituisce 1 (vero) se `string` continiene la sottostringa "%s"
 * in posizione `index`, altrimenti restituisce 0 (falso).
 * 
 * Ad esempio:
 * - is_placeholder("ciao %s", 5) restituisce 1
 * - is_placeholder("ciao %s", X) restituisce 0, per qualunque altro X != 5
 */
int is_placeholder(char *string, int index);

/**
 * Questa funzione conta (e restituisce) la quantità di occorrenze di "%s" in `string`
 * 
 * Ad esempio:
 * - count_placeholders("ciao %s") restituisce 1
 * - count_placeholders("%s %s") restituisce 2
 * - count_placeholders("senza placeholder") restituisce 0
 */
int count_placeholders(char *string);

/**
 * Questa funzione ha l'effetto di sovrascrivere `string` con `new`, 
 * a partire dall'indice `from_index`. 
 * Nessuna nuova stringa viene creata, 
 * ma viene modificata quella passata come primo argomento.
 * 
 * Ad esempio: string_overwrite("ciao mondo", 5, "world") ha l'effetto di modificare "ciao mondo",
 * facendola diventare "ciao world"
 */
void string_overwrite(char *string, int from_index, char *new);
int test_string_fill(char *template, char *word, char *expected);


// STUDENT-SOLUTION-START
char *string_fill(char *template, char *word) {
    int n_placeholders = count_placeholders(template);
    int word_length = strlen(word);
    int length = 1 + strlen(template) + n_placeholders * (word_length - 2);
    char *result = (char *) malloc(length * sizeof(char));
    for (int i = 0, j = 0; template[i] != '\0'; i++) {
        if (is_placeholder(template, i)) {
            string_overwrite(result, j, word);
            j += word_length;
            i++;
        } else {
            result[j] = template[i];
            j++;
        }
    }
    result[length - 1] = '\0';
    return result;
}
// STUDENT-SOLUTION-END

int count_placeholders(char *string) {
    int count = 0;
    for (int i = 0; string[i] != '\0'; i++) {
        if (is_placeholder(string, i)) {
            count++;
        }
    }
    return count;
}

int is_placeholder(char *string, int index) {
    return string[index] == '%' && string[index + 1] == 's';
}

void string_overwrite(char *string, int from_index, char *new) {
    for (int i = 0; new[i] != '\0'; i++) {
        string[from_index + i] = new[i];
    }
}

int main() {
    int status = 0;

    status |= test_string_fill(
        "String without placeholder", 
        "anything",
        "String without placeholder"
    );

    status |= test_string_fill(
        "Hello %s!", 
        "world",
        "Hello world!"
    );

    status |= test_string_fill(
        "%s bells, %s bells, %s all the way", 
        "jingle",
        "jingle bells, jingle bells, jingle all the way"
    );

    status |= test_string_fill(
        "Iulius Caesar: %seni, %sidi, %sici", 
        "V",
        "Iulius Caesar: Veni, Vidi, Vici"
    );

    status |= test_string_fill(
        "1%s, 2%s, 3%s", 
        "",
        "1, 2, 3"
    );

    status |= test_string_fill(
        "%s", 
        "any text",
        "any text"
    );

    return status;
}


int test_string_fill(char *template, char *word, char *expected) {
    printf("Filling template `%s` with word `%s`:\n", template, word);
    printf("\texpected: `%s`\n", expected);
    char *actual = string_fill(template, word);
    printf("\tactual:   `%s`\n", actual == NULL ? "NULL" : actual);
    if (strcmp(expected, actual) == 0) {
        printf("\tOK!\n");
        return 0;
    } else {
        printf("\tERROR: unexpected result!\n");
        return 1;
    }
}