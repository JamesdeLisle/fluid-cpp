#ifndef WALL_H
#define WALL_H
#include <vector>
#include <iostream>
using namespace std;

typedef vector<vector<double> > matw;

class Wall
{
 private:
  int _Nx, _Ny;
  matw walls;
 public:
  Wall(int Nx, int Ny);
  void toggleWall(int x, int y);
  bool getWall(int x, int y) {return walls[x][y];}    
};


#endif
