#ifndef NARZEDZIA

#define NARZEDZIA

#include "definicje.h"
#include <stdio.h>
#include <assert.h>
#include <malloc.h>

int sprawdz(poletko_gry* poletko, int x, int y, int dx, int dy, int ile_jeszcze, char czego_szukamy)
{
    if (x + dx >= 0 && x + dx < SZEROKOSC_POLA && y + dy >= 0 && y + dy < WYSOKOSC_POLA)
    {
        return poletko->pole[x+dx][y+dy] == czego_szukamy && ile_jeszcze ? sprawdz(poletko, x+dx, y+dy, dx, dy, ile_jeszcze - 1, czego_szukamy) : ile_jeszcze;
    }
    return ile_jeszcze;
}

void wypisz(poletko_gry *poletko)//done
{
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_POLA; printf("-"), i++);
    printf("+\n");
    for(int i = 0; i < WYSOKOSC_POLA; i++)
    {
        printf("%2d|", i);
        for(int j = 0; j < SZEROKOSC_POLA; j++)
            switch(poletko->pole[j][i])
            {
                case PUSTE:
                    printf(" . ");
                    break;
                case BIALY:
                    printf(" O ");
                    break;
                case CZARNY:
                    printf(" X ");
                    break;
            }
        printf("|\n");
    }
    printf("  +");
    for(int i = 0; i < 3 * SZEROKOSC_POLA; printf("-"), i++);
    printf("+\n   ");
    for(int i = 0; i < SZEROKOSC_POLA; printf(" %c ", 'A' + i++));
    printf("\nRuch przypada na %c\n", poletko->gracz_na_ruchu == RUCH_BIALEGO ? 'O' : 'X');
}

void ustaw_stan_poczatkowy(poletko_gry *poletko)//done
{
    for(int i = 0; i < SZEROKOSC_POLA; i++)
        for(int j = 0; j < WYSOKOSC_POLA; j++)
            poletko->pole[i][j] = PUSTE;
    int kolumna = SZEROKOSC_POLA >> 1, wiersz = WYSOKOSC_POLA >> 1;
    poletko->pole[kolumna][wiersz] = poletko->pole[kolumna - 1][wiersz - 1] = BIALY;
    poletko->pole[kolumna - 1][wiersz] = poletko->pole[kolumna][wiersz - 1] = CZARNY;


    poletko->gracz_na_ruchu = RUCH_BIALEGO;
}

poletko_gry wykonaj_ruch(poletko_gry* plansza, ruch posuniecie)//michal
{
    assert(SZEROKOSC_POLA > posuniecie.na_pole.kolumna >= 0 &&  WYSOKOSC_POLA > posuniecie.na_pole.wiersz >= 0);
    assert(plansza->pole[posuniecie.na_pole.kolumna][posuniecie.na_pole.wiersz] == PUSTE);
    poletko_gry nowe = *plansza;
    nowe.pole[posuniecie.na_pole.kolumna][posuniecie.na_pole.wiersz] = nowe.gracz_na_ruchu == RUCH_BIALEGO ? BIALY : CZARNY;
    nowe.gracz_na_ruchu = nowe.gracz_na_ruchu == RUCH_BIALEGO ? RUCH_CZARNEGO : RUCH_BIALEGO;
    typ_pola przeciwnik = nowe.gracz_na_ruchu == RUCH_BIALEGO ? BIALY : CZARNY, ja = nowe.gracz_na_ruchu == RUCH_BIALEGO ? CZARNY : BIALY;

    for(int kierunek = 0, dwiersz, dkolumna, wiersz, kolumna; kierunek < 8; kierunek++)
    {
        for(dwiersz = kierunki[kierunek][0], dkolumna = kierunki[kierunek][1], wiersz = posuniecie.na_pole.wiersz + dwiersz, kolumna = posuniecie.na_pole.kolumna + dkolumna; SZEROKOSC_POLA > kolumna && kolumna >= 0 && WYSOKOSC_POLA > wiersz && wiersz >= 0 && nowe.pole[kolumna][wiersz] == przeciwnik ; wiersz += dwiersz, kolumna += dkolumna);
        if (SZEROKOSC_POLA > kolumna && kolumna >= 0 && WYSOKOSC_POLA > wiersz && wiersz >= 0 && nowe.pole[kolumna][wiersz] == ja)
            for(wiersz -= dwiersz, kolumna -= dkolumna; nowe.pole[kolumna][wiersz] == przeciwnik; wiersz -= dwiersz, kolumna -= dkolumna)
                nowe.pole[kolumna][wiersz] = ja;
    }

    return nowe;
}

void zabij_ruchy_na_liscie(ruch_na_liscie* glowa)
{
    assert(glowa);
    if (glowa->nastepny)
        zabij_ruchy_na_liscie(glowa->nastepny);
    free(glowa);
}

ruch_na_liscie* legalne_ruchy(poletko_gry* plansza)
{
    ruch_na_liscie *glowa = NULL, *ptr = NULL;
    ruch ruch;
    for(int kolumna = 0; kolumna < SZEROKOSC_POLA; kolumna++)
        for(int wiersz = 0; wiersz < WYSOKOSC_POLA; wiersz++)
            if (plansza->pole[kolumna][wiersz] == PUSTE)
            {
                if (ptr)
                {
                    ptr->nastepny = (ruch_na_liscie*)calloc(1, sizeof(ruch_na_liscie));
                    ptr = ptr->nastepny;
                }
                else
                    ptr = (ruch_na_liscie*)calloc(1, sizeof(ruch_na_liscie));
                ptr->nastepny == NULL;
                ptr->ruch.na_pole = (pole) { wiersz, kolumna };
                if (!glowa)
                    glowa = ptr;
            }
    return glowa;
}

#endif
