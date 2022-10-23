#include "engine.h"
#include "game.h"
#include "gnome.h"
#include "ncurseslib.h"
#include <string>
#include <stdlib.h>
#include<ncurses.h>
#include <fstream>
#include <queue>
#include"search.h"
#include <vector>
#include <iostream>
#include <time.h>
using namespace std;

Search::Search(vector<vector<int>> &path){
  for(int j = 0; j<path.size(); j++) {
    vector<int> temp;
    for(int i = 0; i<path[0].size(); i++) {
      temp.push_back(path[j][i]);
    }
    map.push_back(temp);
  }
}
Search::~Search(){}
string Search::findshortest(int coox, int cooy) {
  int i = 0;
  while(i<900) {

if(paths.empty()) {
  paths.push("");
  x.push(coox);
  y.push(cooy);
}
else {
  string str1, str2, str3, str4;
  int curx = coox, cury = cooy;
  curx = x.front();
  cury = y.front();
  if(curx-1 > 0 && map[curx-1][cury] != 1 & map[curx-1][cury] != 6) {
    str1 = paths.front() + "U";
    if(map[curx-1][cury] == 4) {
      return str1;
    }
    map[curx-1][cury] = 6;
    x.push(curx-1);
    y.push(cury);
    paths.push(str1);
  }
  if(curx+1 < map.size() && map[curx+1][cury] != 1 && map[curx+1][cury] != 6) {
    str2 = paths.front() + "D";
    if(map[curx+1][cury] == 4){
      return str2;
    }
    map[curx+1][cury]=6;
    x.push(curx+1);
    y.push(cury);
    paths.push(str2);
  }
  if(cury-1>0 and map[curx][cury-1] != 1 && map[curx][cury-1] != 6) {
    str3 = paths.front() + "L";
    if(map[curx][cury-1]==4) {
      return str3;
    }
    map[curx][cury-1] = 6;
    x.push(curx);
    y.push(cury-1);
    paths.push(str3);
  }
  if(cury+1<map[0].size() &&map[curx][cury+1] != 1 && map[curx][cury+1] != 6){
    str4 = paths.front() + "R";
    if(map[curx][cury+1] == 4){
      return str4;
    }
    x.push(curx);
    y.push(cury+1);
    map[curx][cury+1] = 6;
    paths.push(str4);
  }
  paths.pop();
  x.pop();
  y.pop();
  i++;
  }
}

return paths.front();
}
