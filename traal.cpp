#include "engine.h"
#include "game.h"
#include "traal.h"
#include "ncurseslib.h"
#include <string>
#include <stdlib.h>
#include<ncurses.h>
#include <fstream>
#include "search.h"
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;


Traal::Traal(int x, int y, int free):Moving(x,y) {
  freespace = free;
}

Traal::~Traal(){

}

//returns -10 if traal gets player else 0  and places traal to the next posistion
int Traal::nextMove(vector<vector<int>> &map, WINDOW *arena){
  vector<vector<int>> trace;
  int res= 0;
  //-----------------------
  for(int j = 0; j<map.size(); j++) {
    vector<int> temp;
    for(int i = 0; i<map[0].size(); i++) {
      temp.push_back(map[j][i]);
    }
    trace.push_back(temp);
  }
  //---------------------
  int dist;
  //returns shortest distance path int the form of string with chars U,D,R,L
string path = shortestdistance(trace, curx, cury);
dist = path.length();

  //erase current spot
  wattrset(arena, COLOR_PAIR(4));
  map[curx][cury] = 0;
  mvwaddch(arena,curx+1,cury+1, ACS_CKBOARD| A_BOLD);
  wattroff(arena, COLOR_PAIR(4));
  // if distance equals to 1 then TRAAL moves and gets player so result is -10 scorepoints
  //we dont plaqce TRAAL anywhere yet, its placement will take place in the game function
  if(dist == 1) {
    //if the steps taken to reach the player is one then themonster gets the player when it moves so
    //-10 points for the player
    res = -10;
  }
  if(path[0] == 'D')
    move(curx+1, cury, arena,map, res);
  if(path[0]=='U')
    move(curx-1, cury, arena, map, res);
  if(path[0] == 'R')
    move(curx, cury+1, arena, map,res);
  if(path[0]=='L')
    move(curx, cury-1, arena, map,res);
  return res;
}

int Traal::getx(){
  return curx;
}
int Traal::gety() {
  return cury;
}
void Traal::setx(int x){
  curx = x;
}
void Traal::sety(int y) {
 cury = y;
}



string Traal::shortestdistance(vector<vector<int>> &map, int x, int y){
  Search newsearch(map);
  string path =newsearch.findshortest(x,y);
  return path;

}

void Traal::move(int x, int y, WINDOW *arena, vector<vector<int>> &map,int res) {

  // if traal was on top of a diamond in its current spot replace it with
  //a diamond before erasing it
  if(ondiamond) {
    wattrset(arena, COLOR_PAIR(1));
    mvwaddch(arena,curx+1,cury+1,ACS_DIAMOND);
    wattroff(arena, COLOR_PAIR(1));
    map[curx][cury] = 2;
    ondiamond = false;

  }
  if(onpergamini) {
    wattrset(arena, COLOR_PAIR(5));
    mvwaddch(arena,curx+1,cury+1,ACS_DIAMOND);
    wattroff(arena, COLOR_PAIR(5));
    map[curx][cury] = 5;
    onpergamini = false;

  }


  //if it's going to move to a spot with a diamond set ondiamondbool true so
  //it will be replaced in the next  move
  if(map[x][y]==2) {
    ondiamond = true;
  }
  if(map[x][y]==5) {
    onpergamini = true;
  }
  if(res == -10) {
    //if it gets player do not place it on top of player but in arandom place in the array
    //monsters-->3
        int spot = rand() % (freespace-1) + 1;
        for(int j = 0; j<map.size(); j++) {
          for(int k = 0; k<map[0].size(); k++) {
            if(map[j][k] == 0){
              spot--;
              if(spot == 0) {
                map[j][k] = 3;
                setx(j);
                sety(k);
                wattrset(arena, COLOR_PAIR(2));
                mvwaddch(arena, j+1, k+1,  ACS_CKBOARD| A_BOLD);
                wattroff(arena, COLOR_PAIR(2));

              }
            }
          }
    }


  }
  else {
  //place the traal in the next spot
  wattrset(arena, COLOR_PAIR(2));
  mvwaddch(arena,x+1,y+1, ACS_CKBOARD| A_BOLD);
  map[x][y] =3;
  wattroff(arena, COLOR_PAIR(2));
  curx = x;
  cury = y;

}
  wrefresh(arena); //refreh new data about game window



}
