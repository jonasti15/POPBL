#include "funtzioak.h" 
#include "kontrolak.h"
#include "menua.h"
#include "irudiak.h"

/* VIDEOA */
SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Renderer* gRenderer;
/* AUDIOA */
Mix_Music* gMusic = NULL;

TTF_Font* font = 0;
PLAYER player;

int SDLHasi()
{
    int hasieratua = 0;

    if (TTF_Init() < 0)
    {
        printf("SDL_TTF couldn't initialize!, SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        textuaGaitu();
    }
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    //Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
    }
    else
    {
        gMusic = Mix_LoadMUS(".\\Sounds\\mariobros.wav");
        if (gMusic == NULL)
        {
            printf("Ezin izan da musika kargatu. SDL_mixer Error: %s\n", Mix_GetError());
        }
        Mix_PlayMusic(gMusic, -1);

        window = SDL_CreateWindow("MUrio Bros", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        gRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            screenSurface = SDL_GetWindowSurface(window);
            hasieratua = 1;
        }
    }

    return hasieratua;
}

void textuaGaitu()
{
    font = TTF_OpenFontIndex("C:\\Windows\\Fonts\\Arial.TTF", 20, 0);
    if (!font)
    {
        printf("TTF_OpenFontIndex: %s\n", TTF_GetError());
    }
}

void textuaIdatzi(int x, int y, char* str)
{
    SDL_Surface* textSurface;
    SDL_Texture* mTexture;
    SDL_Color textColor = { 255, 255, 255 };
    SDL_Rect src, dst;

    if (font == 0)
    {
        textuaGaitu();
    }
    textSurface = TTF_RenderText_Blended(font, str, textColor);
    mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
    src.x = 0; dst.x = x;
    src.y = 0; dst.y = y;
    src.w = dst.w = textSurface->w;
    src.h = dst.h = textSurface->h;
    SDL_RenderCopy(gRenderer, mTexture, &src, &dst);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(mTexture);
}

void textuaDesgaitu()
{
    if (font != 0)
    {
        TTF_CloseFont(font);
        font = 0;
        SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, 255);
        SDL_RenderClear(gRenderer);
        irudiakMarraztu();
    }
}

int irudiaMarraztu(SDL_Texture* texture, SDL_Rect* pDest)
{
    SDL_Rect src;

    src.x = 0;
    src.y = 0;
    src.w = pDest->w;
    src.h = pDest->h;
    SDL_RenderCopy(gRenderer, texture, &src, pDest);

    return 0;
}

void bukatu()
{
    //Free the music
    Mix_FreeMusic(gMusic);
    gMusic = NULL;
    //Destroy window
    SDL_DestroyWindow(window);
    window = NULL;
    //Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

void jokuaHasi(int pertsonaia)
{
    PLAYER menu;

    if (player.pertsonaia == 1)
    {
        menu.id = irudiaSortu(LEHENENGO_PANTAILA_MARIO);
    }
    else if (player.pertsonaia == 2)
    {
        menu.id = irudiaSortu(LEHENENGO_PANTAILA_LUIGI);
    }

    SDL_RenderPresent(gRenderer);
    SDL_Delay(8000);
    irudiaKendu(menu.id);
    menu.id = irudiaSortu(LEHENENGO_PANTAILA2);


    if (player.pertsonaia == 1)
    {
        player.id = irudiaSortu(MARIO_GELDIRIK2);
        irudiaMugitu(player.id, 100, 378);
        player.pos.x = 100;
        player.pos.y = 378;
        irudiakMarraztu(MARIO_GELDIRIK2);
    }
    else if (player.pertsonaia == 2)
    {
        player.id = irudiaSortu(LUIGI_GELDIRIK2);
        irudiaMugitu(player.id, 100, 378);
        player.pos.x = 100;
        player.pos.y = 378;
        irudiakMarraztu(LUIGI_GELDIRIK2);
    }
}

void berrabiarazi()
{
    int egoera = 0, errorea;
    PLAYER menu;
    //Free the music
    Mix_FreeMusic(gMusic);
    //Destroy window
    SDL_DestroyWindow(window);
    //Quit SDL subsystems
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();

    errorea = SDLHasi();
    if (errorea == 0)
    {
        printf("Erroreak gertatu dira.");
    }
    else
    {
        menu.id = irudiaSortu(MENU);
        irudiakMarraztu();
        SDL_RenderPresent(gRenderer);
        do
        {
            egoera = hasierakomenu(menu);
        } while (egoera != GAME_OVER);
        bukatu();
    }
}