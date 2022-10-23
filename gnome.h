#ifndef GNOME_H
#define GNOME_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "moving.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>


using namespace std;

class Gnome: public Moving {
private:
  bool ondiamond = false;
  bool onpergamini = false;
  int freespace;
public:
  Gnome(int x, int y, int free);
  ~Gnome();
  int nextMove(vector<vector<int>> &map, WINDOW *arena);
  int getx();
  int gety();
  void sety(int y);
  void setx(int x);
  string shortestdistance(vector<vector<int>> &map, int x, int y);
  void move(int x, int y, WINDOW *arena, vector<vector<int>> &map, int res);

};


#endif
