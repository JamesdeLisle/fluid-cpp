#include "../include/window.h"
#include <SDL2/SDL.h>
#include <iostream>
#include "../include/fluid.h"
#include <stdio.h>
#include "SDL2/SDL_ttf.h"

Window::Window(int width, int height, int dim) : \
  _width(width), \
  _height(height), \
  _dim(dim),
  F(dim, dim, 0.01, 0.0, 0.0) {
  _cell_width = (int) (_height / (float) _dim);
  _xstart = (int) (_width - _dim * _cell_width) / 2; 
  _ystart = (int) (_height - _dim * _cell_width) / 2;
}

bool Window::init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("Window could not initialise! SDL_Error: %s\n", SDL_GetError());
    success = false;
  }
  else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    gWindow = SDL_CreateWindow("SDL_Tutorial",
			       SDL_WINDOWPOS_UNDEFINED,
			       SDL_WINDOWPOS_UNDEFINED,
			       _width,
			       _height,
			       SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
      success = false; 
    }
    else {
      gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
      if (gRenderer == NULL) {
	printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
	success = false;
      }
      else {
	SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
      }
    }
  }
  if (TTF_Init() != 0) {
    printf("TTF could not be initialised! SDL_Error: %s\n", TTF_GetError());
    success = false;
  }
  font = TTF_OpenFont("OpenSans-Regular.ttf", 14);
  if (font == NULL) {
    printf("Font not loaded! SDL_Error: %s\n", TTF_GetError());
    success = false;
  }
  return success;
}

bool Window::loadMedia() {
  bool success = true;
  return success;
}

void Window::close() {
  SDL_DestroyTexture(Message);
  Message = NULL;
  TTF_CloseFont(font);
  font = NULL;
  SDL_DestroyRenderer(gRenderer);
  gRenderer = NULL;
  SDL_DestroyWindow(gWindow);
  gWindow = NULL;
  SDL_FreeSurface(surfMessage);
  surfMessage = NULL;
  TTF_Quit();
  SDL_Quit();
}

void Window::drawGrid() {
  int i;
  for (i=0; i<_dim; i++) { 
    SDL_RenderDrawLine(gRenderer,
		       (int) _xstart + i * _cell_width,
		       _ystart,
		       (int) _xstart + i * _cell_width,
		       _ystart + _dim * _cell_width);
  }
  for (i=0; i<_dim+1; i++) { 
    SDL_RenderDrawLine(gRenderer,
		       (int) _xstart, _ystart + i * _cell_width,
		       (int) _width-_xstart, _ystart + i * _cell_width);
  }
  SDL_RenderDrawLine(gRenderer,
		     (int) _xstart + (_dim) * _cell_width,
		     _ystart,
		     (int) _xstart + (_dim) * _cell_width,
		     _ystart + _dim * _cell_width);
}

void Window::fillGrid() {
  int i, j;
  int color;
  for (i=1; i<_dim+1; i++) {
    for (j=1; j<_dim+1; j++) {
      
      SDL_Rect fillRect = {_xstart + (i-1) * _cell_width,
			   _ystart + (j-1) * _cell_width,
			   _cell_width,
			   _cell_width};
      color = (int) F.get_dens(0, i, j);
      SDL_SetRenderDrawColor(gRenderer, color, 0, 0, SDL_ALPHA_OPAQUE); 
      SDL_RenderFillRect(gRenderer, &fillRect);
    }
  }
}

void Window::drawVel() {
  int i, j, x0, y0 , x1, y1;
  double scaling = 50;
  vector<double> vel;
  for (i=1; i<_dim+1; i++) {
    for (j=1; j<_dim+1; j++) {
      x0 = (int) _xstart + (_cell_width / 2) + (i-1) * _cell_width;
      y0 = (int) _ystart + (_cell_width / 2) + (j-1) * _cell_width;
      vel = F.get_vel(i, j);
      x1 = x0 + vel[0] * scaling ;  
      y1 = y0 + vel[1] * scaling ;  
      SDL_RenderDrawLine(gRenderer, x0, y0, x1, y1);
    }
  }
}

void Window::addVel(int x, int y, int x1, int y1) {
  int i, j;
  double scale = 0.1;
  vector<double> vel;
  
  if (x > _xstart && x < _xstart + _dim * _cell_width) {
    if (y > _ystart && y < _ystart + _dim * _cell_width) {
      i = (int) (x - _xstart) / _cell_width;
      j = (int) (y - _ystart) / _cell_width;
      vel.push_back((double) (x1 - x) * scale);
      vel.push_back((double) (y1 - y) * scale);
      F.add_vel(i, j, vel);
    }
  }
}


void Window::addDens(int x, int y) {
  int i, j;
  if (x > _xstart && x < _xstart + _dim * _cell_width) {
    if (y > _ystart && y < _ystart + _dim * _cell_width) {
      i = (int) (x - _xstart) / _cell_width;
      j = (int) (y - _ystart) / _cell_width;
      F.add_dens(i, j, 100);
    }
  }
}

void Window::printVals(int x,
		       int y,
		       double value,
		       char msg[5]) {
  SDL_Color White = {255, 255, 255};
  char buffer[100];
  sprintf(buffer, "%s%f", msg, value);
  surfMessage = TTF_RenderText_Solid(font, buffer, White);
  Message = SDL_CreateTextureFromSurface(gRenderer, surfMessage);
  Message_rect.x = x;
  Message_rect.y = y;
  Message_rect.w = 150;
  Message_rect.h = 25;
  SDL_RenderCopy(gRenderer, Message, NULL, &Message_rect);
}

