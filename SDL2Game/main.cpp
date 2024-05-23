#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include"defs.h"
#include"graphics.h"
#include "Entity.h"
#include "File.h"
#include "Move.h"
#include "Hero.h"
#include <vector>
#include <cstdlib>
#include <SDL_ttf.h>
#include<string>
#include<fstream>
#include<algorithm>



using namespace std;

Graphics graphics;

void backgroundTexture() {
    background.setTexture(graphics.loadTexture("image/background/background_layer_1.png"));
    background2.setTexture(graphics.loadTexture("image/background/background_layer_2.png"));
    background3.setTexture(graphics.loadTexture("image/background/background_layer_3.png"));
    back[0].setTexture(graphics.loadTexture("image/background/00.png"));
    back[1].setTexture(graphics.loadTexture("image/background/01.png"));
    back[2].setTexture(graphics.loadTexture("image/background/02.png"));
    back[3].setTexture(graphics.loadTexture("image/background/03.png"));
    back[4].setTexture(graphics.loadTexture("image/background/04.png"));
    back[5].setTexture(graphics.loadTexture("image/background/05.png"));
    back[6].setTexture(graphics.loadTexture("image/background/06.png"));
    back[7].setTexture(graphics.loadTexture("image/background/07.png"));
    back[8].setTexture(graphics.loadTexture("image/background/08.png"));
    back[9].setTexture(graphics.loadTexture("image/background/09.png"));
    back[10].setTexture(graphics.loadTexture("image/background/10.png"));
    back[11].setTexture(graphics.loadTexture("image/background/11.png"));
}

void SpriteInit() {
    //knight
    knightRun.init(graphics.loadTexture("image/Knight/knight.png"), Comboframes[6], RUN_CLIP);
    knightFall.init(graphics.loadTexture("image/Knight/knight.png"), Comboframes[4], FALL_CLIP);
    knightDead.init(graphics.loadTexture("image/Knight/dead.png"), DEAD_FRAMES, DEAD_CLIP);
    knightJump.init(graphics.loadTexture("image/Knight/knight.png"), Comboframes[5], JUMP_CLIP);
    knightAttack.init(graphics.loadTexture("image/Knight/knight.png"), ATTACK_FRAMES, ATTACK_CLIP);
    knightCrouch.init(graphics.loadTexture("image/Knight/knight.png"), Comboframes[3], CROUCH_CLIP);


    //mob
    Boss.init(graphics.loadTexture("image/Monster/Jumping.png"), BOSS_FRAMES, BOSS_CLIP);
    Boss2.init(graphics.loadTexture("image/Monster/boss2.png"), BOSS2_FRAMES, BOSS2_CLIP);
    Mob_Walk.init(graphics.loadTexture("image/Monster/Mob1.png"), MOB_FRAMES, MOB_CLIP);
    Mob_Attack.init(graphics.loadTexture("image/Monster/Mob.png"), mob_frames[0], MOB_ATTACK);
   // Lazer.init(graphics.loadTexture("image/Monster/LazerR.png"), LAZER_FRAMES, LAZER_CLIP);
    Storm.init(graphics.loadTexture("image/Monster/Storm.png"), mob_frames[1], STORM_CLIP);
    Mob_Dead_Sprite.init(graphics.loadTexture("image/Monster/Mob.png"), mob_frames[2], MOB_DEAD_CLIP);
    Coin_Float.init(graphics.loadTexture("image/Coin.png"), COIN_FRAMES, COIN_CLIP);
    Skull_Fly.init(graphics.loadTexture("image/Monster/skull.png"), SKULL_FRAMES, SKULL_CLIP);
    Spit_Sprite.init(graphics.loadTexture("image/Monster/spit.png"), SPIT_FRAMES, SPIT_CLIP);
    Bomb_Sprite.init(graphics.loadTexture("image/Monster/bomb.png"), BOMB_FRAMES, BOMB_CLIP);
    Boom_Sprite.init(graphics.loadTexture("image/Monster/boom.png"), BOOM_FRAMES, BOOM_CLIP);
}



