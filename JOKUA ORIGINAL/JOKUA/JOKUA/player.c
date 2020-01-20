#include "funtzioak.h"
#include "kontrolak.h"
#include "irudiak.h"
#include "hitbox.h"
#include "SDLHasieratu.h"

SDL_Event event;
POSIZIOA saguPos;
PLAYER player;


int erantzunak[3];
int goraAnimaz = 0, ezkerreraAnimaz = 0, beheraAnimaz = 0, eskubiAnimaz = 0;

void denaKargatu()
{

    if (player.mapa == MAPA_MUNDUA1 || player.mapa == MAPA_MUNDUA2 || player.mapa == MAPA_MUNDUA3)
    {
        irudiaSortu(MUNDUA);
    }
    else if (player.mapa == MAPA_GAZTELUA)
    {
        irudiaSortu(LEHENENGO_PANTAILA2);
    }
    else if (player.mapa == MAPA_NIBEL1)
    {
        irudiaSortu(LEHENENGO_NIBELA);
    }
    else if (player.mapa == MAPA_NIBEL2)
    {
        irudiaSortu(BIGARREN_NIBELA);
    }
    else if (player.mapa == MAPA_NIBEL3)
    {
        irudiaSortu(HIRUGARREN_NIBELA);
    }
    if (player.pertsonaia == 1)
    {
        player.id = irudiaSortu(MARIO_GELDIRIK);
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
    else if (player.pertsonaia == 2)
    {
        player.id = irudiaSortu(LUIGI_GELDIRIK);
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
}

int kargatuPartida()
{
    int kargatu = 0;
    FILE* save;

    save = fopen("MUrio_gorde.sav", "r");
    if (save == NULL)
    {
        printf("Errorea egon da fitxategia irekitzerakoan . . .\n");
    }
    else
    {
        fscanf(save, "Posizioak: %d %d Mapa: %d pertsonaia: %d\n", &player.pos.x, &player.pos.y, &player.mapa, &player.pertsonaia);
        denaKargatu();
        irudiakMarraztu();
        SDL_RenderPresent(gRenderer);
        kargatu = 1;
    }

    return kargatu;
}

void gordePartida()
{
    FILE* save;

    save = fopen("MUrio_gorde.sav", "w");
    if (save == NULL)
    {
        printf("Errorea egon da fitxategia sortzerakoan. . .");
    }
    else
    {
        fprintf(save, "Posizioak: %d %d Mapa: %d pertsonaia: %d\n", player.pos.x, player.pos.y, player.mapa, player.pertsonaia);
        fclose(save);
    }
}

int bukaeraMezua(int ebentoa)
{
    int bukatu = JOLASTEN, bukaeraID = 0;

    SDL_RenderPresent(gRenderer);
    SDL_Delay(3000);
    textuaDesgaitu();
    textuaIdatzi(40, 410, "Sakatu ESC tekla jokutik ateratzeko");
    SDL_RenderPresent(gRenderer);
    bukatu = GAME_OVER;
    do
    {
        ebentoa = ebentuaJasoGertatuBada();
    } while (ebentoa != TECLA_ESCAPE);
    irudiaKendu(bukaeraID);

    return bukatu;
}

void munduraItzuli()
{
    int imgID = -1;

    if (player.mapa == MAPA_NIBEL1)
    {
        player.mapa = MAPA_MUNDUA2;
        irudiaSortu(MUNDUA);
        player.pos.x = 68;
        player.pos.y = 72;
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
    else if (player.mapa == MAPA_NIBEL2)
    {
        player.mapa = MAPA_MUNDUA3;
        irudiaSortu(MUNDUA);
        player.pos.x = 68;
        player.pos.y = 72;
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
    else if (player.mapa == MAPA_NIBEL3)
    {
        player.mapa = MAPA_MUNDUA4;
        irudiaSortu(MUNDU_FINALA);
        player.pos.x = 68;
        player.pos.y = 72;
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
}

void galderaPuntuazioaIgo(int erantzun)
{
    if (player.mapa == MAPA_NIBEL1)player.erantzun.nibel1 = erantzun;
    if (player.mapa == MAPA_NIBEL2)player.erantzun.nibel2 = erantzun;
    if (player.mapa == MAPA_NIBEL3)player.erantzun.nibel3 = erantzun;
}

void playerHasieratu()
{
    player.erantzun.nibel1 = 0;
    player.erantzun.nibel2 = 0;
    player.erantzun.nibel3 = 0;
    player.mapa = MAPA_GAZTELUA;
}

void erantzunaHasieratu()
{
    erantzunak[0] = 1;
    erantzunak[1] = 1;
    erantzunak[2] = 3;
}

int galderakBaieztatu(int zureErantzuna, int galdera)
{
    int ondo = 0;

    if (zureErantzuna == erantzunak[galdera])
    {
        ondo = 1;
    }

    return ondo;
}

int galderaPantailaratu(char* imgGaldera)
{
    int galderaID, ebentoa;

    galderaID = irudiaSortu(imgGaldera);
    SDL_RenderPresent(gRenderer);
    do
    {
        ebentoa = ebentuaJasoGertatuBada();
    } while (ebentoa != SAGU_BOTOIA_EZKERRA);

    irudiaKendu(galderaID);
    galderaID = irudiaSortu(imgGaldera);
    irudiakMarraztu();
    SDL_RenderPresent(gRenderer);

    return galderaID;
}

int galderaKargatu()
{
    int galderaID = -1;

        if (player.mapa == MAPA_NIBEL1)
        {
            galderaPantailaratu(LEHENENGO_GALDERA);
            galderaID = 0;
        }
        else if (player.mapa == MAPA_NIBEL2)
        {
            galderaPantailaratu(BIGARREN_GALDERA);
            galderaID = 1;
        }
        else if (player.mapa == MAPA_NIBEL3)
        {
            galderaPantailaratu(HIRUGARREN_GALDERA);
            galderaID = 2;
        }

    return galderaID;
}

int erantzunaJaso()
{
    int erantzuna = 0, galderaID, zuzen;

    galderaID = galderaKargatu();
    erantzunaHasieratu();
    erantzuna = galderenHitboxa();
    if (erantzuna != 0)
    {
        irudiaKendu(galderaID);
        zuzen = galderakBaieztatu(erantzuna, galderaID);
        if (zuzen == 1)
        {
            galderaPuntuazioaIgo(zuzen);
        }
    }
    irudiaKendu(galderaID);
    amaituEdoJarraitu();
    irudiaMugitu(player.id, player.pos.x, player.pos.y);
    SDL_RenderPresent(gRenderer);

    return erantzuna;
}

void amaituEdoJarraitu()
{
    int egoera, berriz = 0;
    POSIZIOA saguPos;
    if (player.mapa == MAPA_NIBEL1 && player.erantzun.nibel1 == 1)
    {
        irudiaSortu(GALDERA_ZUZENA);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);
        munduraItzuli();
    }
    else if (player.mapa == MAPA_NIBEL1 && player.erantzun.nibel1 != 1)
    {
        irudiaSortu(GALDERA_OKERRA);
        SDL_RenderPresent(gRenderer);
        do {

            egoera = ebentuaJasoGertatuBada();
            saguPos = saguarenPosizioa();
            if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 183 && saguPos.x <= 373) && (saguPos.y >= 242 && saguPos.y <= 267))
            {
                berriz = 1;
            }
        } while (berriz != 1);
        if (berriz)
        {
            berrabiarazi();
        }
    }

    else if (player.mapa == MAPA_NIBEL2 && player.erantzun.nibel2 == 1)
    {
        irudiaSortu(GALDERA_ZUZENA);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);
        munduraItzuli();
    }

    else if (player.mapa == MAPA_NIBEL2 && player.erantzun.nibel2 != 1)
    {
        irudiaSortu(GALDERA_OKERRA);
        SDL_RenderPresent(gRenderer);
        do {

            egoera = ebentuaJasoGertatuBada();
            saguPos = saguarenPosizioa();
            if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 183 && saguPos.x <= 373) && (saguPos.y >= 242 && saguPos.y <= 267))
            {
                berriz = 1;
            }
        } while (berriz != 1);
        if (berriz)
        {
            berrabiarazi();
        }
    }

    else if (player.mapa == MAPA_NIBEL3 && player.erantzun.nibel3 == 1)
    {
        irudiaSortu(GALDERA_ZUZENA);
        SDL_RenderPresent(gRenderer);
        SDL_Delay(5000);
        munduraItzuli();
    }

    else if (player.mapa == MAPA_NIBEL3 && player.erantzun.nibel3 != 1)
    {
        irudiaSortu(GALDERA_OKERRA);
        SDL_RenderPresent(gRenderer);
        do {

            egoera = ebentuaJasoGertatuBada();
            saguPos = saguarenPosizioa();
            if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 183 && saguPos.x <= 373) && (saguPos.y >= 242 && saguPos.y <= 267))
            {
                berriz = 1;
            }
        } while (berriz != 1);
        if (berriz)
        {
            berrabiarazi();
        }
    }

    if (player.pertsonaia == 1)
    {
        player.id = irudiaSortu(MARIO_GELDIRIK);
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
    else if (player.pertsonaia == 2)
    {
        player.id = irudiaSortu(LUIGI_GELDIRIK);
        irudiaMugitu(player.id, player.pos.x, player.pos.y);
    }
    irudiakMarraztu();
}

