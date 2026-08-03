#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols);
void free_matrix(int **a, int a_rows);
void print_matrix(int **a, int a_rows, int a_cols);
int **make_matrix(int rows, int cols, int elem);
int **build_matrix(int rows, int cols, int *elems);
int check(char* name, int** input, int N, int M, int** exp, int exp_count);

/*
Implementare una funzione f(matrix, N, M, count) che 

- accetta in ingresso una matrice N x M di interi
- accetta un puntatore a intero count, passato per riferimento
- restituisce una nuova matrice N x M di interi
- nella nuova matrice:
    * ogni cella contiene 1 se la cella corrispondente nella matrice originale
      e' un massimo locale stretto
    * ogni altra cella contiene 0
- scrive in count il numero totale di massimi locali stretti trovati

Una cella e' un massimo locale stretto se il suo valore e' strettamente maggiore
di tutti i suoi vicini esistenti nelle 8 direzioni:

    sopra, sotto, sinistra, destra,
    diagonale alto-sinistra, diagonale alto-destra,
    diagonale basso-sinistra, diagonale basso-destra.

Le celle sul bordo hanno meno vicini, ma vanno comunque considerate.

In altre parole, un'invocazione f(matrix, 3, 3, &count) con 

             | 1, 2, 3 |
    matrix = | 4, 9, 6 |
             | 7, 8, 5 |

deve restituire una nuova matrice:

             | 0, 0, 0 |
    result = | 0, 1, 0 |
             | 0, 0, 0 |

e deve scrivere in count il valore 1.

La cella centrale vale infatti 9 ed e' strettamente maggiore di tutti i suoi
8 vicini.

Osservazioni e consigli:

* SUGGERIMENTO: Si faccia riferimento alle funzioni di test/verifica per esempi di funzionamento.
* SUGGERIMENTO: La funzione non deve modificare la matrice originale, ma deve restituire una nuova matrice.
* SUGGERIMENTO: Le celle sul bordo devono essere controllate considerando solo i vicini esistenti.
* SUGGERIMENTO: Si suggerisce di compilare con opzione -Wall per ottenere tutti i warning del compilatore: gcc -Wall source.c

NOTE GENERALI:

*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sarà considerato durante la valutazione.
*) E' possibile definire più funzioni ausiliarie qualora lo si ritenga opportuno. 
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verrà confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo è resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarità importanti, è possibile che la prova possa venire annullata, e che ulteriori
modalità di verifica di competenze, ad es. prove orali, siano attuate.
*/
// STUDENT-SOLUTION-START
int **f(int **matrix, int N, int M, int *count) {
    return NULL;
}
// STUDENT-SOLUTION-END

