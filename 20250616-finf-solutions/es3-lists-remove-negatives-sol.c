#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct list {
    int val;
    struct list *next;
};

/* Le funzioni seguenti sono gia' definite sotto, quindi e' possibile
   usarle direttamente */
struct list *list_create(int val, struct list *t);
int list_length(struct list *L);
void list_destroy(struct list *L);
void list_print(struct list *L);
int is_empty(struct list *L);
int list_equal(struct list *L1, struct list *L2);
struct list *list_from_array(int v[], int n);
    
/* FUNZIONE DA REALIZZARE
   ======================
   
   Realizzare la funzione remove_negatives(L) che accetta come parametro una lista di interi `L`
   e ne rimuove tutti gli elementi negativi (valore minore di zero).

   Ad esempio, se L = (-1, 10, 99, -3, 12, 79, 28, -8), al termine dell'esecuzione si deve avere L = (10, 99, 12, 79, 28) 
   ovvero la lista viene modificata sul posto eliminando gli elementi -1, -3, -8.

   Si presti attenzione al fatto che la funzione NON deve creare una nuova lista, ma deve modificare quella passata come parametro. 
   Inoltre, la funzione DEVE liberare correttamente la memoria corrispondente
   al nodo cancellato usando la funzione free().

   NOTA: poiché il primo elemento di `L` potrebbe venir rimosso, la funzione deve restituire 
   il puntatore alla (potenzialmente nuova) testa della lista.

   Se lo si ritiene utile, e' possibile definire ulteriori funzioni di supporto.

   Ricordiamo che una funzione che supera i test non e'
   necessariamente corretta.
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
struct list* remove_negatives(struct list *L) {
    if(!L) return NULL;
    if(L->val < 0) {
        return remove_negatives(L->next);
    } else {
        L->next = remove_negatives(L->next);
        return L;
    }
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
struct list  *list_create(int val, struct list *t)
{
    struct list *r=(struct list *)malloc(sizeof(struct list));
    r->val = val;
    r->next = t;
    return r;
}

/* Restituisce la lunghezza (numero di nodi) della lista L; se L e' la
   lista vuota, restituisce 0 */
int list_length(struct list *L)
{
    if ( NULL == L ) {
        return 0;
    } else {
        return (1 + list_length(L->next));
    }
}

/* Libera la memoria occupata da tutti i nodi della lista L */
void list_destroy(struct list *L)
{
    if ( L != NULL ) {
        list_destroy(L->next);
        L->next = NULL; /* non necessario... */
        free(L);
    }
}

/* Stampa i valori contenuti nei nodi di L; si puo' avere L ==
   NULL. */
void list_print(struct list *L)
{
    printf("(");
    while( L!=NULL ) {
        printf("%d",L->val);
        if (L->next != NULL) { printf(" "); }
        L = L->next;
    }
    printf(")");
}

/* Restituisce 1 se e solo se L e' la lista vuota, 0
   altrimenti */
int is_empty(struct list *L)
{
    return (L == NULL);
}

/* Restituisce 1 sse L1 e L2 contengono gli stessi valori */
int list_equal(struct list *L1, struct list *L2)
{
    if ((L1 == NULL) || (L2 == NULL)) {
        return ((L1 == NULL) && (L2 == NULL));
    } else {
        return ((L1->val == L2->val) && list_equal(L1->next, L2->next));
    }
}

/* Restituisce una lista con n nodi, in cui il nodo i-esimo contiene
   il valore v[i] (il nodo 0 è il primo nodo della lista). */
struct list *list_from_array(int v[], int n)
{
    if (n>0) {
        return list_create(v[0], list_from_array(v+1, n-1));
    } else {
        return NULL;
    }
}

void test(struct list *L, struct list *expect)
{
    struct list* NL = remove_negatives(L);
    if (list_equal(NL, expect)) {
        printf("Test OK\n");
    } else {
        printf("Test fallito: risultato atteso=");
        list_print(expect);
        printf(", risultato ottenuto=");
        list_print(NL);
        printf("\n");
        list_destroy(L);
    }
}

int main(void)
{
    int test1_vin[] = {-1, 10, 99, -3, 12, 79, 28, -8};
    int test1_vout[] = {10, 99, 12, 79, 28};

    struct list *test1 = list_from_array(test1_vin, sizeof(test1_vin)/sizeof(int)),
                *test1_out = list_from_array(test1_vout, sizeof(test1_vout)/sizeof(int));

    int test2_vin[] = {-1, -8};

    struct list *test2 = list_from_array(test2_vin, sizeof(test2_vin)/sizeof(int)),
                *test2_out = NULL;

    int test3_vin[] = {10, 99, -31, 21};
    int test3_vout[] = {10, 99, 21};

    struct list *test3 = list_from_array(test3_vin, sizeof(test3_vin)/sizeof(int)),
        *test3_out = list_from_array(test3_vout, sizeof(test3_vout)/sizeof(int));

    int test4_vin[] = {10, 99, 11};
    int test4_vout[] = { 10, 99, 11 };

    struct list *test4 = list_from_array(test4_vin, sizeof(test4_vin)/sizeof(int)),
        *test4_out = list_from_array(test4_vout, sizeof(test4_vout)/sizeof(int));

    printf("=== Inizio test ===\n");
    test(test1, test1_out);
    test(test2, test2_out);
    test(test3, test3_out);
    test(test4, test4_out);
    printf("=== Fine test ===\n");
    return 0;
}

