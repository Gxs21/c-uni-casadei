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
list *list_clone(list *list);

/*
Realizzare una funzione `list* filter_multiples(list *A, int k)` che accetta in ingresso una lista A e un intero k (assumibile >= 1), 
 e restituisce una nuova lista ottenuta a partire da A ma dove sono tralasciati tutti gli elementi che compaiono in posizione multiple di k
 (assumendo le liste siano 1-indexed, cioè indicizzate a partire dalla posizione 1).

Ad esempio, se A = (3, 7, 4, 1, 3, 7), allora filter_multiples(A,2) restituirà una lista (3, 4, 3), 
ovvero dove gli elementi in posizioni pari (ossia 7, 1, 7) sono stati tralasciati, 

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
list* filter_multiples_with_index(list *A, int k, int i) {
    if(A == NULL) return NULL;
    if(i % k == 0) return filter_multiples_with_index(A->next, k, i+1);
    return list_create(A->val, filter_multiples_with_index(A->next, k, i+1));
}

list* filter_multiples(list *A, int k) {
    return filter_multiples_with_index(A, k, 1);
}
// STUDENT-SOLUTION-END

/**
 ** Non dovrebbe essere necessario modificare la parte seguente
 **/

/* Clona una lista */
list *list_clone(list *list) {
    if (list == NULL) return NULL;
    return list_create(list->val, list_clone(list->next));
}

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


/* Restituisce 1 sse L1 e L2 contengono gli stessi valori */
int list_equal(list *L1, list *L2) {
    if (L1 == NULL || L2 == NULL) {
        return (L1 == NULL && L2 == NULL);
    } else {
        return (L1->val == L2->val && list_equal(L1->next, L2->next));
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
void test(list *A, list *expect, int k) {
    list* ret = filter_multiples(A, k);
    tot++;
    int success = list_equal(ret, expect);
    if (success) ok++;
    printf("TEST %d: ", i++);
    // if(ret != expect) {
        printf("\n\tINPUT    = ");
        list_print(A);        
        printf(", k = %d\n\tACTUAL   = ", k);
        list_print(ret);
        printf("\n\tEXPECTED = ");
        list_print(expect);
        puts("");
    // }
    printf("%s\n---\n", success? "SUCCESS": "FAILURE");
}

int main(void) {
    list *A2 = list_from_array((int[]) { 3, 7, 4, 1, 3, 7 }, 6), 
         *E2 = list_from_array((int[]) { 3, 4, 3 }, 3);
    int K2 = 2;

    list *A3 = list_from_array((int[]) { 3, 7, 4, 1, 3, 7 }, 6), 
         *E3 = list_from_array((int[]) { 3, 7, 1, 3 }, 4);
    int K3 = 3;

    list *A4 = list_from_array((int[]) { 3, 7, 4, 1, 3, 7 }, 6), 
         *E4 = list_from_array((int[]) { 3, 7, 4, 1, 3, 7 }, 6);
    int K4 = 10;

    list *A5 = list_from_array((int[]) { 3, 7, 4, 1, 3, 7 }, 6), 
         *E5 = list_from_array((int[]) {  }, 0);
    int K5 = 1;

    test(NULL, NULL, 1);
    test(A2, E2, K2);
    test(A3, E3, K3);
    test(A4, E4, K4);
    test(A5, E5, K5);

    list* lists[] = { A2, E2, A3, E3 , A4, E4, A5, E5}; 
    int nlists = sizeof(lists) / sizeof(list*);
    for(int i=0; i < nlists; i++) { list_destroy(lists[i]); }
    

    printf("%d tests passed out of %d\n", ok, tot);
    return 0;
}
