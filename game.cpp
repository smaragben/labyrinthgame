#include <string>
#include "game.h"
#include "ncurseslib.h"
#include "traal.h"
#include<ncurses.h>
#include <unistd.h>  /* only for sleep() */
#include <fstream>
#include <vector>
#include "gnome.h"
#include "potter.h"
#include <iostream>
#include <chrono>
#include <thread>
using namespace std;
using namespace std::chrono_literals;

Game::Game(int freespace, vector<vector<int>> &map, WINDOW *arena, WINDOW *game){
  endgame = false;
  gamewin = arena;
  screen = game;
  int spot;
  score = 0;

  //-------------------COPY INITIALIZED MAP-----------------------//
  for(int j = 0; j<map.size(); j++) {
    vector<int> temp;
    for(int i = 0; i<map[0].size(); i++) {
      temp.push_back(map[j][i]);
    }
    gamemap.push_back(temp);
  }

  nfreespace = freespace;
//---------------------------------------------------------------
//------------PLACE PLAYERS, DIAMONDS AND MONSTERS-----------------
  //diamonds --->2
  srand (time(NULL));
  for(int i = 0; i <10; i++) {
      spot = rand() % freespace + 1;
      for(int j = 0; j<gamemap.size(); j++) {
        for(int k = 0; k<gamemap[0].size(); k++) {
          if(gamemap[j][k] == 0){
            spot--;
            if(spot == 0) {
              gamemap[j][k] = 2;
              wattrset(arena, COLOR_PAIR(1));
              mvwaddch(arena, j+1, k+1, ACS_DIAMOND);
              wattroff(arena, COLOR_PAIR(1));

            }
          }
        }
      }
      freespace--;
  }
  //monsters-->3
  for(int i = 0; i <2; i++) {
      spot = rand() % freespace + 1;
      for(int j = 0; j<gamemap.size(); j++) {
        for(int k = 0; k<gamemap[0].size(); k++) {
          if(gamemap[j][k] == 0){
            spot--;
            if(spot == 0) {
              if(i==0) {
                traal = new Traal(j,k, freespace);
                wattrset(arena, COLOR_PAIR(2));
                mvwaddch(arena, j+1, k+1,  ACS_CKBOARD| A_BOLD);
                wattroff(arena, COLOR_PAIR(2));
              }
              if(i==1) {
                gnome = new Gnome(j,k, freespace);
                wattrset(arena, COLOR_PAIR(5));
                mvwaddch(arena, j+1, k+1,  ACS_CKBOARD| A_BOLD);
                wattroff(arena, COLOR_PAIR(5));
              }
              gamemap[j][k] = 3;

            }
          }
        }
      }
      freespace--;
  }
  //player ----> 4
   spot = rand() % freespace + 1;
    for(int j = 0; j<gamemap.size(); j++) {
      for(int i = 0; i<gamemap[0].size(); i++) {
        if(gamemap[j][i] == 0){
          spot--;
          if(spot == 0) {
            gamemap[j][i] = 4;
            player = new Potter(j,i);
            wattrset(arena, COLOR_PAIR(3));
            mvwaddch(arena,j+1,i+1, ACS_CKBOARD| A_BOLD);
            wattroff(arena, COLOR_PAIR(3));
          }
        }
      }
    }
    freespace--;
//-----------------------------------------------------------------------
bool founddiamonds = false, pergaminiplaced = false;
init_pair(5, COLOR_MAGENTA, -COLOR_BLACK);
nodelay(stdscr, TRUE);
scrollok(stdscr, TRUE);
int y=0;
//loop that gives order to when monsters and player have their turn
      while(!endgame && !wingame){
        this_thread::sleep_for(300ms);

        //---------------------traal moves----------------------------------
       int res = traal->nextMove(gamemap, arena);
        score += res;
        wattrset(game, COLOR_PAIR(4));
        mvwprintw(game, 1, 65, "   ");
        wattroff(game, COLOR_PAIR(4));
        mvwprintw(game, 1, 65, "%d", score);
        wrefresh(game); //refreh new data about game window
        //--------------------- player moves ---------------------------------------
        //we give player two chances to move each with 100ms
        for(int i = 0; i<2;i++) {
         res = player->nextMove(gamemap, arena);
        if(res == -1) endgame = true;
        int diamonds = player->checkdiamonds();
        score += res;
        wattrset(game, COLOR_PAIR(4));
        mvwprintw(game, 1, 65, "   ");
        wattroff(game, COLOR_PAIR(4));
        mvwprintw(game, 1, 65, "%d", score);
        wrefresh(game); //refreh new data about game window
        //place pergamini

        if(diamonds == 10 && !founddiamonds && !pergaminiplaced) {

          founddiamonds == true;
          //pergamini ----> 5
            spot = rand() % (freespace-1) + 1;
            for(int j = 0; j<gamemap.size(); j++) {
              for(int i = 0; i<gamemap[0].size(); i++) {
                if(gamemap[j][i] == 0){
                  spot--;
                  if(spot == 0) {
                    gamemap[j][i] = 5;
                    wattrset(arena, COLOR_PAIR(5));
                    mvwaddch(arena,j+1,i+1, ACS_DIAMOND| A_BOLD);
                    wattroff(arena, COLOR_PAIR(5));
                  }
                }
              }
            }
            pergaminiplaced= true;
        }
        if(player->foundpergamini()){
          wingame = true;
        }
        this_thread::sleep_for(100ms);

      }
        //-------------------------gnome moves------------------------------------
      res = gnome->nextMove(gamemap, arena);

          score += res;
          wattrset(game, COLOR_PAIR(4));
          mvwprintw(game, 1, 65, "   ");
          wattroff(game, COLOR_PAIR(4));
          mvwprintw(game, 1, 65, "%d", score);
          wrefresh(game); //refreh new data about game window
          wrefresh(arena); //refreh score



      }

}

int Game::getscore()
 {
   return score;
 }

 //when game/round finishes we want to delete the monsters/player and diamonds
Game::~Game() {

      for(int j = 0; j<gamemap.size(); j++) {
        for(int k = 0; k<gamemap[0].size(); k++) {
          if(gamemap[j][k] == 2|gamemap[j][k] == 3|gamemap[j][k] == 4){
              wattrset(gamewin, COLOR_PAIR(4));
              mvwaddch(gamewin, j+1, k+1,  ACS_CKBOARD| A_BOLD);
              wattroff(gamewin, COLOR_PAIR(4));

          }
        }
      }
}
bool Game::getendgame() {
  return endgame;
}
