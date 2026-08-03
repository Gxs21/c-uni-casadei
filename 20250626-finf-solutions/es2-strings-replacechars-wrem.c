#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
Realizzare la funzione `f(s,c,n)` qui sotto riportata, che dati in ingresso 
	- una stringa `s`, e
	- un array `c` di caratteri di dimensione `n` pari, 
crea e torna in uscita una nuova stringa ottenuta da `s` sostituendo ogni carattere di `s` 
che risulta presente in `c` in posizione pari `i`  con il carattere successivo in `c` (ovvero in posizione `i+1`). 
Inoltre (IMPORTANTE), se il carattere di rimpiazzo è '\0' vuol dire che il carattere da rimpiazzare va rimosso.

Ad esempio un'invocazione f("cciao", ['c','m','i','\0'], 4) deve restituire la stringa "mmao",
 ovvero dove le occorrenze di 'c' sono sostituite da 'm', e dove le occorrenze di 'i' vanno rimosse (poiché è associato a '\0'). 

Si può assumere che `c` contenga al più una occorrenza dello stesso carattere da sostituire.
Si possono fare assunzioni semplificatrici su aspetti non indicati (a patto che non compromettano il passaggio dei test).

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
	return NULL; // TODO
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
	ftest("Example from instructions", "cciao", (char[]){'c','m','i','\0'}, 4, "mmao");
	ftest("Single replacement", "Onorarono", (char[]){'o','0'}, 2, "On0rar0n0");
	ftest("Two replacements", "Onorarono", (char[]){'o','0','a','4'}, 4, "On0r4r0n0");
	ftest("Three replacements", "Onorarono", (char[]){'O','0','a','4','n','2'}, 6, "02or4ro2o");
	ftest("Four replacements", "aaa bb ccc", (char[]){'a','4','c','C','b','b',' ','_'}, 8, "444_bb_CCC");
	ftest("Empty string/replacement", "", (char[]){ }, 0, "");
	ftest("All removals", "a b a", (char[]){'a','\0','b','\0', ' ', '\0'}, 6, "");
	ftest("No matching replacement", "foo", (char[]){'a','\0','b','\0'}, 4, "foo");

	printf("\n---------- RESULT: %d / %d SUCCESSES ----------\n", nsuccesses, ntests);
}

int main(){
	test();
    return 0;
}