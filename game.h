#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <stdlib.h>
#include "potter.h"
#include "traal.h"
#include"gnome.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include "ncurseslib.h"
#include <fstream>


using namespace std;

class Game{
    private:
      int nfreespace;
      Potter *player;
      Traal *traal;
      Gnome *gnome;
      bool endgame = false, wingame = false;
      int score;
      vector<vector<int>> gamemap;
      WINDOW *gamewin, *screen;
    public:
      Game(int freespace, vector<vector<int>> &map, WINDOW *arena, WINDOW *game);
      ~Game();
      int getscore();
      bool getendgame();

};


#endif
