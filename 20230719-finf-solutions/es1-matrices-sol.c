#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

int matrix_equals(char **a, char **b, int a_rows, int a_cols, int b_rows, int b_cols); // controlla l'uguaglianza di due matrici
void free_matrix(char **a, int a_rows); // libera la memoria associata a una matrice
void print_matrix(char **a, int a_rows, int a_cols); // stampa in stdout una matrice
char **make_matrix(int rows, int cols, char elem); // costruisce una matrice di `rows` righe e `cols` colonne, con ogni cella inizializzata a `elem`
char **build_matrix(int rows, int cols, char *elems); // costruisce una matrice di `rows` righe e `cols` colonne, con contenuto fornito sequenzialmente dall'array `elems`
int check(char* name, char** actual, int N, int M, char** expected); // funzione di test

enum Diagonal_Direction {
    TOP_LEFT,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_RIGHT
};

/*
    Questa enumerazione definisce le costanti intere che rappresentano i diversi tipi di istruzioni di disegno.
*/
enum Instructions {
    /* 
      Colora orrizontalmente una riga. Accetta 2 parametri: l'indice della riga da colorare e il colore. 
    */
    HLINE,
    /* 
      Colora verticalmente una colonna. Accetta 2 parametri: l'indice della colonna da colorare e il colore. 
    */
    VLINE,
    /* 
      Colora il bordo (o perimetro) dell'immagine. Accetta 1 parametro: il colore.
    */
    BOUNDARY,
    /* 
      Colora l'intera immagine. Accetta 1 parametro: il colore.
    */
    FILL,
    /* 
        Colora una diagonale a partire dalla cella data. Accetta 4 parametri: la riga della cella, la colonna della cella, 
        la direzione della diagonale (TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT), e il colore.
    */
    DIAGONAL
};

/*
    Questa funzione restituisce il numero di parametri di ogni istruzione.
    Si faccia riferimento all'enumerazione `Instructions` sopra per il significato dei parametri.
*/
int instruction_nargs(int instruction) {
    switch(instruction) {
        case HLINE: return 2;
        case VLINE: return 2;
        case BOUNDARY: return 1;
        case FILL: return 1;
        case DIAGONAL: return 4;
        default: return -1;
    }
}

