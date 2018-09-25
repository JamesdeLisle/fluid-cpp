#ifndef FLUID_H
#define FLUID_H
#include "../include/flat.h"
#include "../include/wall.h"
#include <vector>
#include <string>

using namespace std;

class Fluid
{
 private:
  Lattice _vx;
  Lattice _vy;
  Lattice _d;
  Wall W;
  int _Nx;
  int _Ny;
  double _dt;
  void advect(string which);
  void project();
  
 public:
  Fluid(int Nx, int Ny, double dt, double diff, double visc);

  void add_dens_source(int x, int y, double val);
  void add_dens(int x, int y,  double val);
  double get_dens(bool order, int x, int y);
  void clear_dens();

  void add_vel_source(int x, int y, vector<double> val);
  void add_vel(int x, int y, vector<double> val);
  vector<double> get_vel(int x, int y);
  void clear_vel();
  
  void set_visc(double val);
  double get_visc() {return _vx.getdiff();}

  void set_dt(double val) {_dt = val;}
  double get_dt() {return _dt;}
  
  double get_diff() {return _d.getdiff();}
  void set_diff(double val) {_d.setdiff(val);}
  
  void dens_step();
  void vel_step();

  void toggle_wall(int x, int y);
  bool getWall(int x, int y) {return W.getWall(x, y);}

  void print_dens() {_d.print();}
};

#endif