void Window::drawWalls() {
  int i, j;
  for (i=1; i<_dim+1; i++) {
    for (j=1; j<_dim+1; j++) {
      if (F.getWall(i, j)) {
	SDL_Rect fillRect = {_xstart + (i-1) * _cell_width,
			     _ystart + (j-1) * _cell_width,
			     _cell_width,
			     _cell_width};
	SDL_SetRenderDrawColor(gRenderer, 0, 255, 0, SDL_ALPHA_OPAQUE); 
	SDL_RenderFillRect(gRenderer, &fillRect);
      }
    }
  }
}

std::vector<int> Window::getij(int x, int y) {
  int i = 0, j = 0;
  if (x > _xstart && x < _xstart + _dim * _cell_width) {
    if (y > _ystart && y < _ystart + _dim * _cell_width) {
      i = (int) (x - _xstart) / _cell_width;
      j = (int) (y - _ystart) / _cell_width;
    }
  }
  std::vector<int> rv;
  rv.push_back(i+1);
  rv.push_back(j+1);
  return rv; 
}

void Window::run() {
  int x, y, x1, y1;
  bool fill = false, wall = false, source = false;
  bool vx_up = false, vx_dn = false, vy_up = false, vy_dn = false;
  std::vector<int> index;
  std::vector<double> vel;
  if (!this->init()) {
    printf("Failed to initialise!\n");
  }
  else {
    if (!this->loadMedia()) {
      printf("Failed to load media!\n");
    }
    else {
      bool quit = false;
      bool overlay = false;
      SDL_Event e;
      while (!quit) {
	SDL_GetMouseState(&x, &y);
	index = this->getij(x, y);
	vel = F.get_vel(index[0], index[1]);
	if (fill) {addDens(x, y);}
	if (wall) {F.toggle_wall(index[0], index[1]); wall = false;}
	if (source) {F.add_dens_source(index[0], index[1], 255); source = false;}
	if (vy_up) {vel[1] -= 1;}
	if (vy_dn) {vel[1] += 1;}
	if (vx_up) {vel[0] += 1;}
	if (vx_dn) {vel[0] -= 1;}
	if (vx_up || vx_dn || vy_up || vy_dn) {
	  F.add_vel_source(index[0], index[1], vel);
	  vy_up = false;
	  vy_dn = false;
	  vx_up = false;
	  vx_dn = false;
	}
	F.vel_step();
	F.dens_step();
	SDL_RenderClear(gRenderer);
	SDL_SetRenderDrawColor(gRenderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(gRenderer);
	fillGrid();
	drawWalls();
	if (overlay) {
	  SDL_SetRenderDrawColor(gRenderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	  drawVel();
	}
	SDL_SetRenderDrawColor(gRenderer, 73, 73, 73, SDL_ALPHA_OPAQUE);
	drawGrid();
	printVals(0, 0, F.get_dt(), (char *) "dt: ");
	printVals(0, 50, F.get_visc(), (char *) "vs: ");
	printVals(0, 100, F.get_diff(), (char *)"df: ");
	
	while (SDL_PollEvent(&e) != 0)
	  {
	   if( e.type == SDL_QUIT )
	     {
	       quit = true;
	     }
	   else if (e.type == SDL_KEYDOWN && e.key.repeat == 0) {
	     switch (e.key.keysym.sym) {
	     case SDLK_TAB:
	       overlay = !overlay;
	       break;
	     case SDLK_UP:
	       F.set_dt(F.get_dt() + 0.01);
	       break;
	     case SDLK_DOWN:
	       F.set_dt(F.get_dt() - 0.01);
	       break;
	     case SDLK_LEFT:
	       F.set_visc(F.get_visc() - 0.0001);
	       break;
	     case SDLK_RIGHT:
	       F.set_visc(F.get_visc() + 0.0001);
	       break;
	     case SDLK_w:
	       F.set_diff(F.get_diff() + 0.0001);
	       break;
	     case SDLK_s:
	       F.set_diff(F.get_diff() - 0.0001);
	       break;
	     case SDLK_u:
	       SDL_GetMouseState(&x, &y);
	       vy_up = true;
	       break;
	     case SDLK_j:
	       SDL_GetMouseState(&x, &y);
	       vy_dn = true;
	       break;
	     case SDLK_k:
	       SDL_GetMouseState(&x, &y);
	       vx_up = true; 
	       break;
	     case SDLK_h:
	       SDL_GetMouseState(&x, &y);
	       vx_dn = true; 
	       break;
	     case SDLK_a:
	       SDL_GetMouseState(&x, &y);
	       wall = true;
	       break;
	     case SDLK_c:
	       SDL_GetMouseState(&x, &y);
	       source = true;
	       break;
	     case SDLK_t:
	       F.clear_dens();
	       std::cout << "dens" << std::endl;
	       break;
	     case SDLK_y:
	       F.clear_vel();
	       std::cout << "vel" << std::endl;
	       break;
	     default:
	       break;
	     }
	   }
	   else if (e.type == SDL_MOUSEBUTTONDOWN) {
	     SDL_GetMouseState(&x, &y);
	     if (e.button.button == SDL_BUTTON_LEFT) {
	       fill = !fill;
	     }
	   }
	   else if (e.type == SDL_MOUSEBUTTONUP) {
	     SDL_GetMouseState(&x1, &y1);
	     if (e.button.button == SDL_BUTTON_RIGHT) {
	       addVel(x, y, x1, y1);
	     }
	     else if (e.button.button == SDL_BUTTON_LEFT) {
	       fill = !fill;
	     }
	   }
	  }
	SDL_RenderPresent(gRenderer);
      }
    }
  }
  close();
}
