#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int array_equals(int a[], int b[], int sizea, int sizeb);
void print_array(int *a, int size);
int **build_matrix(int rows, int cols, int *elems);
void free_matrix(int **a, int rows);
void print_matrix(int **a, int rows, int cols);
int check(char *name, int **input, int N, int M, int *exp, int exp_size);

/*
Realizzare una funzione `int *valley_rows(int **matrix, int N, int M, int *size_result)` tale che:

* in input, accetti:
    1. una matrice `matrix` di interi, di dimensione N x M
    2. un puntatore a intero `size_result` passato per riferimento
* in output, restituisca:
    * un nuovo array contenente gli indici delle righe della matrice che hanno
      una valle stretta
    * in `size_result`, la dimensione dell'array restituito

Una riga ha una valle stretta se esiste un indice k, con 0 < k < M - 1, tale
che gli elementi della riga:

- decrescono strettamente fino alla posizione k
- crescono strettamente dopo la posizione k

In altre parole, per una riga `r` deve valere:

    r[0] > r[1] > ... > r[k]

e successivamente:

    r[k] < r[k + 1] < ... < r[M - 1]

L'elemento in posizione k e' il fondo della valle. Il fondo non puo' quindi
trovarsi nella prima o nell'ultima colonna. Una riga con meno di 3 elementi non
puo' avere una valle.

Si consideri il seguente esempio:

             | 7, 4, 1, 3, 6 |
    matrix = | 1, 2, 3, 4, 5 |
             | 8, 5, 2, 2, 7 |
             | 9, 6, 3, 4, 8 |

L'invocazione:

    valley_rows(matrix, 4, 5, &size_result)

deve restituire un nuovo array:

    result = [0, 3]

e deve scrivere in `size_result` il valore 2.
Infatti, la riga 0 decresce fino al valore 1 e poi cresce; la riga 3 decresce fino al
valore 3 e poi cresce. La riga 1 e' solamente crescente, mentre la riga 2
contiene due valori consecutivi uguali e non rispetta quindi la condizione di
stretta monotonia.

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
int *valley_rows(int **matrix, int N, int M, int *size_result) {

    int *result = malloc(N * sizeof(int));
    int count = 0;

    for (int i = 0; i < N; i++) {
        int j = 1;

        /* Parte strettamente decrescente */
        while (j < M && matrix[i][j] < matrix[i][j - 1]) {
            j++;
        }

        /*
         * La valle deve essere interna:
         * j == 1 significa che la riga non ha iniziato a decrescere;
         * j == M significa che ha solo decresciuto.
         */
        if (j == 1 || j == M) {
            continue;
        }

        /* Parte strettamente crescente */
        while (j < M && matrix[i][j] > matrix[i][j - 1]) {
            j++;
        }

        if (j == M) {
            result[count++] = i;
        }
    }

    *size_result = count;

    if (count == 0) {
        free(result);
        return NULL;
    }

    return result;
}
// STUDENT-SOLUTION-END

int tests = 0, tests_success = 0;

int check(char *name, int **input, int N, int M, int *exp, int exp_size){
    int actual_size = 0;
    int *actual = valley_rows(input, N, M, &actual_size);
    int correct = array_equals(exp, actual, exp_size, actual_size)
        && exp_size == actual_size;

    printf("\n### TEST: %s\n\n", name);
    printf("Input matrix:\n");
    print_matrix(input, N, M);
    printf("Return array: expected = ");
    print_array(exp, exp_size);
    printf(", actual = ");
    print_array(actual, actual_size);
    printf("\n");
    printf("Return array size: expected = %d, actual = %d\n", exp_size, actual_size);

    if (correct) {
        printf("TEST PASSED\n");
        tests_success++;
    } else {
        printf("TEST FAILED\n");
    }

    free_matrix(input, N);
    free(actual);
    puts("");
    tests++;
    return correct;
}

int array_equals(int a[], int b[], int sizea, int sizeb) {
    if (sizea != sizeb) {
        return FALSE;
    }

    if (a == NULL || b == NULL) {
        return a == b;
    }

    for (int i = 0; i < sizea; i++) {
        if (a[i] != b[i]) {
            return FALSE;
        }
    }

    return TRUE;
}

void print_array(int *a, int size){
    if(a == NULL && size > 0) {
        printf("NULL");
        return;
    }
    printf("[");
    for (int i=0; i<size; i++) printf("%d%s", a[i], i<size-1 ? "," : "");
    printf("]");
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

void free_matrix(int **a, int rows) {
    if(a == NULL) return;
    for (int i=0; i<rows; i++) free(a[i]);
    free(a);
}

void print_matrix(int **a, int rows, int cols) {
    if(a == NULL) {
        printf("NULL\n");
        return;
    }
    for (int i=0; i<rows; i++) {
        printf("| ");
        for(int j=0; j<cols; j++) printf("%2d ", a[i][j]);
        printf(" |\n");
    }
}

void test(){
    // Test delle istruzioni
    int **m0 = build_matrix(4, 5, (int[]) {
        7, 4, 1, 3, 6,
        1, 2, 3, 4, 5,
        8, 5, 2, 2, 7,
        9, 6, 3, 4, 8
    });
    check("Reference example", m0, 4, 5, (int[]) {0, 3}, 2);

    // Valle con il minimo in posizioni differenti
    int **m1 = build_matrix(4, 6, (int[]) {
        9, 7, 5, 3, 4, 8,
        8, 2, 3, 4, 5, 6,
        6, 5, 4, 3, 2, 1,
        10, 8, 6, 4, 5, 9
    });
    check("Valleys in different positions", m1, 4, 6, (int[]) {0, 1, 3}, 3);

    // Nessuna riga ha una valle
    int **m2 = build_matrix(3, 5, (int[]) {
        1, 2, 3, 4, 5,
        5, 4, 3, 2, 1,
        5, 3, 3, 4, 6
    });
    check("No valley rows", m2, 3, 5, NULL, 0);

    // Valori negativi
    int **m3 = build_matrix(3, 5, (int[]) {
        3, 0, -4, -1, 2,
        -1, -3, -5, -2, 0,
        4, 1, -2, -2, 3
    });
    check("Negative values", m3, 3, 5, (int[]) {0, 1}, 2);

    // Meno di tre colonne
    int **m4 = build_matrix(3, 2, (int[]) {
        2, 1,
        1, 2,
        3, 3
    });
    check("Too few columns", m4, 3, 2, NULL, 0);

    // Multiple vallate in una riga
    int **m5 = build_matrix(2, 7, (int[]) {
        5, 3, 1, 2, 0, 1, 3,
        4, 2, 0, 1, -1, 0, 2
    });
    check("Multiple valleys means no valley", m5, 2, 7, NULL, 0);

    // Matrice con zero righe
    int **m6 = build_matrix(0, 5, NULL);
    check("Empty matrix", m6, 0, 5, NULL, 0);

    printf("\n---\nTotal tests: %d, Success: %d, Failed: %d\n",
        tests, tests_success, tests - tests_success);
}

int main(){
    test();
    return 0;
}
