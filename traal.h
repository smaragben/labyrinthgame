#ifndef TRAAL_H
#define TRAAL_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "moving.h"
#include "search.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>


using namespace std;

class Traal: public Moving {
private:
  bool ondiamond = false;
  bool onpergamini = false;
  int freespace;
public:
  Traal(int x, int y, int free);
  ~Traal();
  int nextMove(vector<vector<int>> &map, WINDOW *arena);
  int getx();
  int gety();
  void sety(int y);
  void setx(int x);
  string shortestdistance(vector<vector<int>> &map, int x, int y);
  void move(int y, int x,WINDOW *arena, vector<vector<int>> &map, int res);

};


#endif