int pausaMenua()
{
    int egoera, id, ret = 0, gorde = 0, segi = 0, irten = 0, pausa = 0;
    POSIZIOA saguPos;

    id = irudiaSortu(PAUSE);
    do
    {
        egoera = ebentuaJasoGertatuBada();
        saguPos = saguarenPosizioa();
        if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 451 && saguPos.x <= 542) && (saguPos.y >= 206 && saguPos.y <= 271))
        {
            gorde = 1;
        }

        if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 451 && saguPos.x <= 542) && (saguPos.y >= 59 && saguPos.y <= 121))
        {
            segi = 1;
        }

        if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 451 && saguPos.x <= 542) && (saguPos.y >= 360 && saguPos.y <= 423))
        {
            irten = 1;
        }

        if (egoera == SAGU_BOTOIA_EZKERRA && (saguPos.x >= 560 && saguPos.x <= 615) && (saguPos.y >= 15 && saguPos.y <= 55))
        {
            if ((Mix_PausedMusic() == 1) && (egoera == SAGU_BOTOIA_EZKERRA))
            {
                //Resume the music
                Mix_ResumeMusic();
                pausa = 0;
                irudiaKendu(id);
                id = irudiaSortu(PAUSE);
                pantailaGarbitu();
                irudiakMarraztu();
                SDL_RenderPresent(gRenderer);
            }
            //If the music is playing
            else
            {
                if (egoera == SAGU_BOTOIA_EZKERRA)
                {
                    //Pause the music
                    Mix_PauseMusic();
                    irudiaKendu(id);
                    id = irudiaSortu(PAUSE_MUTE);
                    pantailaGarbitu();
                    irudiakMarraztu();
                    SDL_RenderPresent(gRenderer);
                }
            }
        }

        SDL_RenderPresent(gRenderer);
    } while (gorde != 1 && segi != 1 && irten != 1);
    saguPos = saguarenPosizioa();
    if (irten == 1)
    {
        ret = GAME_OVER;
    }
    else if (segi == 1)
    {
        ret = JOLASTEN;
    }
    else if (gorde == 1)
    {
        gordePartida();
        ret = JOLASTEN;
    }

    pantailaGarbitu();
    irudiaKendu(id);
    irudiakMarraztu();
    SDL_RenderPresent(gRenderer);

    return ret;
}

