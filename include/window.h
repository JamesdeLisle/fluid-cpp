#ifndef WINDOW_H
#define WINDOW_H
#include "../include/fluid.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include "SDL2/SDL_ttf.h"

class Window
{
 private:
  int _width, _height;
  int _dim;
  int _cell_width;
  int _xstart;
  int _ystart;
  SDL_Window * gWindow = NULL;
  SDL_Renderer * gRenderer = NULL;
  TTF_Font * font = NULL;
  SDL_Surface * surfMessage = NULL;
  SDL_Texture * Message = NULL;
  SDL_Rect Message_rect;
  Fluid F;

  bool init();
  bool loadMedia();
  void close();
  void drawGrid();
  void fillGrid();
  void drawVel();
  void addVel(int x, int y, int x1, int y1);
  void addDens(int x, int y);
  void printVals(int x, int y, double value, char msg[5]);
  void drawWalls();
  std::vector<int> getij(int x, int y);
 public:
  Window(int width, int height, int dim);
  void run();
};


#endif
