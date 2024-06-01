#ifndef _DEFS__H
#define _DEFS__H




const int SCREEN_WIDTH = 1280;//1280
const int SCREEN_HEIGHT = 640;//640
const char* WINDOW_TITLE = "Hello World!";
const int GRAVITY = -15;
const int GROUND = 540;

const int START_X = 50; //100
const int START_Y = 50; //80
const int HERO_WIDTH_PICS = 150; // 300
const int HERO_HEIGHT_PICS = 100; // 200
const int HERO_WIDTH = 40; //80
const int HERO_HEIGHT = 50; //120
const int WAITING_TIME = 10;
const int HERO_HEALTH = 3;


bool Start = false;
bool HighScore = false;
bool Menu = true;
bool EndScreen = false;

int mobHP = 10;
bool Hero_Dead = false;
int heroHP = HERO_HEALTH;
bool Coin_Taken = false;
bool Mob_Dead = false;
int point = 0;
bool isInvincible = false;
int invincibleTime = 100;
int Waiting = WAITING_TIME;
bool Saved = false;
bool attack = false;
int CoinCount = 0;

void Reset() {
     mobHP = 10;
     Hero_Dead = false;
     heroHP = HERO_HEALTH;
     Coin_Taken = false;
     Mob_Dead = false;
     point = 0;
     isInvincible = false;
     invincibleTime = 100;
     Waiting = WAITING_TIME;
     CoinCount = 0;
}

void initClip(int frames, int runClip[][4], int& runFrames) {
    for (int i = 0; i < frames; i++) {
        runClip[i][0] = 100 + 300 * i;
        runClip[i][1] = 80;
        runClip[i][2] = 300;
        runClip[i][3] = 1000;
    }
    runFrames = frames; // Number of frames in the RUN_CLIP animation
}

void initTest(int frames, int runClip[][4], int& runFrames, int w , int h , int f, int s_x , int s_y) {
    for (int i = 0; i < frames; i++) {
        runClip[i][0] = w * i + s_x;
        runClip[i][1] = h * f + s_y;
        runClip[i][2] = w;
        runClip[i][3] = h;
    }
    runFrames = frames; // Number of frames in the RUN_CLIP animation
}

void initVer(int frames, int runClip[][4], int& runFrames, int w, int h, int f, int s_x , int s_y) {
    for (int i = 0; i < frames; i++) {
        runClip[i][0] = 0 + s_x;
        runClip[i][1] = h * i + s_y;
        runClip[i][2] = w;
        runClip[i][3] = h;
    }
    runFrames = frames; // Number of frames in the RUN_CLIP animation
}




#endif