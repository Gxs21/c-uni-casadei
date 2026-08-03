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
int check(char* name, int** input, int N, int M, int** exp);

/*
Implementare una funzione f(matrix, N, M) che 

- accetta in ingresso una matrice N x M di interi
- restituisce una nuova matrice N x M di interi
- nella nuova matrice:
    * ogni cella interna contiene la media intera tra:
        - la cella originale
        - il vicino sopra
        - il vicino sotto
        - il vicino a sinistra
        - il vicino a destra
    * le celle sul bordo vengono copiate uguali dalla matrice originale

In altre parole, un'invocazione f(matrix, 3, 3) con 

             | 1,  2,  3 |
    matrix = | 4, 10,  6 |
             | 7,  8,  9 |

deve restituire una nuova matrice:

             | 1,  2,  3 |
    result = | 4,  6,  6 |
             | 7,  8,  9 |

La cella centrale vale infatti:

    (10 + 2 + 8 + 4 + 6) / 5 = 30 / 5 = 6

Le celle sul bordo rimangono invariate.

Osservazioni e consigli:

* SUGGERIMENTO: Si faccia riferimento alle funzioni di test/verifica per esempi di funzionamento.
* SUGGERIMENTO: La funzione non deve modificare la matrice originale, ma deve restituire una nuova matrice.
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
int **f(int **matrix, int N, int M) {
    int **res = make_matrix(N, M, 0);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {

            // celle sul bordo: copiate uguali
            if (i == 0 || i == N - 1 || j == 0 || j == M - 1) {
                res[i][j] = matrix[i][j];
            } 
            // celle interne: media con i 4 vicini ortogonali
            else {
                res[i][j] = (
                    matrix[i][j] +
                    matrix[i - 1][j] +
                    matrix[i + 1][j] +
                    matrix[i][j - 1] +
                    matrix[i][j + 1]
                ) / 5;
            }
        }
    }

    return res;
}
// STUDENT-SOLUTION-END

void test() {
    // Caso 0: esempio base
    int** m0 = build_matrix(3, 3, (int[]) {
        1,  2,  3,
        4, 10,  6,
        7,  8,  9
    });
    int** exp0 = build_matrix(3, 3, (int[]) {
        1, 2, 3,
        4, 6, 6,
        7, 8, 9
    });
    check("Example from instructions", m0, 3, 3, exp0);

    // Caso 1: matrice 4x4 con celle interne diverse
    int** m1 = build_matrix(4, 4, (int[]) {
        1,  2,  3,  4,
        5, 10, 20,  8,
        9, 30, 40, 12,
        13,14, 15, 16
    });
    int** exp1 = build_matrix(4, 4, (int[]) {
        1,  2,  3,  4,
        5, 13, 16,  8,
        9, 20, 23, 12,
        13,14, 15, 16
    });
    check("Generic 4x4 matrix", m1, 4, 4, exp1);

    // Caso 2: matrice senza celle interne, una sola riga
    int** m2 = build_matrix(1, 5, (int[]) {
        1, 2, 3, 4, 5
    });
    int** exp2 = build_matrix(1, 5, (int[]) {
        1, 2, 3, 4, 5
    });
    check("Single row matrix", m2, 1, 5, exp2);

    // Caso 3: matrice senza celle interne, una sola colonna
    int** m3 = build_matrix(5, 1, (int[]) {
        1,
        2,
        3,
        4,
        5
    });
    int** exp3 = build_matrix(5, 1, (int[]) {
        1,
        2,
        3,
        4,
        5
    });
    check("Single column matrix", m3, 5, 1, exp3);

    // Caso 4: matrice 2x2, solo bordo
    int** m4 = build_matrix(2, 2, (int[]) {
        1, 2,
        3, 4
    });
    int** exp4 = build_matrix(2, 2, (int[]) {
        1, 2,
        3, 4
    });
    check("Only border matrix", m4, 2, 2, exp4);

    // Caso 5: matrice con tutti valori uguali
    int** m5 = build_matrix(3, 4, (int[]) {
        5, 5, 5, 5,
        5, 5, 5, 5,
        5, 5, 5, 5
    });
    int** exp5 = build_matrix(3, 4, (int[]) {
        5, 5, 5, 5,
        5, 5, 5, 5,
        5, 5, 5, 5
    });
    check("All equal values", m5, 3, 4, exp5);

    // Caso 6: matrice vuota
    int** m6 = build_matrix(0, 0, NULL);
    int** exp6 = build_matrix(0, 0, NULL);
    check("Empty matrix 0x0", m6, 0, 0, exp6);
}


int n_tests = 0, n_succ_tests = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", n_succ_tests , n_tests);
    return 0;
}


int check(char* name, int** input, int N, int M, int** exp) {
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", n_tests++, name);

    int** actual = f(input, N, M);

    int success = matrix_equals(actual, exp, N, M, N, M);

    printf("Input:\n");
    print_matrix(input, N, M);

    printf("\nActual:\n");
    print_matrix(actual, N, M);

    puts("");

    if(!success){
        printf("Result: FAIL\n");
        printf("Expected:\n");
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