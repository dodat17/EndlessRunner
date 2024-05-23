#ifndef _ENTITY_H_
#define _ENTITY_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include"defs.h"
#include "graphics.h"
#include "Entity.h"
#include "Move.h"
#include <vector>
#include <cstdlib>


using namespace std;

int RUN_CLIP[10][4], DEAD_CLIP[10][4], FALL_CLIP[3][4], JUMP_CLIP[3][4], ATTACK_CLIP[4][4], CROUCH_CLIP[8][4], SPIT_CLIP[4][4], BOSS2_CLIP[18][4]; // Define RUN_CLIP array
int BOSS_CLIP[15][4], LAZER_CLIP[14][4], MOB_CLIP[8][4], MOB_ATTACK[8][4], STORM_CLIP[17][4], MOB_DEAD_CLIP[7][4], COIN_CLIP[7][4], SKULL_CLIP[8][4];
int RUN_FRAMES, DEAD_FRAMES, FALL_FRAMES, JUMP_FRAMES, ATTACK_FRAMES, BOSS_FRAMES, MOB_FRAMES, LAZER_FRAMES, COIN_FRAMES, SKULL_FRAMES, SPIT_FRAMES, BOSS2_FRAMES; // Declare RUN_FRAMES constant
vector<int> mob_frames(3);
vector<int> Comboframes(8);

int BOMB_CLIP[4][4], BOMB_FRAMES, BOOM_CLIP[6][4], BOOM_FRAMES;

struct ScrollingBackground {

    SDL_Texture* texture;
    int scrollingOffset = 0;
    int width, height;

    void setTexture(SDL_Texture* _texture) {
        texture = _texture;
        SDL_QueryTexture(texture, NULL, NULL, &width, &height);
    }

    void scroll(int distance) {
        scrollingOffset -= distance;
        if (scrollingOffset < 0) { scrollingOffset = width; }
    }
};

struct Sprite {
    SDL_Texture* texture;
    vector<SDL_Rect> clips;
    int currentFrame = 0;

    void init(SDL_Texture* _texture, int frames, int _clips[][4]) {
        texture = _texture;
        SDL_Rect clip;
        for (int i = 0; i < frames; i++) {
            clip.x = _clips[i][0];
            clip.y = _clips[i][1];
            clip.w = _clips[i][2];
            clip.h = _clips[i][3];
            clips.push_back(clip);
        }
    }
    void tick() {
        if (clips.size() != 0) currentFrame = (currentFrame + 1) % clips.size();
        else currentFrame = 1;
    }

    const SDL_Rect* getCurrentClip() const {
        return &(clips[currentFrame]);
    }
};


ScrollingBackground background, background2, background3;
vector< ScrollingBackground> back(12);

Mouse hero, boss, mob /*lazer*/, attackRange, Storm_Attack, coin1, Spit_Mouse, Boss2_Mouse;
Mouse Bomb_Mouse[5], skull_mouse[5];
void MouseLoc() {
    hero.initLoc(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, HERO_WIDTH, HERO_HEIGHT);
    boss.initLoc(-250, 350, 240, 270);
    mob.initLoc(1100, 473, 93, 140);
  //  lazer.initLoc(0 + 150, SCREEN_HEIGHT - 300, 700 * 2, 1500 / 15);
    attackRange.initLoc(SCREEN_WIDTH / 2 + 80, SCREEN_HEIGHT / 2, 50, HERO_HEIGHT);
    Storm_Attack.initLoc(0, 350, 87 * 4, 720);
    coin1.initLoc(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 50, 50);
    
    Spit_Mouse.initLoc(boss.x + 240, boss.y + 200, 732 / 12, 21);
    for (int i = 0; i < 5; i++) {
        Bomb_Mouse[i].initLoc(300 + rand() % 900, 0, /*104*/30, 40/*112*/);
        skull_mouse[i].initLoc(1300, SCREEN_HEIGHT / 2, 96, 112);
    }
    Boss2_Mouse.initLoc(-250, 400, 212, 209);


}


void FramesInit() {
    //knight
    initTest(10, RUN_CLIP, Comboframes[6], HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 6, START_X, START_Y);
    initTest(3, FALL_CLIP, Comboframes[4], HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 4, START_X, START_Y);
    initTest(3, JUMP_CLIP, Comboframes[5], HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 5, START_X, START_Y);
    initTest(4, ATTACK_CLIP, ATTACK_FRAMES, HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 1, START_X, START_Y);
    initTest(8, CROUCH_CLIP, Comboframes[3], HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 3, START_X, START_Y);
    initTest(10, DEAD_CLIP, DEAD_FRAMES, HERO_WIDTH_PICS, HERO_HEIGHT_PICS, 0, 0, 0);

    //mob
    initTest(18, BOSS2_CLIP, BOSS2_FRAMES, 212, 209, 0, 0, 0);
    initTest(17, STORM_CLIP, mob_frames[1], 87 * 4, 720, 0, 0, 80);
    initTest(8, MOB_DEAD_CLIP, mob_frames[2], 280, 120, 0, 150, 810);
    initTest(8, MOB_ATTACK, mob_frames[0], 280, 1120 - 930, 0, 150, 930);
    initTest(15, BOSS_CLIP, BOSS_FRAMES, 299, 248, 0, 0, 0); // 500,500,5,120,120
    initTest(8, MOB_CLIP, MOB_FRAMES, 1120 / 8 * 2, 744 / 8 * 2, 1, 150, 70);
    //initVer(14, LAZER_CLIP, LAZER_FRAMES, 700 * 2, 1500 / 15 * 2, 0, 60, 30);
    initTest(8, SKULL_CLIP, SKULL_FRAMES, 96, 112, 0, 0, 0);
    initTest(4, SPIT_CLIP, SPIT_FRAMES, 732 / 12, 21, 0, 0, 0);

    // bomb
    initTest(4, BOMB_CLIP, BOMB_FRAMES, 52*2, 56*2, 0, 40, 40);
    initTest(6, BOOM_CLIP, BOOM_FRAMES, 52*2, 56*2, 0, 10, 20);
    //coin
    initTest(7, COIN_CLIP, COIN_FRAMES, 50, 50, 0, 5, 5);

}

Sprite knightRun, knightFall, knightDead, knightJump, knightAttack, knightCrouch;
Sprite Boss, Boss2 /*Lazer*/, Mob_Walk, Mob_Attack, Storm, Mob_Dead_Sprite, Coin_Float, Skull_Fly, Spit_Sprite, Bomb_Sprite , Boom_Sprite;


//Mix_Music* gMusic;
//
//Mix_Music* gMusic,* gJump,* gAttack,* gHitted,* gLazer,* gLose,* cAlarm,* cDrop,* cExplode,* cMenu;





#endif // _ENTITY_H_
