#include "engine.h"
#include "game.h"
#include "potter.h"
#include "moving.h"
#include "ncurseslib.h"
#include <stdio.h>
#include <sys/select.h>
#include <termios.h>

#include <string>
#include <stdlib.h>
#include<ncurses.h>
#include <fstream>
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;


int kbhit(WINDOW *win)
{
  nodelay(win, TRUE);

    int ch = wgetch(win);
    printw("%d", ERR);

    if (ch != ERR) {
        ungetch(ch);
        return 1;
    } else {
        return 0;
    }
}

Potter::Potter(int x, int y): Moving{x, y} {
  diamondsnum = 0;
  pergaminibool = false;
}

Potter::~Potter(){

}
int Potter::checkdiamonds() {
  return diamondsnum;
}

//0-->stays, 1-->left, 2-->right, 3-->up, 4-->down
int Potter::nextMove(vector<vector<int>> &map, WINDOW *arena) {
  init_pair(1, COLOR_CYAN, COLOR_BLACK);
  init_pair(2, COLOR_RED, COLOR_BLACK);
  init_pair(3, COLOR_GREEN, COLOR_BLACK);
  init_pair(4, COLOR_BLACK, COLOR_BLACK);

  int res = 0;
  keypad(arena, true);
  noecho();
  nodelay(stdscr, TRUE);
  scrollok(stdscr, TRUE);

  //int c=wgetch(arena);
  raw(); //do not recognize interrupts
//kbhit stores in buffer the key that has been pressed so as to create this "synchronous" movement
//of monsters and player
  if(kbhit(arena)){



  switch (wgetch(arena)){
    case KEY_LEFT:  {
        if(cury-1 < 0 ) return 0;
        if (map[curx][cury-1] == 1 |map[curx][cury-1] == 3 ) return 0;
        if(map[curx][cury-1] == 2) {
          res = 10;
          diamondsnum++;
        }
        if(map[curx][cury-1] == 5) {
          res = 100;
          pergaminibool = true;
        }
        wattrset(arena, COLOR_PAIR(3));
        mvwaddch(arena,curx+1,cury, ACS_CKBOARD| A_BOLD);
        map[curx][cury-1] =4;
        wattroff(arena, COLOR_PAIR(3));
        wattrset(arena, COLOR_PAIR(4));
        map[curx][cury] = 0;
        mvwaddch(arena,curx+1,cury+1, ACS_CKBOARD| A_BOLD);
        wattroff(arena, COLOR_PAIR(4));
        wrefresh(arena); //refreh new data about game window
        cury = cury-1;
        return res;
    }

   case KEY_RIGHT:{
     if(cury > map[0].size() ) return 0;
     if (map[curx][cury+1] == 1 |map[curx][cury+1] == 3 ) return 0;
     if(map[curx][cury+1] == 2) {
       res = 10;
       diamondsnum++;
     }
     if(map[curx][cury+1] == 5) {
       res = 100;
       pergaminibool = true;
     }
     //pplace player in new spot
     wattrset(arena, COLOR_PAIR(3));
     mvwaddch(arena,curx+1,cury+2, ACS_CKBOARD| A_BOLD);
     map[curx][cury+1] =4;
     wattroff(arena, COLOR_PAIR(3));
     //delete player from old one
     wattrset(arena, COLOR_PAIR(4));
     map[curx][cury] = 0;
     mvwaddch(arena,curx+1,cury+1, ACS_CKBOARD| A_BOLD);
     wattroff(arena, COLOR_PAIR(4));
     wrefresh(arena); //refreh new data about game window
     cury = cury+1;
     return res;
   }
   case KEY_DOWN: {
     if(curx+1 > map.size() ) return 0;
     if (map[curx+1][cury] == 1 |map[curx+1][cury] == 3 ) return 0;
     if(map[curx+1][cury] == 2)  {
       res = 10;
       diamondsnum++;
     }
     if(map[curx+1][cury] == 5)  {
       res = 100;
       pergaminibool = true;
     }
     wattrset(arena, COLOR_PAIR(3));
     mvwaddch(arena,curx+2,cury+1, ACS_CKBOARD| A_BOLD);
     map[curx+1][cury] =4;
     wattroff(arena, COLOR_PAIR(3));
     wattrset(arena, COLOR_PAIR(4));
     map[curx][cury] = 0;
     mvwaddch(arena,curx+1,cury+1, ACS_CKBOARD| A_BOLD);
     wattroff(arena, COLOR_PAIR(4));
     wrefresh(arena); //refreh new data about game window
     curx = curx+1;
     return res;
   }

   case KEY_UP: {
     if(curx-1 <0 ) return 0;
     if (map[curx-1][cury] == 1|map[curx-1][cury] == 3 ) return 0;
     if(map[curx-1][cury] == 2) {
       res = 10;
       diamondsnum++;
    }
    if(map[curx-1][cury] == 5) {
      res = 100;
      pergaminibool = true;
   }
     wattrset(arena, COLOR_PAIR(3));
     mvwaddch(arena,curx,cury+1, ACS_CKBOARD| A_BOLD);
     map[curx-1][cury] =4;
     wattroff(arena, COLOR_PAIR(3));
     wattrset(arena, COLOR_PAIR(4));
     map[curx][cury] = 0;
     mvwaddch(arena,curx+1,cury+1, ACS_CKBOARD| A_BOLD);
     wattroff(arena, COLOR_PAIR(4));
     wrefresh(arena); //refreh new data about game window
     curx = curx-1;
     return res;
  }
   case 27:  {
     endwin();
     return -1;
   }
 }
}
return 0;

}

bool Potter::foundpergamini(){
  return pergaminibool;
}
int Potter::getx(){
  return curx;

}

int Potter::gety() {
  return cury;
}