int ebentoaDetektatu(int ebentoa)
{

    int egoera = 1, baimena = 0;

    if (kargatuta != 1)
    {
        kargatuta = kargatuPartida();
        if (kargatuta == 0)
        {
            egoera = GAME_OVER;
        }
    }
    if (player.mapa == MAPA_MUNDUA1 || player.mapa == MAPA_GAZTELUA || player.mapa == MAPA_MUNDUA2 || player.mapa == MAPA_MUNDUA3 || player.mapa == MAPA_MUNDUA4) {
        if (ebentoa == TECLA_w || ebentoa == TECLA_UP)
        {
            baimena = mapenHitboxak(ebentoa);
            pantailaGarbitu();
            if (baimena == 1)
            {
                player.pos.y -= (300 / 60);
            }
            goraAnimaz = gorunztAnimazioa(goraAnimaz);
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        if (ebentoa == TECLA_a || ebentoa == TECLA_LEFT)
        {
            baimena = mapenHitboxak(ebentoa);
            pantailaGarbitu();
            ezkerreraAnimaz = ezkerreruntzAnimazioa(ezkerreraAnimaz);
            if (baimena == 1) {
                player.pos.x -= SPEED / 60;
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        if (ebentoa == TECLA_s || ebentoa == TECLA_DOWN)
        {
            baimena = mapenHitboxak(ebentoa);
            pantailaGarbitu();
            beheraAnimaz = beheruntzAnimazioa(beheraAnimaz);
            if (baimena == 1)
            {
                player.pos.y += 300 / 60;
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        if (ebentoa == TECLA_d || ebentoa == TECLA_RIGHT)
        {
            baimena = mapenHitboxak(ebentoa);
            pantailaGarbitu();
            eskubiAnimaz = eskubiruntzAnimazioa(eskubiAnimaz);
            if (baimena == 1) {
                player.pos.x += SPEED / 60;
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
    }
    if (player.mapa == MAPA_NIBEL1)
    {
        mugimendua_nibelak(ebentoa);
        grabitateaAplikatu_nibel1();
    }
    if (player.mapa == MAPA_NIBEL2)
    {
        mugimendua_nibelak(ebentoa);
        grabitateaAplikatu_nibel2();
    }
    if (player.mapa == MAPA_NIBEL3)
    {
        mugimendua_nibelak(ebentoa);
        grabitateaAplikatu_nibel3();
    }
    if (ebentoa == TECLA_e)
    {
        int munduID = 0;
        //eraikinInterakzio(mapaHitbox);
        if (player.mapa == MAPA_GAZTELUA && player.pos.x >= 581 && player.pos.x <= 631 && player.pos.y >= 350 && player.pos.y <= 420)
        {
            irudiaKendu(munduID);
            player.mapa = MAPA_MUNDUA1;
            irudiaSortu(MUNDUA);
            player.pos.x = 68;
            player.pos.y = 72;
            if (player.pertsonaia == 1)
            {
                player.id = irudiaSortu(MARIO_GELDIRIK);
            }
            else
            {
                player.id = irudiaSortu(LUIGI_GELDIRIK);
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        else if (player.mapa == MAPA_MUNDUA1 && player.pos.x >= 345 && player.pos.x <= 395 && player.pos.y >= 150 && player.pos.y <= 195)
        {
            irudiaKendu(munduID);
            player.mapa = MAPA_NIBEL1;
            irudiaSortu(LEHENENGO_NIBELA);
            player.pos.x = 29;
            player.pos.y = 399;
            if (player.pertsonaia == 1)
            {
                player.id = irudiaSortu(MARIO_GELDIRIK);
            }
            else
            {
                player.id = irudiaSortu(LUIGI_GELDIRIK);
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        else if (player.mapa == MAPA_MUNDUA2 && player.pos.x >= 52 && player.pos.x <= 92 && player.pos.y >= 270 && player.pos.y <= 305)
        {
            irudiaKendu(munduID);
            player.mapa = MAPA_NIBEL2;
            irudiaSortu(BIGARREN_NIBELA);
            player.pos.x = 29;
            player.pos.y = 399;
            if (player.pertsonaia == 1)
            {
                player.id = irudiaSortu(MARIO_GELDIRIK);
            }
            else
            {
                player.id = irudiaSortu(LUIGI_GELDIRIK);
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        else if (player.mapa == MAPA_MUNDUA3 && player.pos.x >= 490 && player.pos.x <= 535 && player.pos.y >= 340 && player.pos.y <= 385)
        {
            irudiaKendu(munduID);
            player.mapa = MAPA_NIBEL3;
            irudiaSortu(HIRUGARREN_NIBELA);
            player.pos.x = 29;
            player.pos.y = 399;
            if (player.pertsonaia == 1)
            {
                player.id = irudiaSortu(MARIO_GELDIRIK);
            }
            else
            {
                player.id = irudiaSortu(LUIGI_GELDIRIK);
            }
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        else if (player.mapa == MAPA_MUNDUA4 && player.pos.x >= 475 && player.pos.x <= 565 && player.pos.y >= 205 && player.pos.y <= 260)
        {
            irudiaKendu(munduID);
            irudiaSortu(IRABAZI);
            egoera = bukaeraMezua(ebentoa);
        }
        else if(player.mapa == MAPA_NIBEL1 && player.pos.x >= 55 && player.pos.x <= 95 && player.pos.y >= 0 && player.pos.y <= 100)
        {
            erantzunaJaso();
        }
        else if (player.mapa == MAPA_NIBEL2 && player.pos.x >= 55 && player.pos.x <= 95 && player.pos.y >= 0 && player.pos.y <= 100)
        {
            erantzunaJaso();
        }
        else if (player.mapa == MAPA_NIBEL3 && player.pos.x >= 55 && player.pos.x <= 95 && player.pos.y >= 0 && player.pos.y <= 100)
        {
            erantzunaJaso();
        }
    }
    if (ebentoa == TECLA_ESCAPE)
    {
        egoera = pausaMenua();
    }

    return egoera;
}

void mugimendua_nibelak(int ebentoa)
{
    Mix_Chunk* saltoa = NULL;

    int hitground = 1, salto_altuera = 50, baimena = 0;
    int playerposy;

    playerposy = player.pos.y;

    if (player.mapa == MAPA_NIBEL1)
    {
        hitground = hitground_nibel1();
    }
    else if (player.mapa == MAPA_NIBEL2)
    {
        hitground = hitground_nibel2();
    }
    else if (player.mapa == MAPA_NIBEL3)
    {
        hitground = hitground_nibel3();
    }

    if (ebentoa == TECLA_w || ebentoa == TECLA_UP)
    {
        while ((player.pos.y >= playerposy - salto_altuera) && (hitground == 0))
        {
            pantailaGarbitu();
            goraAnimaz = saltoAnimazioa(goraAnimaz);
            player.pos.y -= 400 / 60;
            irudiaMugitu(player.id, player.pos.x, player.pos.y);
            irudiakMarraztu();
            SDL_RenderPresent(gRenderer);
        }
        if (hitground == 0) {
            saltoa = Mix_LoadWAV(".\\Sounds\\salto.wav");
            Mix_PlayChannel(-1, saltoa, 0);
        }
    }
    if (ebentoa == TECLA_a || ebentoa == TECLA_LEFT)
    {
        baimena = mapenHitboxak(ebentoa);
        pantailaGarbitu();
        ezkerreraAnimaz = ezkerreruntzAnimazioa(ezkerreraAnimaz);
        if (baimena == 1) {
            player.pos.x -= 9;
        }

        irudiaMugitu(player.id, player.pos.x, player.pos.y);
        irudiakMarraztu();
        SDL_RenderPresent(gRenderer);
    }
    if (ebentoa == TECLA_d || ebentoa == TECLA_RIGHT)
    {
        baimena = mapenHitboxak(ebentoa);
        pantailaGarbitu();
        eskubiAnimaz = eskubiruntzAnimazioa(eskubiAnimaz);
        if (baimena == 1) {
            player.pos.x += 9;
        }

        irudiaMugitu(player.id, player.pos.x, player.pos.y);
        irudiakMarraztu();
        SDL_RenderPresent(gRenderer);
    }
}

int beheruntzAnimazioa(int boo)
{
    if (boo == 0)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJOIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJOIZQ);
        boo = 1;
    }
    else if(boo == 1)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJOIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJOIZQ);
        boo = 2;
    }
    else if (boo == 2)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJOIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJOIZQ);
        boo = 3;
    }
    else if (boo == 3)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJODER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJODER);
        boo = 4;
    }
    else if (boo == 4)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJODER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJODER);
        boo = 5;
    }
    else if (boo == 5)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ABAJODER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ABAJODER);
        boo = 0;
    }

    return boo;
}

int ezkerreruntzAnimazioa(int boo) {
    if (boo == 0) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQDER);
        boo = 1;
    }
    else if (boo==1) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQDER);
        boo = 2;
    }
    else if (boo==2) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQDER);
        boo = 3;
    }
    else if (boo==3) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQIZQ);
        boo = 4;
    }
    else if (boo==4) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQIZQ);
        boo = 5;
    }
    else if (boo == 5) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_IZQIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_IZQIZQ);
        boo = 0;
    }
    return boo;
}

