#include "definicje.h"
#include "narzedzia.h"
#include "ocena.h"
#include "negamax.h"
#include <string.h>

typedef struct
{
    char* nazwa;
    void (*funptr)();
} komenda;

poletko_gry poletko;
char bufor[1024];

void uci();
void szukaj();
void poczatek();
void wypisz_stan_gry();
void graj();
void ruch_gracza_z_konsoli();
void arena();

komenda komendy[] = { { "id", uci }, { "szukaj", szukaj }, { "odnowa", poczatek }, { "wypisz", wypisz_stan_gry }, { "graj", graj }, { "ruch", ruch_gracza_z_konsoli }, {"arena", arena} };

void main()
{
    do
    {
        scanf("%s", bufor);
        for(int i = 0; i < 7; i++)
            if (!strcmp(bufor, komendy[i].nazwa))
                komendy[i].funptr();
    } 
    while(strcmp(bufor, "qniec"));
    printf("hasta manana\n");
}

void uci()
{
    printf("gra reversi\n");
    printf("versja 1.0\n");
    printf("autor Dzajkel Mordan\n");
}

char* enum2txt(int ocena)
{
    if (ocena == -10)
        return "haniebna porazka";
    if (ocena == 10)
        return "chwalebne zwyciestwo";
    return "";
};    

void szukaj()
{
    int glebokosc;
    scanf("%d", &glebokosc);
    int ocena = negamax(&poletko, glebokosc);
    printf("info %s %d\n", enum2txt(ocena), ocena);
}

void graj()
{
    int glebokosc;
    scanf("%d", &glebokosc);
    __graj(glebokosc);
}

void __graj(int glebokosc)
{
    ruch_na_liscie *ruchy = legalne_ruchy(&poletko);
    if (ruchy)
    {
        ruch *ruch_debesciak = NULL;
        int ocena_posuniecia, debesciak = -10;
        for(ruch_na_liscie *ruch = ruchy; ruch; ruch = ruch->nastepny)
        {
            printf("info oceniam ruch %c%d\r", 'A' + ruch->ruch.na_pole.kolumna, ruch->ruch.na_pole.wiersz);
            poletko_gry wariant = wykonaj_ruch(&poletko, ruch->ruch);
            ocena_posuniecia = -negamax(&wariant, glebokosc);
            if (ocena_posuniecia > debesciak)
            {
                debesciak = ocena_posuniecia;
                ruch_debesciak = &ruch->ruch;
                printf("%c%d (%s %d) jest debesciakiem\n", 'A' + ruch->ruch.na_pole.kolumna, ruch->ruch.na_pole.wiersz, enum2txt(ocena_posuniecia), ocena_posuniecia);
            }   
        }
        if (!ruch_debesciak)
            ruch_debesciak = &ruchy->ruch;
        poletko = wykonaj_ruch(&poletko, *ruch_debesciak);
        printf("info debesciak wykonany (%s %d)\n", enum2txt(debesciak), debesciak);
        zabij_ruchy_na_liscie(ruchy);
    }
    else 
        printf("info nie ma legalnego posuniecia\n");
}

int czy_sa_wolne_pola(poletko_gry* p)
{   
    for(int i = 0; i < SZEROKOSC_POLA; i++)
        for(int j = 0; j < WYSOKOSC_POLA; j++)
            if (p->pole[i][j] == PUSTE)
                return 1;
    return 0;
}
    
void arena()//rozpoczecie meczu
{
    int glebokosc_kolka, glebokosc_krzyzyka, ocena;
    scanf("%d %d", &glebokosc_kolka, &glebokosc_krzyzyka);
    printf("info glebokosc kolka %d glebokosc krzyzyka %d\n", glebokosc_kolka, glebokosc_krzyzyka);
    while((ocena = negamax(&poletko, 0)) != -10 && ocena != 10 && czy_sa_wolne_pola(&poletko))
    {
        __graj(poletko.gracz_na_ruchu == RUCH_BIALEGO ? glebokosc_kolka : glebokosc_krzyzyka);
        wypisz(&poletko);
    }
    printf("info arena sie skonczyla\n");
}

void ruch_gracza_z_konsoli()
{
    char ruchstr[5];
    scanf("%s", &ruchstr);
    if (ruchstr[0] >= 'A' && ruchstr[0] < ('A' + SZEROKOSC_POLA) && ruchstr[1] >= '0' && ruchstr[1] < ('0' + WYSOKOSC_POLA) && poletko.pole[ruchstr[0] - 'A'][ruchstr[1] - '0'] == PUSTE)
    {
        ruch ruch_uzytkownika = { .na_pole = { ruchstr[1] - '0', ruchstr[0] - 'A' } };
        poletko = wykonaj_ruch(&poletko, ruch_uzytkownika);
        printf("info ruch wykonany\n");
    }
    else
        printf("info Misiu, nie dam sie zrobic w qnia, ruch jest nieprawidlowy\n");
    
}

void poczatek()// dla nas niepotrzebne
{
    ustaw_stan_poczatkowy(&poletko);
}

void wypisz_stan_gry()
{
    wypisz(&poletko);
}