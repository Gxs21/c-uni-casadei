#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
Realizzare la funzione `f(strings,N,sep)` qui sotto riportata, che 
- dati in ingresso un array di `N` stringhe `strings` e una stringa `sep`
- crei e restituisca in uscita una nuova stringa ottenuta combinando le stringhe in `strings` usando la stringa separatore `sep`. 
Ad esempio f(["hello","world","!"], 3, "...") deve restituire la stringa "hello...world...!!!"

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
char *f(char **strings, int n, char *sep){
	if(n<=0) return strdup("");
	int total_length = 0;
	for(int i=0; i<n; i++) {
		total_length += strlen(strings[i]);
	}
	int sep_len = strlen(sep);
	total_length += (n-1) * sep_len;
	char *res = (char*) malloc(total_length + 1);
	int k = 0;
	for(int i=0; i<n; i++){
		for(int j = 0; strings[i][j]; j++) {
			res[k++] = strings[i][j];
		}
		if(i<n-1){
			for(int j=0; j<sep_len; j++) {
				res[k++] = sep[j];
			}
		}
	}
	res[k] = '\0';
	return res;
}
// STUDENT-SOLUTION-END

int check_counter = 0;
int check_successes = 0;

void check(char **strings, int n, char *sep, char *expected) {
    printf("### Test %d: f([", ++check_counter);
    for(int i=0; i<n; i++){
        printf("\"%s\",", strings[i]);
    }
    printf("],%d,\"%s\")\n\n", n, sep);
    char *actual = f(strings, n, sep);
    if (actual == NULL) {
        printf("DA IMPLEMENTARE\n---\n");
        return;
    }
    int ok = strcmp(expected, actual) == 0;
    if(ok) {
        printf("SUCCESS: \"%s\".\n", actual);
    } else {
        printf("FAILURE.\n");
        printf("\tEXPECTED: \"%s\"\n", expected);
        printf("\tACTUAL  : \"%s\"\n", actual);
    }
    if (ok) check_successes++;
    puts("");
    free(actual);
}

void test() {
    // Caso base: 3 stringhe con separatore normale
    char *s1[] = {"hello", "world", "!"};
    check(s1, 3, "...", "hello...world...!");

    // Separatore vuoto
    char *s2[] = {"ab", "cd", "ef"};
    check(s2, 3, "", "abcdef");

    // Una sola stringa: nessun separatore
    char *s3[] = {"ciao"};
    check(s3, 1, "XXX", "ciao");

    // Nessuna stringa: output vuoto
    char **s4 = NULL;
    check(s4, 0, "---", "");

    // Stringhe vuote con separatore
    char *s6[] = {"", "", ""};
    check(s6, 3, "+", "++");

    // Stringhe vuote con separatore
    char *s7[] = {"foo", "", "bar"};
    check(s7, 3, "!", "foo!!bar");

    printf("==> %d/%d test superati\n", check_successes, check_counter);
}


int main(){
	test();
    return 0;
}