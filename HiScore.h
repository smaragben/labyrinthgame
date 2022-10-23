#ifndef HISCORE_H
#define HISCORE_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "moving.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>


using namespace std;

class HiScore {
private:
  string players[5];
  WINDOW *gamewin;
  int scores[5];
  string curplayer;
  int curscore;
public:
  HiScore(string *names, int *points, WINDOW *game);
  ~HiScore();
  friend void operator<< (HiScore &tablescore, int score);
  friend HiScore& operator<< (HiScore &tablescore, string name);
  int* getscores();
  void refreshdisplay(WINDOW *game);
  string* getnames();
};


#endif