int main(int argc,char *argv[]){ 
    graphics.init();

    //scrolling background
    backgroundTexture();
    
    //Music and Chunk
    SoundManager opera;
    opera.loadSounds(graphics);

    //handle event
    SDL_Event event;
    bool quit = false;
    
    // initialize the frames
    FramesInit();
  
    //declare sprite
    SpriteInit();

    //font
    TTF_Font* font = graphics.loadFont("Asset/Score.ttf", 75);;
    SDL_Color color = { 255, 255, 0, 0 };
    
    //score
    TakeInputScore();
    
    
    int count = 1;
    
   
    SDL_Texture *Intro = graphics.loadTexture("image/Intro.png");
    SDL_Texture* HScore = graphics.loadTexture("image/HighScore.jpg");
    SDL_Texture* EScreen = graphics.loadTexture("image/EndGame.jpg");
    SDL_Texture* HCount = graphics.loadTexture("image/Heart.png");

    MyMan Jeff;

    while (!quit) {
        
        while (SDL_PollEvent(&event) && Menu) {
            if (event.type == SDL_QUIT) quit = true;
            
            if (!Start) {
                int s_x, s_y;
                SDL_GetMouseState(&s_x, &s_y);
                graphics.renderTexture(Intro, 0, 0);
                graphics.presentScene();
                if (event.type == SDL_MOUSEBUTTONDOWN) {
                    if (CheckClick(s_x, s_y, graphics.Start_Button)) {
                        graphics.play(opera.cMenu);
                        Start = true; HighScore = false; Menu = false;
                        Reset(); count = 1; MouseLoc();
                    }
                    if (CheckClick(s_x, s_y, graphics.HiScore_Button)) {
                        graphics.play(opera.cMenu);
                        Start = false; HighScore = true; Menu = false;
                    }
                    if (CheckClick(s_x, s_y, graphics.Quit_Button)) {
                        graphics.play(opera.cMenu);
                        quit = true; Menu = false;
                    }
                }


            }
        }
        if (HighScore) {
            graphics.renderTexture(HScore, 0, 0);
            //graphics.presentScene();
            
            int s_x, s_y;
            SDL_GetMouseState(&s_x, &s_y);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (CheckClick(s_x, s_y, graphics.ComeBack)) {
                    graphics.play(opera.cMenu);
                    Start = false; HighScore = false; Menu = true;
                }
            }
            

            for (int i = 0; i < 3; i++) {
                color = { 255, 0, 0, 0 };
                int x = v[v.size()-1-i];
                if (i == 0) {
                    SDL_Texture* text = graphics.renderText("Rank 1: ", font, color);
                    graphics.renderTexture(text, SCREEN_WIDTH / 2 - 200, 200 + 100 * i);
                }
                else if (i == 1) {
                    SDL_Texture* text = graphics.renderText("Rank 2: ", font, color);
                    graphics.renderTexture(text, SCREEN_WIDTH / 2 - 200, 200 + 100 * i);
                }
                else {
                    SDL_Texture* text = graphics.renderText("Rank 3: ", font, color);
                    graphics.renderTexture(text, SCREEN_WIDTH / 2 - 200, 200 + 100 * i);
                }


                string s = to_string(x);
                SDL_Texture* HiScore = graphics.renderText(s.c_str(), font, color);
                graphics.renderTexture(HiScore, SCREEN_WIDTH/2 + 100, 200 + 100*i);
                
            }
            graphics.presentScene();


        }
        if (EndScreen) {
            graphics.renderTexture(EScreen, 0, 0);
            color = { 255, 0, 0, 0 };
            SDL_Texture* text = graphics.renderText("Your Score: ", font, color);
            graphics.renderTexture(text, SCREEN_WIDTH / 2 - 200, 275);

            string s = to_string(point);
            SDL_Texture* HiScore = graphics.renderText(s.c_str(), font, color);
            graphics.renderTexture(HiScore, SCREEN_WIDTH / 2 + 100, 275);

            if (!Saved) {
                v.push_back(point);
                sort(v.begin(), v.end());
                cout << v[v.size() - 1] << endl;
                SaveScore();
                Saved = true;
            }
            

            int s_x, s_y;
            SDL_GetMouseState(&s_x, &s_y);
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                if (CheckClick(s_x, s_y, graphics.Re_Button)) {
                    graphics.play(opera.cMenu);
                    Start = true; HighScore = false; Menu = false; EndScreen = false;
                    Reset(); count = 1; MouseLoc(); Saved = false;
                }
                if (CheckClick(s_x, s_y, graphics.Back_Button)) {
                    graphics.play(opera.cMenu);
                    Start = false; HighScore = false; Menu = true; EndScreen = false;
                    Saved = false;
                }
            }

            graphics.presentScene();
        }
        if (Start) {
            graphics.prepareScene();

            point = count / 5;

            for (int i = 11; i  >= 4; i--) {
                graphics.render(back[i]);
            }
            if (point >= 100) {
                graphics.render(Boss2_Mouse.x, Boss2_Mouse.y, Boss2);
                Boss2_Mouse.BossRun();
                Boss2_Mouse.move();
            }
            if(point == 100) graphics.play(opera.cAlarm);
            for (int i = 3; i >= 0; i--) {
                graphics.render(back[i]);
            }

            color = { 255, 255, 0, 0 };
            string s = to_string(point);
            SDL_Texture* Score = graphics.renderText(s.c_str(), font, color);
            graphics.renderTexture(Score, 100, 100);

            //const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
            //if (currentKeyStates[SDL_SCANCODE_UP] or currentKeyStates[SDL_SCANCODE_W]) hero.turnUp();
            //if (currentKeyStates[SDL_SCANCODE_DOWN] or currentKeyStates[SDL_SCANCODE_S]) hero.turnDown();
            //if (currentKeyStates[SDL_SCANCODE_LEFT] or currentKeyStates[SDL_SCANCODE_A]) hero.turnLeft();
            //if (currentKeyStates[SDL_SCANCODE_RIGHT] or currentKeyStates[SDL_SCANCODE_D]) hero.turnRight();
            //if (currentKeyStates[SDL_SCANCODE_J]) attack = true;
            Jeff.My_Run();
                       
            //Boss2.tick();
            //if (count % 05 == 1) {
            //    knightRun.tick(), knightFall.tick(), knightJump.tick();
            //    knightCrouch.tick(); Coin_Float.tick(); Skull_Fly.tick(); Boss.tick(); Spit_Sprite.tick();
            //    Bomb_Sprite.tick(); Boom_Sprite.tick(); 
            //     knightDead.tick();
            //}
            //if (count % 10 == 1) {
            //    Mob_Walk.tick(); Mob_Attack.tick(); Mob_Dead_Sprite.tick(); knightAttack.tick();
            //}
            Jeff.Ticking(count);

            count += 1;

            //hitbox
            //SDL_Rect her;
            //her.x = hero.x; 
            //her.y = hero.y; 
            //her.w = hero.w; 
            //her.h = hero.h; 
            //SDL_SetRenderDrawColor(graphics.renderer, 0, 255, 0, 255);
            Jeff.Hero_Logic(graphics,opera);

            
            if (!Coin_Taken) {
                graphics.renderTexture(HCount, coin1.x, coin1.y);
                //graphics.render(coin1.x, coin1.y, Coin_Float);
                if (Collision(hero, coin1)) {
                    Coin_Taken = true;
                    CoinCount++;
                }
            }
            else {
                coin1.x = 300 + rand() % 900;
                coin1.y = 100+ rand() % 400;
                if(count % 500 == 1) Coin_Taken = false;
                if (CoinCount % 5 == 2) {
                    heroHP++;
                    CoinCount = 0;
                }
            }


            
            //if (!Hero_Dead) {
            //    if (isInvincible) {
            //        SDL_RenderDrawRect(graphics.renderer, &her);
            //        invincibleTime--;
            //        if (invincibleTime == 0) {
            //            isInvincible = false;
            //            invincibleTime = 100;
            //        }
            //    }
            //    if (attack) {
            //        if (hero.y > GROUND) hero.y = GROUND;
            //        graphics.render(hero.x, hero.y, knightAttack);
            //        graphics.play(opera.gAttack);
            //        attackRange.x = hero.x + HERO_WIDTH;
            //        attackRange.y = hero.y;
            //        if (Collision(attackRange, mob)) {
            //            mobHP--;
            //            if (mobHP == 0) {
            //                Mob_Dead = true;
            //                
            //                mobHP = 20;
            //            }
            //        }
            //        for (int i = 0; i <= point/100; i++) {
            //            if (Collision(attackRange, skull_mouse[i])) {
            //                skull_mouse[i].x = rand() % 1280 + 1280;
            //                skull_mouse[i].y = rand() % 500;
            //            }
            //        }
            //        attack = false;
            //    }
            //    else if (hero.Crouch == true) {
            //        
            //        graphics.render(hero.x, hero.y, knightCrouch);
            //        hero.Crouch = false;
            //    }
            //    else if (hero.dy == 0 && hero.y >= 455) {
            //        if (hero.y > GROUND) hero.y = GROUND;
            //        graphics.render(hero.x, hero.y, knightRun);
            //        /*graphics.play(gRun);*/
            //    }
            //    else if (hero.dy > 0 && hero.y < GROUND) {
            //        if (hero.y > GROUND) hero.y = GROUND;
            //        graphics.render(hero.x, hero.y, knightFall);
            //    }
            //    else if (hero.dy < 0) {
            //        if (hero.y > GROUND) hero.y = GROUND;
            //        graphics.render(hero.x, hero.y, knightJump);
            //        graphics.play(opera.gJump);
            //    }  
            //}
            //if (Hero_Dead) {
            //    cerr << heroHP << endl;
            //    if (Waiting == WAITING_TIME) {
            //        
            //        graphics.play(opera.gHitted);
            //    } graphics.render(hero.x, hero.y - 40, knightDead);
            //        
            //        if (heroHP) {
            //            heroHP--;
            //            isInvincible = true;
            //            Hero_Dead = false; 
            //        }
            //        if(heroHP == 0) {
            //            if(Waiting == WAITING_TIME) graphics.play(opera.gLose);
            //            Waiting--; heroHP = 0;
            //            cerr << Waiting << endl;
            //            if (Waiting == 0) {
            //                EndScreen = true; Start = false; HighScore = false; Menu = false;
            //                continue;
            //            }
            //        }
            //}

            Jeff.Mob_Logic(graphics, opera, count);
            //if (!Mob_Dead) {
            //    mob.dx = -MOB_SPEED;
            //    mob.move();
            //    graphics.render(mob.x, mob.y, Mob_Walk);
            //    for(int i =0 ; i <= point/100 ; i++){
            //        if (Collision(mob, boss) or Collision(mob, skull_mouse[i]) or Collision(mob, Spit_Mouse)) {
            //            Mob_Dead = true;
            //        }
            //    }
            //}
            //else {
            //    graphics.render(mob.x, mob.y, Mob_Dead_Sprite);
            //    if (count % 125 == 1) {
            //        mob.x = rand()%600 + 1300;
            //        Mob_Dead = false;
            //    }
            //}
            ////boss settings
            //graphics.render(boss.x, boss.y, Boss);
            //boss.Attract();
            //boss.move();
            //
            //      
            //graphics.render(Spit_Mouse.x, Spit_Mouse.y, Spit_Sprite);
            //Spit_Mouse.dx = MOB_SPEED + 5;
            //Spit_Mouse.SpeedUp(point / 100);
            //Spit_Mouse.move(); 
            //int show = point / 100;
            //if (show >= 5) show = 5;
            //for (int i = 0; i < show; i++) {
            //        
            //    if (Bomb_Mouse[i].y < 500) {
            //        graphics.render(Bomb_Mouse[i].x, Bomb_Mouse[i].y, Bomb_Sprite);
            //        Bomb_Mouse[i].dy = 3;
            //        Bomb_Mouse[i].SpeedUp(point / 100);
            //    }
            //    else {
            //        Bomb_Mouse[i].y = 500;
            //        Bomb_Mouse[i].dy = 0;
            //        graphics.render(Bomb_Mouse[i].x, Bomb_Mouse[i].y, Boom_Sprite);
            //        if (count % 100 == 1) {
            //            Bomb_Mouse[i].x = rand() % 900 + 300;
            //            Bomb_Mouse[i].y = -900 + rand() % 500;
            //        }
            //    }
            //    Bomb_Mouse[i].move();
            //    skull_mouse[i].Fly();
            //    skull_mouse[i].SpeedUp(point / 100);
            //    skull_mouse[i].move();
            //    graphics.render(skull_mouse[i].x, skull_mouse[i].y, Skull_Fly);
            //    if (!isInvincible) {
            //        if (Collision(hero, skull_mouse[i]) or Collision(hero, Bomb_Mouse[i])) Hero_Dead = true;
            //    }
            //    
            //}
            //mob
 
           
            
            SDL_Delay(10);

            for (int i = 0; i < 12; i++) {
                back[i].scroll(hero.speedX + i + -6);
            }

            graphics.presentScene();
            SDL_Delay(10);
            hero.Inter();





        }

        
        
    }
    
    

    

    SDL_DestroyTexture(background.texture);
    SDL_DestroyTexture(background2.texture);
    SDL_DestroyTexture(background3.texture);
    
   // SDL_DestroyTexture(helloText);
    TTF_CloseFont(font);

    
    graphics.quit();

    return 0;
}

