#ifndef FUNTZIOAK_H
#define FUNTZIOAK_H
#include "sdlHasieratu.h"

#define MAPA_MUNDUA1 0
#define MAPA_MUNDUA2 1
#define MAPA_MUNDUA3 2
#define MAPA_MUNDUA4 3
#define MAPA_NIBEL1 4
#define MAPA_NIBEL2 5
#define MAPA_NIBEL3 6
#define MAPA_GAZTELUA 7

typedef struct
{
    int x;
    int y;

}POSIZIOA;

typedef struct
{
    int nibel1;
    int nibel2;
    int nibel3;
}ERANTZUNA;

typedef struct
{
    int id;
    POSIZIOA pos;
    ERANTZUNA erantzun;
    int mapa;
    int pertsonaia;
}PLAYER;


PLAYER player;
int kargatuta;

void denaKargatu();
int kargatuPartida();
void gordePartida();
void playerHasieratu();
void galderaPuntuazioaIgo(int erantzun);
void munduraItzuli();
void amaituEdoJarraitu();
void erantzunaHasieratu();
int galderakBaieztatu(int zureErantzuna, int galdera);
int galderaKargatu();
int galderaPantailaratu(char* imgGaldera);
int erantzunaJaso();
POSIZIOA saguarenPosizioa();
int ebentoaDetektatu(int ebentoa);
int ebentuaJasoGertatuBada();
int pausaMenua();
int mapenHitboxak(int tecla);
int beheruntzAnimazioa(int boo);
int ezkerreruntzAnimazioa(int boo);
int gorunztAnimazioa(int boo);
int eskubiruntzAnimazioa(int boo);
int saltoAnimazioa(int boo);
void mugimendua_nibelak(int ebentoa);

#endif