int gorunztAnimazioa(int boo) {
    if (boo == 0) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBDER);
        else if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBDER);
        boo = 1;
    }
    else if(boo == 1) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBDER);
        boo = 2;
    }
    else if(boo == 2) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBDER);
        boo = 3;
    }
    else if(boo == 3) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBIZQ);
        boo = 4;
    }
    else if(boo == 4) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBIZQ);
        boo = 5;
    }
    else if(boo == 5) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_ARRIBIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_ARRIBIZQ);
        boo = 0;
    }
    return boo;
}

int eskubiruntzAnimazioa(int boo) {
    if (boo == 0) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERDER);
        boo = 1;
    }
    else if(boo==1) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERDER);
        boo = 2;
    }
    else if (boo == 2)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERDER);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERIZQ);
        boo = 3;
    }
    else if (boo == 3)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERIZQ);
        boo = 4;
    }
    else if (boo == 4)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERIZQ);
        boo = 5;
    }
    else if (boo == 5)
    {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(SPRITE_PLAYER_DERIZQ);
        if (player.pertsonaia == 2)player.id = irudiaSortu(PLAYER_DERIZQ);
        boo = 0;
    }

    return boo;
}

int saltoAnimazioa(int boo) {
    if (boo == 0) {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(MARIO_SALTO);
        if (player.pertsonaia == 2)player.id = irudiaSortu(LUIGI_SALTO);
        boo = 1;
    }
    else {
        irudiaKendu(player.id);
        if (player.pertsonaia == 1)player.id = irudiaSortu(MARIO_SALTO);
        if (player.pertsonaia == 2)player.id = irudiaSortu(LUIGI_SALTO);
        boo = 0;
    }
    return boo;
}

