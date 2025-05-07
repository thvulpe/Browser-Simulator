/* VULPE Theodor - 315CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "browser.h"

// Citeste informatiile despre pagini din fisierul de intrare
TPage* CitestePagini(FILE* in, int* nrPagini) {
    fscanf(in, "%d", nrPagini);

    TPage* pages = (TPage*)malloc(*nrPagini * sizeof(TPage));

    if (!pages) {
        printf(ERROR_MEMORY);
        return NULL;
    }
    
    for (int i = 0; i < *nrPagini; i++) {
        fscanf(in, "%d", &pages[i].id);
        fgetc(in);
        fgets(pages[i].url, MAX_URL_LENGTH, in);

        pages[i].description = (char*)malloc(MAX_DESCRIPTION_LENGTH * sizeof(char));
        fgets(pages[i].description, MAX_DESCRIPTION_LENGTH, in);
    }

    return pages;
}

// Initializeaza pagina implicita
TPage InitPaginaImplicita() {
    TPage implicitPage;
    implicitPage.id = 0;
    strcpy(implicitPage.url, "https://acs.pub.ro/\n");
    implicitPage.description = strdup("Computer Science");
    return implicitPage;
}

// Verifica tipul operatiei si o proceseaza
void ProceseazaOperatie(char *operatie, TBrowser *browser, TPage *implicitPage,
    int *idCurentTab, TPage *pages, int nrPagini) {
        if (!strcmp(operatie, "NEW_TAB")) {
            DeschideTabNou(browser, implicitPage, idCurentTab);
        } else if (!strcmp(operatie, "PRINT")) {
            PrinteazaTaburi(browser);
        } else if (!strcmp(operatie, "CLOSE")) {
            InchideTabCurent(browser);
        } else if (strstr(operatie, "OPEN")) {
            int id = atoi(operatie + 5);
            DeschideTab(browser, id);
        } else if(!strcmp(operatie, "NEXT")) {
            DeschideTabUrmator(browser);
        } else if(!strcmp(operatie, "PREV")) {
            DeschideTabAnterior(browser);
        } else if (strstr(operatie, "PAGE")) {
            int id = atoi(operatie + 5);
            DeschidePagina(browser, pages, nrPagini, id);
        } else if (strstr(operatie, "PRINT_HISTORY")) {
            int id = atoi(operatie + 14);
            AfiseazaIstoric(browser, id);
        } else if(!strcmp(operatie, "BACKWARD")) {
            PaginaInapoi(browser->current);
        } else if(strstr(operatie, "FORWARD")) {
            PaginaInainte(browser->current);
        }
}

int main() {
    char operatie[MAX_OPERATION_LENGTH];

    FILE *in = fopen("tema1.in", "rt");

    if (in == NULL) {
        fprintf(stderr, "Nu s-a putut deschide fisierul de input.\n");
        return -1;
    }

    int nrPagini = 0;
    TPage *pages = CitestePagini(in, &nrPagini);

    int nrOperatii = 0;
    fscanf(in, "%d", &nrOperatii);
    fgetc(in);

    TBrowser browser;

    // Initializam santinela
    browser.list = AlocCelula(NULL);

    // Pagina implicita
    TPage implicitPage = InitPaginaImplicita();

    int idCurentTab = 0;

    // Initializam tab-ul cu ID 0
    DeschideTabNou(&browser, &implicitPage, &idCurentTab);

    // Citim operatiile
    for (int i = 0; i < nrOperatii; i++) {
        fgets(operatie, MAX_OPERATION_LENGTH, in);

        /* 
         * Eliminam caracterul endline de la final daca exista.
         * Verific pentru ambele tipuri de endline pentru ca am remarcat
         * o inconsistenta in fisierele de input ale checker-ului.
        */
        int op_len = strlen(operatie);
        if (operatie[op_len - 1] == '\n' || operatie[op_len - 1] == '\r')
            operatie[op_len - 1] = '\0';

        ProceseazaOperatie(operatie, &browser, &implicitPage, &idCurentTab,
            pages, nrPagini);
    }
    fclose(in);

    // Eliberam memoria

    for (int i = 0; i < nrPagini; i++) {
        free(pages[i].description);
    }
    free(pages);
    free(implicitPage.description);
    DistrugeLista(&browser.list);
    return 0;
}