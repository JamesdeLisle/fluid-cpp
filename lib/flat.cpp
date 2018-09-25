#include "../include/flat.h"
#include "../include/wall.h"
#include <string>
#include <algorithm>
#include <iostream>

Lattice::Lattice(int Nx, int Ny, double diff) : \
  _Nx(Nx), _Ny(Ny), _diff(diff) {
  int i;
  l0 = &_lattice0;
  l1 = &_lattice1;
  lS = &_latticeS;
  
  (*l0).resize(_Nx + 2);
  (*l1).resize(_Nx + 2);
  (*lS).resize(_Nx + 2);
  for (i=0; i<_Nx + 2; i++) {
    (*l0)[i].resize(_Ny + 2);
    (*l1)[i].resize(_Ny + 2);
    (*lS)[i].resize(_Ny + 2);
  }
}

void Lattice::addSource(int x, int y, double val) {
  if (val > 255) {
    (*lS)[x][y] = 255;
  }
  else {
    (*lS)[x][y] = val;
  }
}

void Lattice::mergeSource(double dt) {
  int i, j;
  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      if ((*l1)[i][j] + (*lS)[i][j] < 255) {
	(*l1)[i][j] +=  (*lS)[i][j];
      }
      else {
	(*l1)[i][j] = 255;
      }
    }
  }
}

void Lattice::swap() {
  mat * tmp = l0;
  l0 = l1;
  l1 = tmp;
}

void Lattice::set(bool order, int x, int y, double val) {
  order ? (*l1)[x][y] = val : (*l0)[x][y] = val;
}

double Lattice::get(bool order, int x, int y) {
  mat * l;
  order ? l = l1 : l = l0;
  return (*l)[x][y];
}

void Lattice::print() {
  int i, j;
  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      std::cout << (*l0)[i][j] << " ";
    }
    std::cout << std::endl; 
  }
  std::cout << std::endl;
}

void Lattice::clear() {
  int i, j;
  for (i=0; i<_Nx+2; i++) {
    for (j=0; j<_Ny+2; j++) {
      (*lS)[i][j] = 0.0;
    }
  }
}

void Lattice::setBound(bool order, int b, Wall W) {
  int i, j, k;
  mat * l;
  order ? l = l1 : l = l0;
  bool closed = false;
  
  for (i=1; i<_Ny+1; i++) {
    if (closed) {
      (*l)[0][i] = b==1 ? -(*l)[1][i] : (*l)[1][i];
      (*l)[_Nx+1][i] = b==1 ? -(*l)[_Nx][i] : (*l)[_Nx][i];
    }
    else {
      (*l)[0][i] = (*l)[1][i];
      (*l)[_Nx+1][i] = (*l)[_Nx][i];
    }
  }
  for (i=1; i<_Nx+1; i++) {
    if (closed) {
      (*l)[i][0] = b==2 ? -(*l)[i][1] : (*l)[i][1];
      (*l)[i][_Ny+1] = b==2 ? -(*l)[i][_Ny] : (*l)[i][_Ny];
    }
    else {
      (*l)[i][0] = (*l)[i][1];
      (*l)[i][_Ny+1] = (*l)[i][_Ny];
    }
  }
  
  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      if (W.getWall(i, j)) {
	(*l)[i][j] = b==0 ? 0.0 :  (*l)[i][j];
	for (k=-1; k<2; k++) {
	  (*l)[i-1][j+k] = b==1 ? -(*l)[i-2][j+k] : (*l)[i-2][j+k];
	  (*l)[i+1][j+k] = b==1 ? -(*l)[i+2][j+k] : (*l)[i+2][j+k];
	  (*l)[i+k][j-1] = b==2 ? -(*l)[i+k][j-2] : (*l)[i+k][j-2];
	  (*l)[i+k][j+1] = b==2 ? -(*l)[i+k][j+2] : (*l)[i+k][j+2];
	}
      }
    }
  }
  (*l)[0][0] = 0.5 * ((*l)[1][0] + (*l)[0][1]);
  (*l)[0][_Ny+1] = 0.5 * ((*l)[1][_Ny+1] + (*l)[0][_Ny+1]);
  (*l)[_Nx+1][0] = 0.5 * ((*l)[_Nx+1][0] + (*l)[_Nx+1][1]);
  (*l)[_Nx+1][_Ny+1] = 0.5 * ((*l)[_Nx][_Ny+1] + (*l)[_Nx+1][_Ny]);
}

void Lattice::diffuse(double dt, int b, Wall W) {
  int i, j, k;
  float a = dt * _diff * _Nx * _Ny;
  double val;
  
     
  for (k=0; k<20; k++) {
    for (i=1; i<_Nx+1; i++) {
      for (j=1; j<_Ny+1; j++) {
	val = ((*l0)[i][j] +
	       a * ((*l1)[i-1][j] +
		    (*l1)[i+1][j] +
		    (*l1)[i][j-1] +
		    (*l1)[i][j+1])) / (1 + 4 * a);
	(*l1)[i][j] = val;
      }
    }
    this->setBound(1, b, W);
  }
}
