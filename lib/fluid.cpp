#include "../include/fluid.h"
#include "../include/flat.h"
#include <stdlib.h>
#include <string>
#include <iostream>

double fRand(double fmin, double fmax) {
  double f = (double) rand() / RAND_MAX;
  return fmin + f * (fmax - fmin);
}

Fluid::Fluid(int Nx, int Ny, double dt, double diff, double visc) : \
  _vx(Nx, Ny, visc), \
  _vy(Nx, Ny, visc), \
  _d(Nx, Ny, diff), \
  W(Nx, Ny), \
  _Nx(Nx), \
  _Ny(Ny), \
  _dt(dt) {
} 

void Fluid::add_dens_source(int x, int y, double val) {
  _d.addSource(x, y, val);
}

void Fluid::add_dens(int i, int j, double val) {
  double current = _d.get(1, i, j);
  if (current + val > 255) {_d.set(1, i, j, 255);}
  else {_d.set(1, i, j, current + val);}
}

double Fluid::get_dens(bool order, int x, int y) {
  return _d.get(order, x, y);
}

void Fluid::clear_dens() {
  _d.clear();
}

void Fluid::add_vel_source(int x, int y, vector<double> val) {
  _vx.addSource(x, y, val[0]);
  _vy.addSource(x, y, val[1]);
}

void Fluid::add_vel(int x, int y, vector<double> val) {
  _vx.addSource(x, y, _vx.get(1, x, y) + val[0]);
  _vy.addSource(x, y, _vy.get(1, x, y) + val[1]);
}

vector<double> Fluid::get_vel(int x, int y) {
  vector<double> rv;
  rv.push_back(_vx.get(1, x, y));
  rv.push_back(_vy.get(1, x, y));
  return rv;
}

void Fluid::clear_vel() {
  _vx.clear();
  _vy.clear();
}

void Fluid::set_visc(double val) {
  _vx.setdiff(val);
  _vy.setdiff(val);
}

void Fluid::toggle_wall(int x, int y) {
  W.toggleWall(x, y);
}

void Fluid::advect(string which) {
  int i, j, i0, j0, i1, j1, a, b;
  float x, y, s0, t0, s1, t1, dt0;
  double val;
  Lattice * a0;

  if (which == (string) "d") {
    a0 = &_d;
    a = 1;
    b = 0;
  }
  else if (which == (string) "vx") {
    a0 = &_vx;
    a = 0;
    b = 1;
  }
  else if (which == (string) "vy") {
    a0 = &_vy;
    a = 0;
    b = 2;
  }
  else {
    throw "advect method passed non-valid arg";
  }
  
  dt0 = _dt * _Nx;
  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      x = i - dt0 * _vx.get(a, i, j); 
      y = j - dt0 * _vy.get(a, i, j); 
      if (x<0.5) {x=0.5;} if (x>_Nx+0.5) {x=_Nx+0.5;}
      i0 = (int) x; i1 = i0 + 1;
      if (y<0.5) {y=0.5;} if (y>_Ny+0.5) {y=_Ny+0.5;}
      j0 = (int) y; j1 = j0 + 1;
      s1 = x - i0; s0 = 1 - s1;
      t1 = y - j0; t0 = 1 - t1;
      val = s0 * (t0 * (*a0).get(0, i0, j0) + t1 * (*a0).get(0, i0, j1));
      val += s1 * (t0 * (*a0).get(0, i1, j0) + t1 * (*a0).get(0, i1, j1));
      (*a0).set(1, i, j, val);
    }
  }
  (*a0).setBound(1, b, W);
}

void Fluid::project() {
  double hx = 1.0 / _Nx, hy = 1.0 / _Ny, val;
  int i, j, k;
  Lattice P(_Nx, _Ny, 1.0);

  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      val = 0.0;
      val += -0.5 * hx * (_vx.get(1, i + 1, j) - _vx.get(1, i-1, j));
      val += -0.5 * hy * (_vy.get(1, i, j + 1) - _vy.get(1, i, j-1));
      P.set(1, i, j, val);
      P.set(0, i, j, 0.0);
    }
  }
  P.setBound(0, 0, W);
  P.setBound(1, 0, W);
  
  for (k=0; k<20; k++) {
    for (i=1; i<_Nx+1; i++) {
      for (j=1; j<_Ny+1; j++) {
	val = 0.0;
	val += P.get(1, i, j);
	val += P.get(0, i-1, j);
	val += P.get(0, i+1, j);
	val += P.get(0, i, j-1);
	val += P.get(0, i, j+1);
	val /= 4.0;
	P.set(0, i, j, val);
      }
    }
  }
  P.setBound(0, 0, W);
  for (i=1; i<_Nx+1; i++) {
    for (j=1; j<_Ny+1; j++) {
      val = _vx.get(1, i, j) - 0.5 * (P.get(0, i+1, j) - P.get(0, i-1, j)) / hx;
      _vx.set(1, i, j, val);
      val = _vy.get(1, i, j) - 0.5 * (P.get(0, i, j+1) - P.get(0, i, j-1)) / hx;
      _vy.set(1, i, j, val);
    }
  }
  _vx.setBound(1, 1, W);
  _vy.setBound(1, 2, W);
}


void Fluid::dens_step() {
  _d.mergeSource(_dt);
  _d.swap();
  _d.diffuse(_dt, 0, W);
  _d.swap();
  this->advect("d");
}

void Fluid::vel_step(){
  _vx.mergeSource(_dt);
  _vy.mergeSource(_dt);
  _vx.swap();
  _vy.swap();
  _vx.diffuse(_dt, 1, W);
  _vy.diffuse(_dt, 2, W);
  this->project();
  _vx.swap();
  _vy.swap();
  this->advect("vx");
  this->advect("vy");
  this->project();
}
