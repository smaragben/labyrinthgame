#include <ncurses.h>
#include "engine.h"
#include "ncurseslib.h"
#include <fstream>
#include <vector>
#include <iostream>
using namespace std;

int main(int argc, char **argv) {
  initscr(); //initialize screen
  raw(); //do not recognize interrupts
  noecho(); //do not print input
  start_color();

curs_set(0);
  //open file
    fstream map;
    fstream scores;
  	map.open(argv[1], ios::in);
    scores.open(argv[2], ios::in | ios::out);
  	if (!map) {
      move(0,0);
      printw("notopened");
  	}

//start an engine with player linda
    Engine mygame(map, scores, "Linda", argv[2]);



  map.close();
  scores.close();
  return 0;

}
