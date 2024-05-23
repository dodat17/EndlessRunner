#ifndef _FILE_H_
#define _FILE_H_

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

vector<int> v;
void TakeInputScore() {
    ifstream file("Asset/Score.txt");
    if (!file.is_open()) {
        cout << "jdjkdfuk" << endl;
    }
    while (!file.eof()) {
        int score;
        file >> score;
        v.push_back(score);
    }
    sort(v.begin(), v.end());
    file.close();
}

void SaveScore() {
    ofstream file("Asset/Score.txt");
    for (int i = v.size() - 1; i >= v.size() - 3; i--) {
        file << v[i] << " ";
    }
    file.close();
}





#endif 