void test() {
    // Caso 0: esempio base, massimo locale al centro
    int** m0 = build_matrix(3, 3, (int[]) {
        1, 2, 3,
        4, 9, 6,
        7, 8, 5
    });
    int** exp0 = build_matrix(3, 3, (int[]) {
        0, 0, 0,
        0, 1, 0,
        0, 0, 0
    });
    check("Example from instructions", m0, 3, 3, exp0, 1);

    // Caso 1: massimo locale sul bordo
    int** m1 = build_matrix(3, 3, (int[]) {
        9, 2, 3,
        4, 1, 6,
        7, 8, 5
    });
    int** exp1 = build_matrix(3, 3, (int[]) {
        1, 0, 0,
        0, 0, 0,
        0, 1, 0
    });
    check("Local maxima on border", m1, 3, 3, exp1, 2);

    // Caso 2: nessun massimo locale stretto per valori uguali
    int** m2 = build_matrix(3, 3, (int[]) {
        5, 5, 5,
        5, 5, 5,
        5, 5, 5
    });
    int** exp2 = build_matrix(3, 3, (int[]) {
        0, 0, 0,
        0, 0, 0,
        0, 0, 0
    });
    check("All equal values", m2, 3, 3, exp2, 0);

    // Caso 3: matrice con piu' massimi locali
    int** m3 = build_matrix(4, 4, (int[]) {
        9, 1, 2, 8,
        1, 0, 1, 2,
        2, 1, 7, 1,
        6, 1, 1, 5
    });
    int** exp3 = build_matrix(4, 4, (int[]) {
        1, 0, 0, 1,
        0, 0, 0, 0,
        0, 0, 1, 0,
        1, 0, 0, 0
    });
    check("Several local maxima", m3, 4, 4, exp3, 4);

    // Caso 4: matrice con una sola riga
    int** m4 = build_matrix(1, 5, (int[]) {
        1, 3, 2, 5, 4
    });
    int** exp4 = build_matrix(1, 5, (int[]) {
        0, 1, 0, 1, 0
    });
    check("Single row matrix", m4, 1, 5, exp4, 2);

    // Caso 5: matrice con una sola colonna
    int** m5 = build_matrix(5, 1, (int[]) {
        1,
        4,
        2,
        6,
        3
    });
    int** exp5 = build_matrix(5, 1, (int[]) {
        0,
        1,
        0,
        1,
        0
    });
    check("Single column matrix", m5, 5, 1, exp5, 2);

    // Caso 6: matrice 1x1
    int** m6 = build_matrix(1, 1, (int[]) {
        7
    });
    int** exp6 = build_matrix(1, 1, (int[]) {
        1
    });
    check("Single cell matrix", m6, 1, 1, exp6, 1);

    // Caso 7: matrice vuota
    int** m7 = build_matrix(0, 0, NULL);
    int** exp7 = build_matrix(0, 0, NULL);
    check("Empty matrix 0x0", m7, 0, 0, exp7, 0);
}


int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, int** input, int N, int M, int** exp, int exp_count) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);

    int actual_count = 0;
    int** actual = f(input, N, M, &actual_count);

    int success_matrix = matrix_equals(actual, exp, N, M, N, M);
    int success_count = actual_count == exp_count;
    int success = success_matrix && success_count;

    printf("Input:\n");
    print_matrix(input, N, M);

    printf("\nActual:\n");
    print_matrix(actual, N, M);

    printf("\nExpected count: %d, actual count: %d\n", exp_count, actual_count);

    puts("");

    if(!success){
        printf("Result: FAIL\n");
        printf("Expected matrix:\n");
        print_matrix(exp, N, M);
    } else {
        n_succ_tests++;
        printf("Result: OK\n");
    }

    printf("\n");

    free_matrix(input, N);
    free_matrix(exp, N);
    free_matrix(actual, N);

    return success;
}

int **make_matrix(int rows, int cols, int elem) {
    int** m = (int **) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++){
        m[i] = (int *) malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
    return m;
}

int **build_matrix(int rows, int cols, int *elems) {
    int** m = (int **) malloc(rows * sizeof(int*));
    for(int i=0; i<rows; i++){
        m[i] = (int *) malloc(cols * sizeof(int));
        for(int j=0; j<cols; j++){
            m[i][j] = elems[i * cols + j];
        }
    }
    return m;
}

int matrix_equals(int **a, int **b, int a_rows, int a_cols, int b_rows, int b_cols) {
    if(a_rows != b_rows || a_cols != b_cols) return FALSE;
    if(a == NULL || b == NULL) return a==b;
    for (int i=0; i<a_rows && i<b_rows; i++) {
        for(int j=0; j<a_cols && j<b_cols; j++) {
            if(a[i][j] != b[i][j]) return FALSE;
        }
    }
    return TRUE;
}


void free_matrix(int **a, int a_rows) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(int **a, int a_rows, int a_cols) { 
    if(a == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i=0; i<a_rows; i++) {
        printf("| ");
        for(int j=0; j<a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}

int array_equals(int a[], int b[], int sizea, int sizeb){
    if(a == b) return FALSE;
    if(a == NULL || b == NULL) return FALSE;
    if(sizea != sizeb) return FALSE;
    for (; sizea--;)
        if (a[sizea] != b[sizea])
            return FALSE;
    return TRUE;
}

void print_array(int *a, int size){
    if(a == NULL) {
        printf("NULL");
        return;
    }
    int i;
    printf("[");
    for (i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
}