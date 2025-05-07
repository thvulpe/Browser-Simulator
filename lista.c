/* VULPE Theodor - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include "browser.h"

TTabsList AlocCelula(TTab* tab) {
    TTabsList aux = (TTabsList)malloc(sizeof(TCelulaLista));
    
    if (!aux) {
        printf("Nu s-a putut aloca memorie\n");
        return NULL;
    }    

    aux->tab = tab;
    aux->urm = aux;
    aux->pre = aux;
    return aux;
}

void DistrugeLista(TTabsList *aL) {
    if (aL == NULL)
        return;

    if (*aL == NULL)
        return;

    TTabsList start = *aL;
    
    // Sarim peste santinela
    *aL = start->urm;

    // Ramanem in bucla pana cand ajungem pe santinela
    while (*aL != start) {
        TTabsList urm = (*aL)->urm;

        DistrugeS(&((*aL)->tab->backwardStack));
        DistrugeS(&((*aL)->tab->forwardStack));
        free((*aL)->tab);

        free(*aL);
        *aL = urm;
    }

    // Eliberam santinela
    free(start);

    *aL = NULL;
}

void AdaugaCelula(TTabsList aL, TTab *tab) {
    TTabsList aux = AlocCelula(tab);
    aux->urm = aL;
    aux->pre = aL->pre;
    aL->pre->urm = aux;
    aL->pre = aux;
}

void StergeCelula(TTabsList cel) {
    cel->pre->urm = cel->urm;
    cel->urm->pre = cel->pre;

    DistrugeS(&(cel->tab->backwardStack));
    DistrugeS(&(cel->tab->forwardStack));
    free(cel->tab);
    free(cel);
}

