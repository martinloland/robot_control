#ifndef VECTOR_LIB_H
#define VECTOR_LIB_H
#include <math.h>

struct vec
{
     double x,y,z = 0;
};

struct inertia
{
     double M[3][3] = {0};
};

vec transform_2Dvector(double x, double y, vec startVec, double angle, double scale);


#endif // VECTOR_LIB_H
