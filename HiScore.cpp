#include "engine.h"
#include "game.h"
#include "ncurseslib.h"
#include <string>
#include "HiScore.h"
#include "moving.h"
#include <stdlib.h>
#include<ncurses.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;



HiScore::HiScore(string *names, int *points, WINDOW *game) {
  gamewin = game;
  for(int i = 0; i<5; i++) {
    players[i] = names[i];
    scores[i] = points[i];
  }

}
HiScore::~HiScore() {

}

void operator<< (HiScore &tablescore, int score){
  tablescore.curscore = score;
  tablescore.refreshdisplay(tablescore.gamewin);
}
HiScore& operator<< (HiScore &tablescore, string name) {
  tablescore.curplayer = name;
  return tablescore;
}

void HiScore::refreshdisplay(WINDOW *game) {
  wattrset(game, COLOR_PAIR(2));
  mvwprintw(game, 1, 65, "    ");
  wattroff(game, COLOR_PAIR(2));
  bool found = false;
  string name = curplayer;
  int score = curscore;
  string tempnam, swapnam;
  int tempscore, swapsc;
  for(int i =0; i<5; i++) {


    if(found) {
      swapnam = players[i];
      swapsc = scores[i];
      players[i] = tempnam;
      scores[i] = tempscore;
      tempnam = swapnam;
      tempscore = swapsc;
    }


    if (score>scores[i] && !found) {


      tempscore = scores[i];
      tempnam = players[i];
      scores[i] = score;
      players[i] = name;
      found = true;
    }
  }

  for(int i = 0; i<5; i++) {
    string playname = players[i] ;
  //  playname += " |";
    const char * nam = playname.c_str();
    wattrset(game, COLOR_PAIR(4));
    mvwprintw(game, 4+i, 55, "           ");
    wattroff(game, COLOR_PAIR(4));
    wrefresh(game); //refreh new data about game window
    wattrset(game, COLOR_PAIR(1));
    mvwprintw(game, 4+i, 55, nam);
    mvwprintw(game, 4+i, 65, "%d", scores[i]);
    wattroff(game, COLOR_PAIR(1));

    wrefresh(game); //refreh new data about game window
  }
  wrefresh(game); //refreh new data about game window

}
int* HiScore::getscores(){
  return scores;

}

string* HiScore::getnames(){

  return players;

}
