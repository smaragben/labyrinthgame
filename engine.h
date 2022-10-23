#ifndef ENGINE_H
#define ENGINE_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "game.h"
#include "moving.h"
#include "HiScore.h"
#include "potter.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>


using namespace std;

class Engine {
    private:
      string playername;
      Game *round;
      HiScore *highscores;
      vector<vector<int>> map;
      int freespace;
      int scorepoints[5];
      string scorenames[5];
      int height, width, start_x, start_y; //characteristics of main program layout
      int inpw, inph; //size of input array
      int startar_x, startar_y; //coordinates to place the Labyrinth
      WINDOW *game ;//main window
      WINDOW *arena ; //labyrinth  window
    public:
      Engine(fstream &infile, fstream &points, string name, string outfile);
      ~Engine();




};


#endif
