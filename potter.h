#ifndef POTTER_H
#define POTTER_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "moving.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>


using namespace std;

class Potter: public Moving {
private:
  int diamondsnum = 0;
  bool pergaminibool;
public:
  Potter(int x, int y);
  ~Potter();
  int nextMove(vector<vector<int>> &map, WINDOW *arena);
  int checkdiamonds();
  bool foundpergamini();
  int getx();
  int gety();
};


#endif
