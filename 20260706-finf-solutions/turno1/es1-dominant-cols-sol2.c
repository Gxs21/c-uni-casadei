#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int **make_matrix(int rows, int cols, int elem);
int **build_matrix(int rows, int cols, int *elems);
void free_matrix(int **a, int rows);
void print_matrix(int **a, int rows, int cols);
int check(char *name, int **input, int N, int M, int *exp, int exp_size);

/*
Realizzare una funzione `int *dominant_cols(int **matrix, int N, int M, int *size_result)` tale che:

* in input, accetti:
    1. una matrice `matrix` di interi non negativi, di dimensione N x M
    2. un puntatore a intero `size_result` passato per riferimento
* in output, restituisca:
    * un nuovo array contenente gli indici delle colonne dominanti della matrice
    * in `size_result`, la dimensione dell'array restituito

Una colonna si dice dominante se esiste almeno un elemento della colonna che e' strettamente maggiore della somma di tutti gli altri elementi della stessa colonna.

Si consideri il seguente esempio:

    matrix =
    |  1  4 20  8 |
    |  2  5  1  8 |
    | 10  6  2  1 |
    |  3  7  3  1 |

La colonna 0 e' dominante perche':

    10 > 1 + 2 + 3

La colonna 1 non e' dominante perche' nessun suo elemento e' strettamente maggiore della somma degli altri elementi della colonna.

La colonna 2 e' dominante perche':

    20 > 1 + 2 + 3

La colonna 3 non e' dominante perche':

    8 non e' > 8 + 1 + 1

Ci si attende quindi che la funzione restituisca l'array:

    [0, 2]

e che scriva in `size_result` il valore 2.

Si noti che il confronto deve essere stretto: se un elemento e' uguale alla somma degli altri elementi, allora non e' dominante.

Si assuma che gli elementi della matrice siano interi non negativi.

NOTE GENERALI:
*) ATTENZIONE: la propria soluzione va inserita nella porzione del sorgente inclusa tra i commenti single-line
`// STUDENT-SOLUTION-START` e  `// STUDENT-SOLUTION-END`.
Codice scritto al di fuori di tali commenti non sara' considerato durante la valutazione.
*) E' possibile definire piu' funzioni ausiliarie qualora lo si ritenga opportuno.
Ma lo si faccia all'interno dei commenti, come indicato nel punto precedente.
*) ATTENZIONE: la soluzione verra' confrontata con quella dei colleghi mediante strumenti automatici al fine
di rilevare potenziali copiature. Il controllo e' resistente a rename di variabili, spezzamento di espressioni etc.
Qualora vengano riscontrate similarita' importanti, e' possibile che la prova possa venire annullata, e che ulteriori
modalita' di verifica di competenze, ad es. prove orali, siano attuate.
*/
// STUDENT-SOLUTION-START
int *dominant_cols(int **matrix, int N, int M, int *size_result) {
    int dominant_col_indices[M];
    int n_dom = 0;
    for(int i = 0; i < M; i++) {
        dominant_col_indices[i] = 0;
        // for every element in column i, check for property
        for(int cur = 0; cur < N; cur++) {
            int sum = 0;
            for(int r = 0; r < N; r++) {
                if(r == cur) continue;
                sum += matrix[r][i];
            }
            if(sum < matrix[cur][i]) {
                dominant_col_indices[i] = 1;
                n_dom++;
            }
        }
    }
    printf("Found %d dominant columns\n", n_dom);fflush(stdout);
    *size_result = n_dom;
    int *result = (int *)malloc(n_dom * sizeof(int));
    for(int i = M-1; i >= 0; i--) {
        if(dominant_col_indices[i]) {
            result[--n_dom] = i;
        }
    }
    return result;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

void test() {
    int **m0 = build_matrix(4, 4, (int[]) {
         1,  4, 20,  8,
         2,  5,  1,  8,
        10,  6,  2,  1,
         3,  7,  3,  1
    });
    check("Reference example", m0, 4, 4, (int[]) { 0, 2 }, 2);

    int **m1 = build_matrix(3, 3, (int[]) {
        5, 9, 7,
        2, 4, 1,
        3, 8, 1
    });
    check("Strict comparison", m1, 3, 3, (int[]) { 2 }, 1);

    int **m2 = build_matrix(4, 3, (int[]) {
        1, 2, 3,
        1, 2, 3,
        1, 2, 3,
        1, 2, 3
    });
    check("No dominant columns", m2, 4, 3, (int[]) { }, 0);

    int **m3 = build_matrix(1, 4, (int[]) {
        0, 5, 1, 9
    });
    check("Single row matrix", m3, 1, 4, (int[]) { 1, 2, 3 }, 3);

    int **m4 = build_matrix(5, 1, (int[]) {
        1,
        2,
        20,
        3,
        4
    });
    check("Single column dominant", m4, 5, 1, (int[]) { 0 }, 1);

    int **m5 = build_matrix(5, 1, (int[]) {
        1,
        2,
        3,
        4,
        10
    });
    check("Single column equality is not dominant", m5, 5, 1, (int[]) { }, 0);

    int **m6 = build_matrix(0, 0, NULL);
    check("Empty matrix", m6, 0, 0, (int[]) { }, 0);

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n", tests, tests_success, tests - tests_success);
}

int main() {
    test();
    return 0;
}

int check(char *name, int **input, int N, int M, int *exp, int exp_size) {
    int actual_size = 0;
    int *actual = dominant_cols(input, N, M, &actual_size);
    int correct = array_equals(actual, exp, actual_size, exp_size);

    printf("\n### TEST: %s\n\n", name);
    printf("Input matrix:\n");
    print_matrix(input, N, M);
    printf("\nReturn array: expected = ");
    print_array(exp, exp_size);
    printf(", actual = ");
    print_array(actual, actual_size);
    printf("\nReturn array size: expected = %d, actual = %d\n", exp_size, actual_size);

    if (correct) {
        printf("TEST PASSED\n");
        tests_success++;
    } else {
        printf("TEST FAILED\n");
    }

    tests++;
    free_matrix(input, N);
    free(actual);
    return correct;
}

int **make_matrix(int rows, int cols, int elem) {
    int **m = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        m[i] = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            m[i][j] = elem;
        }
    }
    return m;
}

int **build_matrix(int rows, int cols, int *elems) {
    int **m = (int **) malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; i++) {
        m[i] = (int *) malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            m[i][j] = elems[i * cols + j];
        }
    }
    return m;
}

void free_matrix(int **a, int rows) {
    if (a == NULL) return;
    for (int i = 0; i < rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(int **a, int rows, int cols) {
    if (a == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i = 0; i < rows; i++) {
        printf("| ");
        for (int j = 0; j < cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf("|\n");
    }
}

void print_array(int *a, int size) {
    if (a == NULL || size == 0) {
        printf("[]");
        return;
    }
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d%s", a[i], i < size - 1 ? "," : "");
    }
    printf("]");
}

int array_equals(int a[], int b[], int sizea, int sizeb) {
    if ((a == NULL || b == NULL) && sizea == 0 && sizeb == 0) return TRUE;
    if ((a == NULL || b == NULL) && a != b) return FALSE;
    if (sizea != sizeb) return FALSE;
    for (int i = 0; i < sizea; i++) {
        if (a[i] != b[i]) return FALSE;
    }
    return TRUE;
}
