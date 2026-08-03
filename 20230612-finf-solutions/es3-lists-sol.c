#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    int val;
    struct list *next;
} list;

/* Questi funzioni sono gia' definite, quindi e' possibile usarle direttamente */
list *list_create(int val, list *t);
int list_length(list *L);
void list_destroy(list *L);
void list_print(list *L);
int is_empty(list *L);
list *list_from_array(int v[], int n);

/*
   FUNZIONE DA REALIZZARE
   ======================

   Realizzare la funzione f(list *A, list *B, int k) che accetta come parametri due liste A e B e un intero k (si assuma > 0):

   - la funzione restituisce TRUE (1) se ogni elemento i-esimo di A compare contiguamente per k volte lista B (cioè A_i = B_{k * i} = B_{k * i + 1} = ... = B_{k * i + (k - 1)}), 
   FALSE (0) altrimenti.

   - Ad esempio, se A = (0, 1, 2), allora f(A,B,2) restituisce TRUE se B = (0, 0, 1, 1, 2, 2) e FALSE se B = (0, 1, 0, 1, 2, 2). Ulteriori esempi sono presenti nei test. 

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
int f(list *A, list *B, int k) {
    for(; A != NULL && B!= NULL && B->next != NULL; A = A->next) {
        for(int i=0; i<k; i++) {
            if(A->val != B->val) return 0;
            B = B->next;
        }
    }
    return A == B;
}
// STUDENT-SOLUTION-END

/**
 ** Non dovrebbe essere necessario modificare la parte seguente
 **/

/* Crea (mediante malloc() ) e restituisce un puntatore ad un nuovo
   nodo di una lista; il nodo contiene il valore v e punta a t come
   elemento successivo. Il chiamante e' responsabile per deallocare
   mediante free() o simili il blocco di memoria restituita da questa
   funzione, quando non piu' utilizzata */
list *list_create(int val, list *t) {
    list *r = (list *)malloc(sizeof(list));
    r->val = val;
    r->next = t;
    return r;
}

/* Restituisce la lunghezza (numero di nodi) della lista L; se L e' la
   lista vuota, restituisce 0 */
int list_length(list *L) {
    if (NULL == L) {
        return 0;
    } else {
        return (1 + list_length(L->next));
    }
}

/* Libera la memoria occupata da tutti i nodi della lista L */
void list_destroy(list *L) {
    if (L != NULL) {
        list_destroy(L->next);
        L->next = NULL; /* non necessario... */
        free(L);
    }
}

/* Stampa i valori contenuti nei nodi di L; si puo' avere L == NULL. */
void list_print(list *L) {
    printf("(");
    while (L != NULL) {
        printf("%d", L->val);
        if (L->next != NULL) {
            printf(" ");
        }
        L = L->next;
    }
    printf(")");
}

/* Restituisce 1 se e solo se L e' la lista vuota, 0 altrimenti */
int is_empty(list *L) { return (L == NULL); }

/* Restituisce una lista con n nodi, in cui il nodo i-esimo contiene
   il valore v[i] (il nodo 0 è il primo nodo della lista). */
list *list_from_array(int v[], int n) {
    if (n > 0) {
        return list_create(v[0], list_from_array(v + 1, n - 1));
    } else {
        return NULL;
    }
}

int i = 1, ok = 0, tot = 0;
void test(list *A, list *B, int k, int expect) {
    int ret = f(A, B, k);
    tot++;
    if (ret == expect) ok++;
    printf("TEST %d %s: expected %s, got %s\n", i++, ret == expect? "SUCC": "FAIL", expect ? "TRUE" : "FALSE", ret ? "TRUE" : "FALSE");
    // if(ret != expect) {
        printf("\tA = ");
        list_print(A);
        printf("; B = ");
        list_print(B);
        puts("");
    // }
}

int main(void) {
    list *A1 = NULL, *B1 = NULL;

    int a2[] = {0};
    int b2[] = {0, 0};
    int b2_3[] = {0, 0, 0};

    int a3[] = {0};
    int b3[] = {0, 1};

    int b4[] = {0, 0};

    int a5[] = {0};

    int a6[] = {0, 1, 2};
    int b6[] = {0, 0, 1, 1, 2, 2};
    int b6_4[] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2};

    int a7[] = {0, 1, 2};
    int b7[] = {0, 1, 0, 1, 2, 2};

    int a8[] = {0, 1};
    int b8[] = {0, 0, 1, 1, 2};

    list *A2 = list_from_array(a2, sizeof(a2) / sizeof(int)),
         *B2 = list_from_array(b2, sizeof(b2) / sizeof(int)),
         *B2_3 = list_from_array(b2_3, sizeof(b2_3) / sizeof(int)), 
         *A3 = list_from_array(a3, sizeof(a3) / sizeof(int)),
         *B3 = list_from_array(b3, sizeof(b3) / sizeof(int)),
         *A4 = NULL,
         *B4 = list_from_array(b4, sizeof(b4) / sizeof(int)),
         *A5 = list_from_array(a5, sizeof(a5) / sizeof(int)),
         *B5 = NULL,
         *A6 = list_from_array(a6, sizeof(a6) / sizeof(int)),
         *B6 = list_from_array(b6, sizeof(b6) / sizeof(int)),
         *B6_4 = list_from_array(b6_4, sizeof(b6_4) / sizeof(int)),
         *A7 = list_from_array(a7, sizeof(a7) / sizeof(int)),
         *B7 = list_from_array(b7, sizeof(b7) / sizeof(int)),
         *A8 = list_from_array(a8, sizeof(a8) / sizeof(int)),
         *B8 = list_from_array(b8, sizeof(b8) / sizeof(int));
    
    test(A1, B1, 2, 1);
    test(A2, B2, 2, 1);
    test(A2, B2_3, 3, 1);
    test(A3, B3, 2, 0);
    test(A4, B4, 2, 0);
    test(A5, B5, 2, 0);
    test(A6, B6, 2, 1);
    test(A6, B6_4, 4, 1);
    test(A7, B7, 2, 0);
    test(A8, B8, 2, 0);

    list* lists[] = { A1, B1, A2, B2, B2_3, A3, B3, A4, B4, A5, B5, A6, B6, B6-4, A7, B7, A8, B8 };
    int nlists = sizeof(lists) / sizeof(list*);
    for(int i=0; i < nlists; i++) { list_destroy(lists[i]); }

    printf("%d tests passed out of %d\n", ok, tot);
    return 0;
}