/*
Si supponga di voler realizzare una funzione per facilitare il disegno di un'immagine bitmap.
Si supponga di rappresentare un'immagine mediante una matrice di char N x M (righe x colonne), dove ogni cella rappresenta un pixel, 
e dove il valore associato ad ogni cella/pixel ne rappresenta il colore (potrebbe essere 0 per bianco, e qualunque altro valore per il nero, 
non ha importanza ai fini di questo esercizio).

Allora, realizzare una funzione `f(N,M,instructions,K)` secondo le seguenti specifiche:

* La funzione accetta in ingresso le dimensioni di un'immagine NxM da creare, e un array di K istruzioni di disegno (ognuna formata come descritto in seguito);

* La funzione si occupa di creare un'immagine della dimensione data, di eseguire le istruzioni date, e di restituirla in output.

* Un'istruzione è data da una n-pla (tipo_istruzione,parametro1,...,parametroJ), dove il numero J di parametri dipende dal tipo di istruzione.
  Il tipo di istruzione è dato dalle costanti intere HLINE, VLINE, BOUNDARY, FILL, DIAGONAL dichiarate sopra.
  La funzione data `instruction_nargs` restituisce il numero di parametri di una certa istruzione; ad esempio, visto che HLINE si occupa di "colorare" una riga,
  ha bisogno del numero di riga da colorare e dal valore char del colore da usare, e quindi instruction_nargs(HLINE) restituisce 2.

Dunque, f(3, 5, [HLINE, 1, 8], 1) significa che voglio ottenere una immagine/matrice 3 x 5 (3 righe e 5 colonne), su cui voglio eseguire 1 sola istruzione di disegno,
che è l'istruzione HLINE con parametri 1 e 8. 

Osservazioni e consigli:

* NOTA: si può assumere che l'array delle istruzioni sia corretto (giusto numero di parametri per ogni istruzione)

* NOTA: si presti attenzione alla lunghezza K fornita; essa è relativa al **numero di istruzioni** (e non al numero di elementi dell'array `instructions`,
  che dipenderà in generale dal tipo di istruzioni considerate, il cui numero di parametri può variare)

* NOTA: per la creazione di una matrice, si faccia riferimento alle funzioni fornite, come `make_matrix`. 
  Si noti che le matrici sono costruite allocando i puntatori corrispondenti alle righe, e ogni riga è allocata separatamente.
  Dunque, una matrice appare come un "puntatore di puntatore", ad esempio char** m, dove m[2] ottiene il puntatore alla terza riga,
  e m[2][3] accede alla quarta cella/colonna di tale riga.

* SUGGERIMENTO: Si faccia riferimento alla funzione `test` per esempi di funzionamento

* SUGGERIMENTO: si suggerisce di compilare con opzione -Wall per ottenere tutti i warning del compilatore: gcc -Wall source.c

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
void hline(char **matrix, int N, int M, int row, int color) {
    for(int i = 0; i < M; i++) {
        matrix[row][i] = color;
    }
}

void vline(char **matrix, int N, int M, int col, int color) {
    for(int i = 0; i < N; i++) {
        matrix[i][col] = color;
    }
}

void fill(char **matrix, int N, int M, int color) {
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < M; j++) matrix[i][j] = color;
    }
}

void boundary(char **matrix, int N, int M, int color) {
    hline(matrix, N, M, 0, color);
    hline(matrix, N, M, N-1, color);
    vline(matrix, N, M, 0, color);
    vline(matrix, N, M, M-1, color);    
}

void diagonal(char **matrix, int N, int M, int row, int col, int direction, int color) {
    for(int i = row, j = col; (i < N && i >= 0) && (j < M && j >= 0); ) {
        matrix[i][j] = color;
        switch(direction) {
            case TOP_LEFT: i--; j--; break;
            case TOP_RIGHT: i--; j++; break;
            case BOTTOM_LEFT: i++; j--; break;
            case BOTTOM_RIGHT: i++; j++; break;
        }
    }
}

/*
  Restituire una matrice N x M, rappresentata come fatto in make_matrix, su cui sono state eseguite le K operazioni di disegno descritte in instructions.
*/
char** f(int N, int M, int* instructions, int K) {
    char** pic = make_matrix(N, M, 0);

    for(int i = 0, j = 0; i < K; i++) {
        switch(instructions[j]) {
            case HLINE: hline(pic, N, M, instructions[j+1], instructions[j+2]); j += 3; break;
            case VLINE: vline(pic, N, M, instructions[j+1], instructions[j+2]); j += 3; break;
            case BOUNDARY: boundary(pic, N, M, instructions[j+1]); j += 2; break;
            case FILL: fill(pic, N, M, instructions[j+1]); j += 2; break;
            case DIAGONAL: diagonal(pic, N, M, instructions[j+1], instructions[j+2], instructions[j+3], instructions[j+4]); j += 5; break;
            default: printf("Unexpected instruction"); j++;
        }    
    }

    return pic; 
}
// STUDENT-SOLUTION-END

