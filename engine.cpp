#include "engine.h"
#include "game.h"
#include "ncurseslib.h"
#include "HiScore.h"
#include <string>
#include "moving.h"
 #include <unistd.h>
#include <stdlib.h>
#include<ncurses.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;





Engine::Engine(fstream &infile, fstream &points, string name, string fileout) {
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_BLACK);
  init_pair(5, COLOR_YELLOW, COLOR_BLACK);


  //---------------READ FILES------------------------------//
  string line;
  freespace = 0;
  //Eenter the walls to map-->1, free space-->0
try{
  for(int i = 0; i < 5; i++) {
    points >> scorenames[i] >>  scorepoints[i] ;
  }
}
catch(exception const& e) {
printw("scores file is not in the proper format must be: 'Name' 'Points' x5\n");
exit(0);
}
  highscores = new HiScore(scorenames, scorepoints, game);
  try {
  while(getline(infile, line)) {
    vector<int> temp;
    for(int i = 0; i<line.length(); i++) {
      if(line[i] == '*' ) {
        temp.push_back(1);
      }
      else if(line[i] == ' ') {
        freespace++;
        temp.push_back(0);
      }
      else{
        throw "improper character in map file must be: '*' or ' '";
      }

    }
    map.push_back(temp);
  }
}
catch(string msg) {
  printw("%s", msg);
  exit(0);
}
//----------------------------------------------------

//---------------------CREATE WINDOWS AND INITIALIZE THEM---------------//
  height = 45;
  width = 70;
  inpw = map[0].size() +2;
  inph = map.size()+2;
  start_x=start_y = 5;
  startar_x = startar_y = 20;
  arena = newwin(inph, inpw, startar_y, startar_x);
  game = newwin(height, width, start_y, start_x);
  refresh(); //refreh new data
  box(game,0,0); //create a box around main window

  wrefresh(game); //refreh new data about game window
  mvwprintw(game, 1, 1, "Labyrinth Game");
  mvwprintw(game, 3, 1, "Potter->Green");
  mvwprintw(game, 4, 1, "Traal->Red");
  mvwprintw(game, 5, 1, "Gnome->Pink");

  //wattroff(game, COLOR_PAIR(1));
  playername = name;
  playername += " |";
  const char * nam = playername.c_str();
  mvwprintw(game, 1, 55, nam);
  mvwprintw(game, 1, 65, "0");
  mvwprintw(game, 3, 55, "High Scores:");

  for(int i = 0; i<5; i++) {
    string players = scorenames[i] ;
    players += " |";
    const char * nam = players.c_str();
    mvwprintw(game, 4+i, 55, nam);
    mvwprintw(game, 4+i, 65, "%d", scorepoints[i]);
  }
  wrefresh(game); //refreh new data about game window
  for(int j = 1; j<map.size()+1; j++) {
    for(int i = 1; i<map[0].size()+1; i++) {
      if(map[j-1][i-1] == 1){
        mvwaddch(arena, j, i, ACS_CKBOARD);
      }
    }
  }

  wrefresh(arena); //refreh new data about game window
//---------------------------------------------------------

//---------------NEW ROUND-----------------------------//
HiScore sc(scorenames, scorepoints, game);

while(true) {
  round = new Game(freespace, map, arena, game);

  //when round finishes get score
  int score = round->getscore();
  sc << name << score;
  if (round->getendgame()) {
    delete round;
    break;
  }
  delete round;
}
//when player hits ESC previous loop breaks and scores and names are parsed to the output file
//and program finishes
int *scores;
string *names;
scores = sc.getscores();
names = sc.getnames();
fstream output;
output.open(fileout, ios::out|ios::trunc);
for(int i = 0; i < 5; i++) {
  output << names[i] << " "<< scores[i] << endl;
}
}

Engine::~Engine() {
  endwin();
}
