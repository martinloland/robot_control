#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <iostream>
#include <math.h>
using namespace std;

struct vec
{
     double x,y,z = 0;

     vec& operator -(const vec& b)
     {
         vec newVec;
         newVec.x = x-b.x;
         newVec.y = y-b.y;
         newVec.z = z-b.z;
         return newVec;
     }

     vec& operator +(const vec& b)
     {
         vec newVec;
         newVec.x = x+b.x;
         newVec.y = y+b.y;
         newVec.z = z+b.z;
         return newVec;
     }

     vec& operator =(const vec& b)
     {
         x = b.x;
         y = b.y;
         z = b.z;
         return *this;
     }

     vec& operator /(const double b)
     {
         vec newVec;
         newVec.x = x/b;
         newVec.y = y/b;
         newVec.z = z/b;
         return newVec;
     }

     vec& operator *(const double b)
     {
         vec newVec;
         newVec.x = x*b;
         newVec.y = y*b;
         newVec.z = z*b;
         return newVec;
     }

     void print(){
         cout << "[" << x << ", " << y << ", " << z << "]" << endl;
     }
};

struct inertia
{
     double M[3][3] = {0};
};

vec transform_2Dvector(double x, double y, vec startVec, double angle, double scale);


#endif // VECTOR_LIB_H
