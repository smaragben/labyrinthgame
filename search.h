#ifndef SEARCH_H
#define SEARCH_H
#include <iostream>
#include "ncurseslib.h"
#include <stdlib.h>
#include "moving.h"
#include<ncurses.h>
#include<vector>
#include <string>
#include <fstream>
#include <queue>


using namespace std;

class Search {
private:
  vector<vector<int>> map;
  queue<string> paths;
  queue<int> x,y;
public:
  Search(vector<vector<int>> &path);
  ~Search();
  string findshortest(int x, int y);


};


#endif
