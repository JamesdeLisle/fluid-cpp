#ifndef FLAT_H
#define FLAT_H
#include "../include/wall.h"
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
typedef vector<vector<double> > mat;

class Lattice
{
 private:
  int _Nx, _Ny;
  double _diff;
  mat _lattice0, _lattice1, _latticeS;
  mat * l0 = NULL;
  mat * l1 = NULL;
  mat * lS = NULL;
  
 public:
  Lattice(int Nx, int Ny, double diff);
  void swap();
  void addSource(int x, int y, double val);
  void mergeSource(double dt);
  void setBound(bool order, int b, Wall W);
  void set(bool order, int x, int y, double val);
  double get(bool order, int x, int y);
  double getdiff() {return _diff;}
  void setdiff(double val) {_diff = val;}
  void diffuse(double dt, int b, Wall W);
  void advect();
  void print();
  void clear();
};

#endif
