#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <iostream>
#include <math.h>
#include "transformation.h"
using namespace std;

struct vec
{
    double x;
    double y;
    double z;
    vec();
    vec(double x, double y, double z);
    vec(Transformation tran);


    vec cross(const vec& b);
    vec operator -(const vec& b);
    vec operator +(const vec& b);
    vec operator =(const vec& b);
    vec operator /(const double b);
    vec operator *(const double b);
    void print(){
     cout << "[" << x << ", " << y << ", " << z << "]" << endl;
    }
};

struct inertia
{
     double M[3][3] = {0};
};

struct rotMat
{
    rotMat(Transformation tran);
    double R[3][3] = {0};
    vec operator *(const vec& b);
    void print();
};

vec transform_2Dvector(double x, double y, vec startVec, double angle, double scale);


#endif // VECTOR_LIB_H
