#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
Si realizzi una funzione string_matrix_to_csv(string_matrix, n_rows, n_cols) che, dati in ingresso
- una matrice di stringhe `string_matrix` di dimensione nrows x ncols
restituisca una stringa rappresentante un contenuto di testo di tipo "CSV (Comma-Separated Values)".

Esempio: data in ingresso
string_matrix = [ ["Alice", "Rossi", "30"], ["Bob", "Bianchi", "25"] ] con n_rows = 2 e n_cols = 3, 
la funzione restituirà una nuova stringa rappresentante il seguente testo CSV 
(dove i caratteri backtick ` NON fanno parte della stringa ma sono solo usati per delimitare il testo in queste istruzioni):

```
Alice,Rossi,30
Bob,Bianchi,25
```

Suggerimenti

* Il tipo `char ***m`, è una matrice di stringhe, per cui m[i][j] è una stringa (ovvero un array di char terminato da '\0').
* Si consiglia di usare funzioni di libreria, ad esempio da stdio.h o string.h (https://cppreference.com/c/string/byte)
  - Ad esempio, si può usare un cursore di scrittura e sprintf per appendere nuove stringhe al risultato:
    wcursor += sprintf(wcursor, "%s", stringa_da_scrivere_nel_risultato);
* La parte delicata è calcolare la dimensione totale della stringa da restituire, in modo da allocare la memoria necessaria.
  Si considerino i caratteri aggiuntivi del separatore (,) e del newline (\n) tra le righe. 
  L'ultima riga termina con un terminatore di stringa ('\0') invece che con il newline.

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
char *string_matrix_to_csv(char ***string_matrix, int n_rows, int n_cols) {
    if (n_rows <= 0 || n_cols <= 0) {
        return NULL;
    }
    // calculate total length of resulting string
    int total_length = 0;
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            total_length += strlen(string_matrix[i][j]) + 1; // +1 for comma or newline
        }
    }
    char *result = malloc(total_length);
    char *wcursor = result;
    for (int i = 0; i < n_rows; i++) {
        for (int j = 0; j < n_cols; j++) {
            wcursor += sprintf(wcursor, "%s", string_matrix[i][j]);
            if (j < n_cols - 1) {
                *(wcursor++) = ','; // add comma between columns
            }
        }
        *(wcursor++) = '\n'; // add newline at end of row
    }
    *(wcursor - 1) = '\0'; // replace last newline with null terminator
    return result;
}
// STUDENT-SOLUTION-END

int n_tests = 0, n_ok = 0;

void test(char *name, char ***input, int i1, int i2, char *expected_output);

int main() {
    int status = 0;

    char* row1[20] = {"nome", "cognome", "età"};
    char* row2[20] = {"Alice", "Rossi", "30"};
    char* row3[20] = {"Bob", "Bianchi", "25"};
    // to matrix
    char *(*input1[20]) = {row1, row2, row3, NULL};
    char *expected_output1 = "nome,cognome,età\nAlice,Rossi,30\nBob,Bianchi,25";
    test("Test 1 (from instructions)", input1, 3, 3, expected_output1);

    // test with just one column
    char* row4[20] = {"nome"};
    char* row5[20] = {"Alice"};
    char* row6[20] = {"Bob"};
    char *(*input2[20]) = {row4, row5, row6, NULL};
    char *expected_output2 = "nome\nAlice\nBob";
    test("Test 2 (one column)", input2, 3, 1, expected_output2);

    // test with just one row
    char* row7[20] = {"nome", "cognome", "età"};
    char *(*input3[20]) = {row7, NULL};
    char *expected_output3 = "nome,cognome,età";
    test("Test 3 (one row)", input3, 1, 3, expected_output3);   

    // summary of tests
    printf("### Summary: %d/%d tests OK\n", n_ok, n_tests);

    return status;
}

void test(char *testname, char ***input, int i1, int i2, char *expected_output) {
    printf("### Test '%s':\n", testname);
    printf("\n>> Input string matrix is:\n");
    for (int i = 0; input[i] != NULL; i++) {
        for (int j = 0; input[i][j] != NULL; j++) {
            printf("%s ", input[i][j]);
        }
        printf("\n");
    }
    printf("\n>> Expected output is:\n%s\n", expected_output);
    char *actual_output = string_matrix_to_csv(input, i1, i2);
    printf("\n>> Actual result:\n%s\n", actual_output);
    if(expected_output == NULL) {
        if (actual_output == NULL) {
            printf("\n>> OK!\n");
            n_ok++;
        } else {
            printf("\n>> TEST FAILURE: expected NULL but got '%s'!\n", actual_output);
            free(actual_output);
        }
        n_tests++;
        printf("\n");
        return;
    }
    int error = strcmp(actual_output, expected_output);
    if (!error) {
        printf("\n>> OK!\n");
        n_ok++;
    } else {
        printf("\n>> TEST FAILURE: unexpected result (%d)!\n", error);
    }
    n_tests++;
    free(actual_output);
    printf("\n");
}
