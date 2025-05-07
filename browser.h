/* VULPE Theodor - 315CB */

#define ERROR_MESSAGE "403 Forbidden\n"
#define ERROR_MEMORY "Eroare la alocarea memoriei\n"

#define MAX_PAGES 50
#define MAX_OPERATION_LENGTH 20
#define MAX_URL_LENGTH 50
#define MAX_DESCRIPTION_LENGTH 256

typedef struct {
    int id;
    char url[50];
    char* description;
} TPage;

typedef struct celulaPagina {
    TPage* page;
    struct celulaPagina *urm;
} TCelulaPagina, *TStivaPagini;

// Adauga un element in stiva
int AdaugaS(TStivaPagini *s, TPage* page);

// Elimina un element din stiva
void EliminaS(TStivaPagini *s);

// Distruge stiva
void DistrugeS(TStivaPagini *s);

TStivaPagini AlocCelulaS(TPage *page);

// Adauga o celula in stiva si modifica varful
void AdaugaCelulaS(TStivaPagini *varf, TPage *page);

// Afiseaza link-urile paginilor retinute in stiva
void AfiseazaS(TStivaPagini varf, int reverse);

typedef struct {
    int id;
    TStivaPagini backwardStack;
    TPage* currentPage;
    TStivaPagini forwardStack;
} TTab;

typedef struct celulaTab{
    TTab* tab;
    struct celulaTab *urm;
    struct celulaTab *pre;
} TCelulaLista, *TTabsList;

TTabsList AlocCelula(TTab *tab);

void DistrugeLista(TTabsList *aL);

// Adauga celula unei liste cu santinela
void AdaugaCelula(TTabsList aL, TTab *tab);

// Sterge ultima celula din lista
void StergeCelula(TTabsList aL);

typedef struct {
    TTab *current;
    TTabsList list;
} TBrowser;

void PrinteazaTaburi(TBrowser *browser);

// Deschide un nou TAB si acceseaza pagina default
TTab* DeschideTabNou(TBrowser *browser, TPage *pageToOpen, int *id);

// Inchide TAB-ul curent prin eliminarea din lista
void InchideTabCurent(TBrowser *browser);

void DeschideTab(TBrowser *browser, int id);

void DeschideTabUrmator(TBrowser *browser);

void DeschideTabAnterior(TBrowser *browser);

void DeschidePagina(TBrowser *browser, TPage *pages, int nrPagini, int id);

void AfiseazaIstoric(TBrowser *browser, int id);

void PaginaInapoi(TTab *tab);

void PaginaInainte(TTab *tab);

// Elibereaza memoria asociata browser-ului
void ElibereazaBrowser(TBrowser *browser);