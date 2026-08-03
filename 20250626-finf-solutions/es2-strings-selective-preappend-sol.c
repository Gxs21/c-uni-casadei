#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
Realizzare la funzione `f(s,c,n)` qui sotto riportata, che dati in ingresso 
	- una stringa `s`, e
	- un array `c` contente `n` triplette di valori (c0,c1,p) , 
crea e torna in uscita una nuova stringa ottenuta da `s` aggiungendo 
ad ogni occorrenza di `c0` in `s`, un numero di occorrenze |p| (valore assoluto di `p`) di `c1`,
(prima dell'occorrenza di `c0` se p<0 o dopo se p>0). 
In altre parole, è una funzione usata per appendere/prependere certi caratteri ad alcuni caratteri della stringa in input
(NON si tratta di sostituzioni: i caratteri originali della stringa sono preservati).

Ad esempio un'invocazione f("ciao,mondo(!)", [',',' ',1, '(',' ',-1], 2) deve restituire la stringa "ciao, mondo (!)",
dove 
	- tutti i caratteri della stringa di partenza sono preservati 
	- ad ogni occorrenza della virgola ',' **segue** una (1) occorrenza di uno spazio, e 
	- ad ogni occorrenza della parentesi di apertura '(' va **preceduta** una (-1) occorrenza di uno spazio.

Altri esempi:
	- f("eee", ['e','h',1]) -----> "eheheh" (si appende una 'h' dopo ogni 'e')
	- f("eee", ['e','h',-1]) -----> "hehehe" (si prepende una 'h' prima di ogni 'e')
	- f("A!", ['A','.',-3,'!','h',-3], 2) -----> "...Ahhh!" (si prependono tre '.' ad 'A', e si prependono tre 'h' a '!')

Si noti che il parametro `n` indica il numero di triple presenti nell'array `c`, e non il totale di elementi (che sarà `n*3`). 

Si osservi la funzione test per comprendere il funzionamento atteso attraverso ulteriori esempi.

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
char *f(char *s, char c[], int n){
	int nlen = strlen(s);
	for(int i=0; s[i]; i++) {
		for(int j=0; j<n; j++) {
			int p = j*3;
			if(c[p] == s[i]) { 
				nlen += abs(c[p+2]);
				break;
			}
		}
	}

	char* result = (char*)malloc(nlen+1);
	int k = 0;
	for(int i=0; s[i]; i++) {
		int match = -1;
		for(int j=0; j<n; j++) {
			int p = j*3;
			if(c[p] == s[i] ) { match = j; break; } 
		}
		if(match != -1) {
			if(c[match*3+2] < 0) { 
				for(int occ = abs(c[match*3+2]); occ > 0; occ--) result[k++] = c[match*3+1];
			}
			result[k++] = s[i];
			if(c[match*3+2] > 0) { 
				for(int occ = abs(c[match*3+2]); occ > 0; occ--) result[k++] = c[match*3+1];
			}
		} else {
			result[k++] = s[i];
		}
	}
	result[nlen] = '\0';
	return result;
}
// STUDENT-SOLUTION-END

int check(char *expected, char *actual, int size) {
	if(actual == NULL) { printf("DA IMPLEMENTARE\n"); return 0; }
	printf("EXPECTED: %s\n", expected);
    printf("ACTUAL  : %s\n", actual);
	int success = strcmp(expected, actual)==0;
    printf("==> %s\n---\n", success ? "TRUE" : "FALSE");
	return success;
}

int ntests = 0;
int nsuccesses = 0;
void ftest(char *name, char *input, char *repl, int size, char *expected) {
	ntests++;
	printf("\n*** %s ***\n", name);
	char *actual = f(input, repl, size);
	nsuccesses += check(expected, actual, size);
	free(actual);
}

void test(){
	ftest("Example 1 from instructions", "ciao,mondo(!)", (char[]){',',' ',1, '(',' ',-1}, 2, "ciao, mondo (!)");
	ftest("Example 2 from instructions", "eee", (char[]){'e','h',1}, 1, "eheheh");
	ftest("Example 3 from instructions", "eee", (char[]){'e','h',-1}, 1, "hehehe");
	ftest("Example 4 from instructions", "A!", (char[]){'A','.',-3,'!','h',-3}, 2, "...Ahhh!");
	ftest("No additions", "Ah", (char[]){ }, 0, "Ah");
	ftest("No matching additions", "Ah", (char[]){ 'b', 'c', 3 }, 1, "Ah");
	ftest("Empty string", "", (char[]){ 'b', 'c', 3 }, 1, "");
	ftest("Added chars are NOT considered in turn", "a!a", (char[]){ 'a', '!', 3, '!', '?', 2 }, 2, "a!!!!??a!!!");

	printf("\n---------- RESULT: %d / %d SUCCESSES ----------\n", nsuccesses, ntests);
}

int main(){
	test();
    return 0;
}