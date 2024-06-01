#ifndef MOVE_H
#define MOVE_H

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "Entity.h"

using namespace std;

#define INITIAL_SPEED_X 10;
#define INITIAL_SPEED_Y 50;//400
#define MOB_SPEED 2;
#define SKULL_SPEED 7;


struct Mouse {
public:
    bool Crouch;
    int x, y;
    int w, h;
    int dx = 0, dy = 0;
    int speedX = INITIAL_SPEED_X;
    int speedY = INITIAL_SPEED_Y;
    void move() {
        if (Waiting == WAITING_TIME) {
            x += dx;
            y += dy;
        }

    }
    void SpeedUp(int speed) {
        if (dx > 0) dx += speed;
        else if(dx <0) dx -= speed;
        if (dy > 0) dy += speed;
        else if (dy < 0) dy -= speed;

    }
    void initLoc(int a,int b,int c,int d) {
        x = a;
        y = b;
        w = c;
        h = d;
    }
    void Inter() {
        if (y <= 530) dy -= GRAVITY;
        else dy = 0;

    }
    void turnUp() { 
        //dy = -speedY;
        if(y >= GROUND - 300) dy = -speedY;
        //if (y >= GROUND - 10) dy = -speedY;
        if (y <= 0) {
            y = 0;
            dy = 0;
        }
        // else dy = 0;
        
    }
    void turnDown() {
        if (y < GROUND) dy = speedY;
        else {
            Crouch = true;
            dy = 0;
        }
        
    }
    void turnLeft() {
      //  if (y < 470 - 15) dy -= GRAVITY;
        dx = -speedX;
    }
    void turnRight() {
       // if (y < GROUND - GRAVITY) dy -= GRAVITY;
        dx = speedX;
    }
    void Flyup(int a ) {
        /*if (dy == 0) dy = -1;
        if (y >500 && dy == 1) dy = -1;
        else if(y <0 && dy == -1) dy = 1;*/

        if (a % 90 == 0) {
            y = 460;
        }
        if (a % 90 == 30) {
             y = 470 / 2;
        }
        if (a % 90 == 60) {
             y = 0;
        }
    }
    void Attract() {
        if (x >= -100) 
        {
            dx = -1;
            cerr << "lui ve" << endl;
        }
        if (x <= -250) {
            cerr << "tien len" << endl;
            dx = +1;
        }
        
        
    }
    void Fly() {
        dx = -SKULL_SPEED;
        if (x < 0) {
            x = rand() % 1280 + 2500;
            y = rand() % 400 + 100;
        }
    }

    void BossRun() {
        dx = INITIAL_SPEED_X;
        if (x == SCREEN_WIDTH / 2 - 100) dx = 0;
    }

    
    
};

bool Collision(Mouse rect1, Mouse rect2) {

    if (rect1.x + rect1.w >= rect2.x and rect2.x + rect2.w >= rect1.x and
        rect1.y + rect1.h >= rect2.y and rect2.y + rect2.h >= rect1.y) {

        return true;
    }
    else {
        
        return false;
    }
}

bool CheckClick(int s_x , int s_y, SDL_Rect a) {
    if (s_x >= a.x && s_x <= a.x + a.w && a.y <= s_y && a.y + a.h >= s_y) {
        
        return 1;
    } return 0;
}

#endif // MOVE_H