void test(){
    char** p0 = f(3, 3, (int[]) {  }, 4);
    check("immagine vuota", p0, 3, 3, build_matrix(3, 3, (char[]) 
        { 0, 0, 0,
          0, 0, 0,
          0, 0, 0 }
    ));

    /* 
    4 istruzioni: 
      - "HLINE, 0, 1" indica una scrittura orizzontale della riga 0 con valore 1 
      - "HLINE, 2, 1" indica una scrittura orizzontale della riga 2 con valore 1
      - "VLINE, 0, 1" indica una scrittura verticale della colonna 0 con valore 1 
      - "VLINE, 2, 1" indica una scrittura verticale della colonna 2 con valore 1
    */
    char** p1 = f(3, 3, (int[]) { HLINE, 0, 1, HLINE, 2, 1, VLINE, 0, 1, VLINE, 2, 1 }, 4);
    check("bordo", p1, 3, 3, build_matrix(3, 3, (char[]) 
        { 1, 1, 1,
          1, 0, 1,
          1, 1, 1 }
    ));

    // 1 istruzione: "FILL, 5" indica che tutta la matrice/immagine va riempita con il valore 5
    char** p2 = f(3, 3, (int[]) { FILL, 5 }, 1);
    check("riempimento", p2, 3, 3, build_matrix(3, 3, (char[]) 
        { 5, 5, 5,
          5, 5, 5,
          5, 5, 5 }
    ));

    char** p3 = f(3, 5, (int[]) { FILL, 8, HLINE, 1, 2,VLINE, 2, 3 }, 3);
    check("riempimento e varie righe", p3, 3, 5, build_matrix(3, 5, (char[]) 
        { 8, 8, 3, 8, 8,
          2, 2, 3, 2, 2,
          8, 8, 3, 8, 8 }
    ));


    /* 
     "DIAGONAL, 2, 0, TOP_RIGHT, 1" vuol dire che a partire dalla cella (riga=2, colonna=0), 
     va scritta una diagonale verso l'alto e verso destra con valori 1.
     Si noti che per una matrice 3 x 5 gli indici sono come segue:

    [0][0] [0][1] [0][2] [0][3] [0][4]
    [1][0] [1][1] [1][2] [1][3] [1][4]
    [2][0] [2][1] [2][2] [2][3] [2][4]

    quindi il numero di colonne va da sinistra -> destra
    e il numero di righe dall'alto -> basso.
    */
    char** p4 = f(3, 5, (int[]) { DIAGONAL, 2, 0, TOP_RIGHT, 1, 
                                  DIAGONAL, 0, 2, BOTTOM_RIGHT, 1 }, 2);
    check("piramide", p4, 3, 5, build_matrix(3, 5, (char[]) 
        { 0, 0, 1, 0, 0,
          0, 1, 0, 1, 0,
          1, 0, 0, 0, 1 }
    ));

    char** p5 = f(5, 5, (int[]) { BOUNDARY, 1, 
                                  DIAGONAL, 0, 2, BOTTOM_LEFT, 4, 
                                  DIAGONAL, 2, 4, TOP_LEFT, 4,
                                  DIAGONAL, 2, 0, BOTTOM_RIGHT, 4, 
                                  DIAGONAL, 4, 2, TOP_RIGHT, 4 }, 5);
    check("rombo inscritto", p5, 5, 5, build_matrix(5, 5, (char[]) 
        { 1, 1, 4, 1, 1,
          1, 4, 0, 4, 1,
          4, 0, 0, 0, 4,
          1, 4, 0, 4, 1, 
          1, 1, 4, 1, 1 }
    ));
}

int i = 0, success = 0;

int main(){
    test();
    printf("=== SUCCESS %d OUT OF %d TESTS ===\n", success , i);
    return 0;
}


int check(char *name, char** actual, int N, int M, char** expected) {
    int equals = matrix_equals(actual, expected, N, M, N, M);
    printf("\n-----------------\nTEST %d: %s\n-----------------\n", i++, name);
    puts("");
    if(!equals){
        printf("Result: FAIL\n");
        printf("Actual:\n");
        print_matrix(actual, N, M);
        printf("Expected:\n");
        print_matrix(expected, N, M);    
    } else {
        success++;
        printf("Result: OK\n\n");
        print_matrix(expected, N, M);
    }
    printf("\n");
    free_matrix(actual, N);
    free_matrix(expected, N);
    return equals;
}

char **make_matrix(int rows, int cols, char elem) {
    char** m = (char **) malloc(rows * sizeof(char*));
    for(int i=0; i<rows; i++){
        m[i] = (char *) malloc(cols * sizeof(char));
        for(int j=0; j<cols; j++){
            m[i][j] = elem;
        }
    }
    return m;
}

char **build_matrix(int rows, int cols, char *elems) {
    char** m = (char **) malloc(rows * sizeof(char*));
    for(int i=0; i<rows; i++){
        m[i] = (char *) malloc(cols * sizeof(char));
        for(int j=0; j<cols; j++){
            m[i][j] = elems[i * cols + j];
        }
    }
    return m;
}

int matrix_equals(char **a, char **b, int a_rows, int a_cols, int b_rows, int b_cols) {
    if(a_rows != b_rows || a_cols != b_cols) return FALSE;
    if(a == NULL) return b == NULL;
    for (int i=0; i<a_rows; i++) {
        for(int j=0; j<a_cols; j++) {
            if(a[i][j] != b[i][j]) return FALSE;
        }
    }
    return TRUE;
}


void free_matrix(char **a, int a_rows) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        free(a[i]);
    }
    free(a);
}

void print_matrix(char **a, int a_rows, int a_cols) { 
    if(a == NULL) return;
    for (int i=0; i<a_rows; i++) {
        printf("| ");
        for(int j=0; j<a_cols; j++) {
            printf("%2d ", a[i][j]);
        }
        printf(" |\n");
    }
}
