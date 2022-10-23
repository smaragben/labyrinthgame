#ifndef MOVING_H
#define MOVING_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "game.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>

using namespace std;

class Moving {
  protected:
    int curx, cury;
  public:
    Moving(int x, int y);
    ~Moving();
    virtual int nextMove(vector<vector<int>> &map, WINDOW *arena) = 0;
};


#endif
