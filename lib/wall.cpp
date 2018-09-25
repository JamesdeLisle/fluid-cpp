#include "../include/wall.h"

Wall::Wall(int Nx, int Ny) : _Nx(Nx), _Ny(Ny) {
  int i;
  walls.resize(_Nx + 2);
  for (i=0; i<_Nx + 2; i++) {
    walls[i].resize(_Ny + 2);
  }
}

void Wall::toggleWall(int x, int y) {
  walls[x][y] = !walls[x][y];
}
