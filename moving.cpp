#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "game.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>

using namespace std;

Moving::Moving(int x, int y) {
  curx = x;
  cury = y;
}
Moving::~Moving() {}
