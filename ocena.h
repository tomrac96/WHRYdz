#ifndef OCENA //oceniam pozycje (kto by pomyslal)

#define OCENA

#include "definicje.h"

int ocen_pozycje(poletko_gry* plansza)
{
    int kolka = 0, krzyzyki = 0, puste = 0;
    for(int kolumna = 0; kolumna < SZEROKOSC_POLA; kolumna++)
        for(int wiersz = 0; wiersz < WYSOKOSC_POLA; wiersz++)
            switch(plansza->pole[kolumna][wiersz])
            {
                case BIALY:
                    kolka++; break;
                case CZARNY:
                    krzyzyki++; break;
                case PUSTE:
                    puste++; break;
            }
    if (!puste)
        return plansza->gracz_na_ruchu == RUCH_BIALEGO ? (kolka > krzyzyki ? 10 : (kolka < krzyzyki ? -10 : 0)) : (kolka < krzyzyki ? 10 : (kolka > krzyzyki ? -10 : 0));
    return (plansza->gracz_na_ruchu == RUCH_BIALEGO ? kolka - krzyzyki : krzyzyki - kolka);
}

#endif