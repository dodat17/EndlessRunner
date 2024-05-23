#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "defs.h"
#include "Entity.h"
#include "Move.h"
#include <vector>
#include <SDL_ttf.h>


using namespace std;



class Graphics {
public:
    SDL_Rect Start_Button, HiScore_Button, Quit_Button, ComeBack , Re_Button , Back_Button;
    SDL_Renderer* renderer;
    SDL_Window* window;
 


    Graphics() {
        Start_Button.x = 500; HiScore_Button.x = 500; Quit_Button.x = 500; ComeBack.x = 20; Re_Button.x = 416; Back_Button.x = 683;
        Start_Button.y = 250; HiScore_Button.y = 370; Quit_Button.y = 490; ComeBack.y = 20; Re_Button.y = 432; Back_Button.y = 432;
        Start_Button.w = 250; HiScore_Button.w = 250; Quit_Button.w = 250; ComeBack.w = 90; Re_Button.w = 160; Back_Button.w = 160;
        Start_Button.h = 100; HiScore_Button.h = 100; Quit_Button.h = 100; ComeBack.h = 80; Re_Button.h = 50; Back_Button.h = 50;
    }
    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    void init() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit("SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
            SDL_RENDERER_PRESENTVSYNC);


        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        // Music  
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            logErrorAndExit("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
        }
        //ttf
        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ",
                TTF_GetError());
        }


    }


    //font
    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont(path, size);
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load font %s", TTF_GetError());
        }
        return gFont;
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface = TTF_RenderText_Solid(font, text, textColor);
        if (textSurface == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textSurface);
        if (texture == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Create texture from text %s", SDL_GetError());
        }

        SDL_FreeSurface(textSurface);
        return texture;
    }


    void prepareScene()
    {
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
    }

    void prepareScene(SDL_Texture* background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture* loadTexture(const char* filename)
    {
        // SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture* texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture* texture, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    void render(const ScrollingBackground& bgr) {
        renderTexture(bgr.texture, bgr.scrollingOffset, 0);
        renderTexture(bgr.texture, bgr.scrollingOffset - bgr.width, 0);
    }

    void render(int x, int y, const Sprite& sprite) {
        const SDL_Rect* clip = sprite.getCurrentClip();
        SDL_Rect renderQuad = { x, y, clip->w, clip->h };
        SDL_RenderCopy(renderer, sprite.texture, clip, &renderQuad);
    }



    void quit()
    {
        Mix_Quit();
        IMG_Quit();

        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        TTF_Quit();
    }

    Mix_Music* loadMusic(const char* path)
    {
        Mix_Music* gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }
    void play(Mix_Music* gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic(gMusic, -1);
        }
        else if (Mix_PausedMusic() == 1) {
            Mix_ResumeMusic();
        }
    }

    Mix_Chunk* loadSound(const char* path) {
        Mix_Chunk* gChunk = Mix_LoadWAV(path);
        if (gChunk == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                "Could not load sound! SDL_mixer Error: %s", Mix_GetError());
        }
        return gChunk;
    }

    void play(Mix_Chunk* gChunk) {
        if (gChunk != nullptr) {
            Mix_PlayChannel(-1, gChunk, 0);
        }
    }


};


class SoundManager{
public:
    Mix_Music* gMusic;
    Mix_Chunk* gJump;
    Mix_Chunk* gAttack;
    Mix_Chunk* gHitted;
    Mix_Chunk* gLazer;
    Mix_Chunk* gLose;
    Mix_Chunk* cAlarm;
    Mix_Chunk* cDrop;
    Mix_Chunk* cExplode;
    Mix_Chunk* cMenu;

    void loadSounds(Graphics& graphics) {
        gMusic = graphics.loadMusic("Asset\\Music\\Revenge.wav");
        gJump = graphics.loadSound("Asset\\Chunk\\jump.wav");
        gAttack = graphics.loadSound("Asset\\Chunk\\Attack.mp3");
        gHitted = graphics.loadSound("Asset\\Chunk\\hitted.wav");
        gLazer = graphics.loadSound("Asset\\Chunk\\lazer.mp3");
        gLose = graphics.loadSound("Asset\\Chunk\\lose.wav");
        cAlarm = graphics.loadSound("Asset\\Chunk\\alarm.wav");
        cDrop = graphics.loadSound("Asset\\Chunk\\drop.wav");
        cExplode = graphics.loadSound("Asset\\Chunk\\explode.wav");
        cMenu = graphics.loadSound("Asset\\Chunk\\Menu.wav");
    }
};





#endif // _GRAPHICS__H