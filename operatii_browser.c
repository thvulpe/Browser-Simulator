/* VULPE Theodor - 315CB */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "browser.h"

// Primeste un ID si intoarce tab-ul din lista sau NULL
TTabsList CautaTab(TTabsList tabList, int id) {
    if (tabList == NULL)
        return NULL;

    // Sarim peste santinela
    TTabsList aux = tabList->urm;

    do {
        if (aux->tab->id == id)
            return aux;
        aux = aux->urm;
    } while (aux != tabList);

    return NULL;
}

void PrinteazaTaburi(TBrowser* browser) {
    int idStart = browser->current->id;
    TTabsList aux = CautaTab(browser->list, idStart);

    // Afisam id-urile tab-urilor
    do {
        printf("%d ", aux->tab->id);
        aux = aux->urm;
        // Sarim peste santinela
        if (aux->tab == NULL) aux = aux->urm; 
    } while (aux->tab->id != idStart);
    printf("\n");

    char *desc = browser->current->currentPage->description;
    printf("%s", desc);

    // Afisam endline daca descrierea nu are deja la final
    if (desc[strlen(desc) - 1] != '\n')
        printf("\n");
}

TTab *DeschideTabNou(TBrowser* browser, TPage* pageToOpen, int* id) {
    TTab *tab = (TTab*)malloc(sizeof(TTab));
    tab->id = *id;
    tab->forwardStack = NULL;
    tab->backwardStack = NULL;
    tab->currentPage = pageToOpen;

    browser->current = tab;

    // Adaugam tab-ul in lista
    AdaugaCelula(browser->list, tab);

    (*id)++;

    return tab;
}

void InchideTabCurent(TBrowser* browser) {
    // Verificam daca tab-ul care trebuie inchis nu este cel initial
    int idTab = browser->current->id;
    if (idTab == 0) {
        printf(ERROR_MESSAGE);
        return;
    }

    // Obtinem celula tab-ului curent
    TTabsList tabList = CautaTab(browser->list, idTab);
    
    // Actualizam tab-ul curent
    browser->current = tabList->pre->tab;

    StergeCelula(tabList);
}

int VerificaExistaTab(TTabsList tabList, int id) {
    return CautaTab(tabList, id) != NULL;
}

void DeschideTab(TBrowser *browser, int id) {
    // Verificam daca exista tab-ul
    int exista = VerificaExistaTab(browser->list, id);
    if (!exista) {
        printf(ERROR_MESSAGE);
        return;
    }

    browser->current = CautaTab(browser->list, id)->tab;
}

void DeschideTabUrmator(TBrowser *browser) {
    TTabsList tab = CautaTab(browser->list, browser->current->id);
    tab = tab->urm;
    
    // Daca a picat pe santinela
    if (tab->tab == NULL) tab = tab->urm;

    browser->current = tab->tab;
}

void DeschideTabAnterior(TBrowser *browser) {
    TTabsList tabList = CautaTab(browser->list, browser->current->id);
    tabList = tabList->pre;
    
    // Daca a picat pe santinela
    if (tabList->tab == NULL) tabList = tabList->pre;

    browser->current = tabList->tab;
}

void DeschidePagina(TBrowser *browser, TPage *pages, int nrPagini, int id) {
    TPage *page = NULL;
    
    // Cautam pagina
    for (int i = 0; i < nrPagini; i++) {
        if (pages[i].id == id) {
            page = &pages[i];
            break;
        }
    }

    if (!page) {
        printf(ERROR_MESSAGE);
        return;
    }

    TTab *tabCurent = browser->current;

    AdaugaCelulaS(&(tabCurent->backwardStack), tabCurent->currentPage);

    DistrugeS(&tabCurent->forwardStack);

    tabCurent->currentPage = page;
}

void AfiseazaIstoric(TBrowser *browser, int id) {
    // Verificam daca exista tab-ul
    int exista = VerificaExistaTab(browser->list, id);
    if (!exista) {
        printf(ERROR_MESSAGE);
        return;
    }

    TTabsList tabList = CautaTab(browser->list, id);

    AfiseazaS(tabList->tab->forwardStack, 1);
    printf("%s", tabList->tab->currentPage->url);
    AfiseazaS(tabList->tab->backwardStack, 0);
}

// Verifica daca o stiva este goala
int StivaEsteGoala(TStivaPagini s) {
    return (s == NULL);
}

void PaginaInapoi(TTab *tab) {
    if (StivaEsteGoala(tab->backwardStack)) {
        printf(ERROR_MESSAGE);
        return;
    }

    AdaugaCelulaS(&tab->forwardStack, tab->currentPage);
    tab->currentPage = tab->backwardStack->page;
    EliminaS(&tab->backwardStack);
}

void PaginaInainte(TTab *tab) {
    if (StivaEsteGoala(tab->forwardStack)) {
        printf(ERROR_MESSAGE);
        return;
    }

    AdaugaCelulaS(&tab->backwardStack, tab->currentPage);

    tab->currentPage = tab->forwardStack->page;
    EliminaS(&tab->forwardStack);
}