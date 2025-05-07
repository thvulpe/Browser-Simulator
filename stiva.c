/* VULPE Theodor - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "browser.h"

int AdaugaS(TStivaPagini* s, TPage* page) {
    TStivaPagini aux = (TStivaPagini)malloc(sizeof(TCelulaPagina));
    if (!aux) return 0;
    aux->page = page;
    aux->urm = *s;
    *s = aux;
    return 1;
}

void EliminaS(TStivaPagini* s) {
    if (s == NULL)
        return;

    if (*s == NULL)
        return;

    TStivaPagini aux = *s;

    *s = aux->urm;
    free(aux);
}

void DistrugeS(TStivaPagini *s) {
    if (s == NULL)
        return;

    if (*s == NULL)
        return;

    TStivaPagini aux = NULL;
    while(*s != NULL) {
        aux = (*s)->urm;
        free(*s);
        *s = aux;
    }

    *s = NULL;
}

TStivaPagini AlocCelulaS(TPage* page) {
    TStivaPagini aux = (TStivaPagini)malloc(sizeof(TCelulaPagina));
    
    if (!aux) {
        printf("Nu s-a putut aloca memorie\n");
        return NULL;
    }
    
    aux->page = page;
    aux->urm = NULL;

    return aux;
}

void AdaugaCelulaS(TStivaPagini *varf, TPage *page) {
    TStivaPagini aux = AlocCelulaS(page);
    
    aux->urm = *varf;
    *varf = aux;
}

void AfiseazaS(TStivaPagini varf, int reverse) {
    if (varf == NULL)
        return;

    TStivaPagini aux = varf;
    if (!reverse) {
        while (aux) {
            printf("%s", aux->page->url);
            aux = aux->urm;
        }
    } else {
        // Afisam stiva invers
        int nrPaginiStiva = 0;
        while (aux) {
            nrPaginiStiva++;
            aux = aux->urm;
        }

        char **afisare = malloc(nrPaginiStiva * sizeof(char*));
        if (!afisare) {
            printf(ERROR_MEMORY);
            return;
        }

        aux = varf;
        int nrPagina = nrPaginiStiva;
        while (aux) {
            nrPagina--;
            afisare[nrPagina] = strdup(aux->page->url);

            aux = aux->urm;
        }

        for (int i = 0; i < nrPaginiStiva; i++) {
            printf("%s", afisare[i]);

            free(afisare[i]);
        }

        free(afisare);
    }
}

