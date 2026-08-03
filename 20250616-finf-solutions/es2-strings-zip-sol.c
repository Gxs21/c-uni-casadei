#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

/*
Realizzare la funzione `f(strings1,strings2,N,pairsep,itemsep)` qui sotto riportata, che 
- dati in ingresso due array di `N` stringhe ciascuno, `strings1`, `strings2` e due stringhe `pairsep` e `itemsep`
- crei e restituisca in uscita una nuova stringa ottenuta combinando le stringhe in `strings1` e `strings2` usando i separatori 

Ad esempio f(["Marco","Stefano"], ["Bianchi","Neri"], 2, " ", ";") deve restituire la stringa "Marco Bianchi;Stefano Neri". 
In questo caso specifico
- `strings1` è una lista di stringhe, ognuna rappresentante un nome
- `strings2` è una lista di stringhe, ognuna rappresentante un cognome
- `N=2` è la dimensione di tali liste di stringhe (assunta essere uguale)
- `pairsep=" "` è la stringa di separazione usata per creare le coppie
- `itemsep=";"` è la stringa di separazione usata per separare diverse coppie

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
char *f(char **strings1, char **strings2, int N, char *pairsep, char *itemsep){
	if(N<=0) return strdup("");
	int total_length = 0;
	for(int i=0; i<N; i++) {
		total_length += strlen(strings1[i]) + strlen(strings2[i]);
	}
	int pairsep_len = strlen(pairsep);
    int itemsep_len = strlen(itemsep);
	total_length += (N-1) * itemsep_len + N * pairsep_len;
	char *res = (char*) malloc(total_length + 1);
	int k = 0;
	for(int i=0; i<N; i++){
		for(int j = 0; strings1[i][j]; j++) {
			res[k++] = strings1[i][j];
		}
		for(int j=0; j<pairsep_len; j++) {
			res[k++] = pairsep[j];
		}
		for(int j = 0; strings2[i][j]; j++) {
			res[k++] = strings2[i][j];
		}
		if(i<N-1){
			for(int j=0; j<itemsep_len; j++) {
				res[k++] = itemsep[j];
			}
		}
	}
	res[k] = '\0';
	return res;
}
// STUDENT-SOLUTION-END

int check_counter = 0;
int check_successes = 0;

void check(char **strings1, char **strings2, int n, char *pairsep, char *itemsep, char *expected) {
    printf("### Test %d: f([", ++check_counter);
    for(int i=0; i<n; i++){ printf("\"%s\",", strings1[i]); }
    printf("],[");
    for(int i=0; i<n; i++){ printf("\"%s\",", strings2[i]); }
    printf("],%d,\"%s\",\"%s\")\n\n", n, pairsep, itemsep);
    char *actual = f(strings1, strings2, n, pairsep, itemsep);
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
    char *s11[] = {"Marco", "Stefano"};
    char *s12[] = {"Bianchi", "Neri"};
    check(s11, s12, 2, " ", ";", "Marco Bianchi;Stefano Neri");
    check(s12, s11, 2, " ", ", ", "Bianchi Marco, Neri Stefano");
    check(s11, s11, 2, "", "", "MarcoMarcoStefanoStefano");
    check(s12, s12, 1, "", "", "BianchiBianchi");

    char *s21[] = {"Bjarne Stroustrup", "Dennis Ritchie", "Guido van Rossum"};
    char *s22[] = {"C++", "C", "Python"};
    check(s21, s22, 3, " created ", ". ", "Bjarne Stroustrup created C++. Dennis Ritchie created C. Guido van Rossum created Python");

    printf("==> %d/%d test superati\n", check_successes, check_counter);
}


int main(){
	test();
    return 0;
}