int ebentuaJasoGertatuBada()
{
    int ret = 0;
    if (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode)
            {
            case SDL_SCANCODE_W:
                ret = TECLA_w;
                break;
            case SDL_SCANCODE_D:
                ret = TECLA_d;
                break;
            case SDL_SCANCODE_A:
                ret = TECLA_a;
                break;
            case SDL_SCANCODE_S:
                ret = TECLA_s;
                break;
            case SDL_SCANCODE_ESCAPE:
                ret = TECLA_ESCAPE;
                break;
            case SDL_SCANCODE_UP:
                ret = TECLA_UP;
                break;
            case SDL_SCANCODE_DOWN:
                ret = TECLA_DOWN;
                break;
            case SDL_SCANCODE_RIGHT:
                ret = TECLA_RIGHT;
                break;
            case SDL_SCANCODE_LEFT:
                ret = TECLA_LEFT;
                break;
            case SDL_SCANCODE_E:
                ret = TECLA_e;
                break;
            default:
                ret = event.key.keysym.scancode;
                break;
            }
            break;
        case SDL_QUIT:
            ret = GERTAERA_IRTEN;
            break;
        case SDL_MOUSEBUTTONUP:
            switch (event.button.button) {
            case SDL_BUTTON_LEFT:
                ret = SAGU_BOTOIA_EZKERRA;
                break;
            case SDL_BUTTON_RIGHT:
                ret = SAGU_BOTOIA_ESKUMA;
                break;
            default:
                ret = event.button.button;
                break;
            }
            break;
        case SDL_MOUSEMOTION:
            //ALDAGIA OROKOR BATEN EZARRIKO DUGU X ETA Y GERO FUNZTIO BATEKIN IRAKURTZEKO AZKEN EBENTUAREN POSIZIOA
            saguPos.x = event.motion.x;
            saguPos.y = event.motion.y;
            ret = SAGU_MUGIMENDUA;
            break;

        }
    }
    return ret;
}

POSIZIOA saguarenPosizioa() { return saguPos; }