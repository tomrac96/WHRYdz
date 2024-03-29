#ifndef DEFINICJE

#define DEFINICJE

#define SZEROKOSC_POLA 16
#define WYSOKOSC_POLA 8

//const int HANIEBNA_PORAZKA = -(SZEROKOSC_POLA * WYSOKOSC_POLA + 100);
//const int CHWALEBNE_ZWYCIESTWO = -HANIEBNA_PORAZKA;

#include <limits.h>

typedef enum { PUSTE, BIALY, CZARNY } typ_pola;
typedef enum { RUCH_BIALEGO, RUCH_CZARNEGO } ruch_gracza;

typedef struct
{
    typ_pola pole[SZEROKOSC_POLA][WYSOKOSC_POLA];
    ruch_gracza gracz_na_ruchu;
} poletko_gry;

typedef struct
{
    char wiersz, kolumna;
} pole;

typedef struct
{
    pole na_pole;
} ruch;

typedef struct element
{
    ruch ruch;
    struct element* nastepny;
} ruch_na_liscie;

int kierunki[8][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0}, {1, -1}, {-1, 1}, {-1, -1}, {1, 1} };

#endif