#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "GeometricFigure.h"

class Triangle : public GeometricFigure{

private:
  double height;
  double base;
public:
  Triangle(double h, double b, string name);

  double caculatedArea(void);
  double getHeight(void);
  double getBase(void);
  void setHeight(double h);
  void setBase(double b);
};

Triangle::Triangle(double h, double b, string name) : GeometricFigure(name){
  height = h;
  base = b;
}
double Triangle::caculatedArea(void){
  return (height*base)/2;
}
double Triangle::getHeight(void){
  return height;
}
void Triangle::setHeight(double h){
  height = h;
}
double Triangle::getBase(void){
  return base;
}
void Triangle::setBase(double b){
  base = b;
}

#endif
