#ifndef _HERO_H_
#define _HERO_H_

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include"defs.h"
#include"graphics.h"
#include "Entity.h"
#include "Move.h"
#include <vector>
#include <cstdlib>
#include <SDL_ttf.h>
#include<string>
#include<fstream>
#include<algorithm>



using namespace std;

struct MyMan : public Graphics, public Mouse, public Sprite, public SoundManager
{
	void My_Run() {
        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP] or currentKeyStates[SDL_SCANCODE_W]) hero.turnUp();
        if (currentKeyStates[SDL_SCANCODE_DOWN] or currentKeyStates[SDL_SCANCODE_S]) hero.turnDown();
        if (currentKeyStates[SDL_SCANCODE_LEFT] or currentKeyStates[SDL_SCANCODE_A]) hero.turnLeft();
        if (currentKeyStates[SDL_SCANCODE_RIGHT] or currentKeyStates[SDL_SCANCODE_D]) hero.turnRight();
        if (currentKeyStates[SDL_SCANCODE_J]) attack = true;
	}


    void Ticking(int count) {
        Boss2.tick();
        if (count % 05 == 1) {

            knightRun.tick(), knightFall.tick(), knightJump.tick();
            knightCrouch.tick(); Coin_Float.tick(); Skull_Fly.tick(); Boss.tick(); Spit_Sprite.tick();
            Bomb_Sprite.tick(); Boom_Sprite.tick();
            knightDead.tick();
        }
        if (count % 10 == 1) {
            Mob_Walk.tick(); Mob_Attack.tick(); Mob_Dead_Sprite.tick(); knightAttack.tick();
        }
    }

    void Hero_Logic(Graphics &graphics, SoundManager &opera) {

        SDL_Rect her;
        her.x = hero.x;
        her.y = hero.y;
        her.w = hero.w;
        her.h = hero.h;
        SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);

        if (!Hero_Dead) {
            if (isInvincible) {
                SDL_RenderDrawRect(graphics.renderer, &her);
                invincibleTime--;
                if (invincibleTime == 0) {
                    isInvincible = false;
                    invincibleTime = 100;
                }
            }
            if (attack) {
                if (hero.y > GROUND) hero.y = GROUND;
                graphics.render(hero.x, hero.y, knightAttack);
                graphics.play(opera.gAttack);
                attackRange.x = hero.x + HERO_WIDTH;
                attackRange.y = hero.y;
                if (Collision(attackRange, mob)) {
                    mobHP--;
                    if (mobHP == 0) {
                        Mob_Dead = true;

                        mobHP = 20;
                    }
                }
                for (int i = 0; i <= point / 100; i++) {
                    if (Collision(attackRange, skull_mouse[i])) {
                        skull_mouse[i].x = rand() % 1280 + 1280;
                        skull_mouse[i].y = rand() % 500;
                    }
                }
                attack = false;
            }
            else if (hero.Crouch == true) {

                graphics.render(hero.x, hero.y, knightCrouch);
                hero.Crouch = false;
            }
            else if (hero.dy == 0 && hero.y >= 455) {
                if (hero.y > GROUND) hero.y = GROUND;
                graphics.render(hero.x, hero.y, knightRun);
                /*graphics.play(gRun);*/
            }
            else if (hero.dy > 0 && hero.y < GROUND) {
                if (hero.y > GROUND) hero.y = GROUND;
                graphics.render(hero.x, hero.y, knightFall);
            }
            else if (hero.dy < 0) {
                if (hero.y > GROUND) hero.y = GROUND;
                graphics.render(hero.x, hero.y, knightJump);
                if(hero.y >= GROUND - 10 && hero.dy < 0) graphics.play(opera.gJump);
            }
        }
        if (Hero_Dead) {
            cerr << heroHP << endl;
            if (Waiting == WAITING_TIME) {

                graphics.play(opera.gHitted);
            } graphics.render(hero.x, hero.y - 40, knightDead);

            if (heroHP) {
                heroHP--;
                isInvincible = true;
                Hero_Dead = false;
            }
            if (heroHP == 0) {
                if (Waiting == WAITING_TIME) graphics.play(opera.gLose);
                Waiting--; heroHP = 0;
                cerr << Waiting << endl;
                if (Waiting == 0) {
                    EndScreen = true; Start = false; HighScore = false; Menu = false;
                    
                }
            }
        }
        hero.SpeedUp(point / 100);
        hero.move();
        hero.dx = 0;
        hero.dy = 0;

        if (!isInvincible) {
            if (Collision(hero, boss) or Collision(hero, mob) or Collision(hero, Spit_Mouse)) {
                Hero_Dead = true;
            }
        }
   }


    void Mob_Logic(Graphics& graphics, SoundManager& opera, int count) {
        if (!Mob_Dead) {
            mob.dx = -MOB_SPEED;
            mob.move();
            graphics.render(mob.x, mob.y, Mob_Walk);
            for (int i = 0; i <= point / 100; i++) {
                if (Collision(mob, boss) or Collision(mob, skull_mouse[i]) or Collision(mob, Spit_Mouse)) {

                    Mob_Dead = true;
                }
            }

        }
        else {
            graphics.render(mob.x, mob.y, Mob_Dead_Sprite);
            if (count % 125 == 1) {
                mob.x = rand() % 600 + 1300;
                Mob_Dead = false;
            }
        }


        //boss settings
        graphics.render(boss.x, boss.y, Boss);
        boss.Attract();
        boss.move();


        graphics.render(Spit_Mouse.x, Spit_Mouse.y, Spit_Sprite);
        Spit_Mouse.dx = MOB_SPEED + 5;
        if (Spit_Mouse.x >= 1400 && count % 400 == 2) {
            Spit_Mouse.x = 100;
        }
        Spit_Mouse.SpeedUp(point / 100);
        Spit_Mouse.move();

        int show = point / 100;
        if (show >= 5) show = 5;
        for (int i = 0; i < show; i++) {

            if (Bomb_Mouse[i].y < 500) {
                graphics.render(Bomb_Mouse[i].x, Bomb_Mouse[i].y, Bomb_Sprite);
                Bomb_Mouse[i].dy = 3;
                Bomb_Mouse[i].SpeedUp(point / 100);
            }
            else {
                Bomb_Mouse[i].y = 500;
                Bomb_Mouse[i].dy = 0;
                graphics.render(Bomb_Mouse[i].x, Bomb_Mouse[i].y, Boom_Sprite);
                if (count % 100 == 1) {
                    Bomb_Mouse[i].x = rand() % 900 + 300;
                    Bomb_Mouse[i].y = -1200 + rand() % 300;
                }
            }
            Bomb_Mouse[i].move();



            skull_mouse[i].Fly();
            skull_mouse[i].SpeedUp(point / 100);
            skull_mouse[i].move();
            graphics.render(skull_mouse[i].x, skull_mouse[i].y, Skull_Fly);
            if (!isInvincible) {
                if (Collision(hero, skull_mouse[i]) or Collision(hero, Bomb_Mouse[i])) Hero_Dead = true;
            }


        }
        SDL_Texture* HCount = graphics.loadTexture("image/Heart.png");
        for (int i = 0; i <= heroHP ; i++) {
            graphics.renderTexture(HCount, 1280 - 40 * i, 50);
        }
    }


};





#endif 