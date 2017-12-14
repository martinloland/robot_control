#include "vector_lib.h"

vec transform_2Dvector(double x, double y, vec startVec, double angle, double scale){
    vec newVec;
    newVec.z =  startVec.z;

    newVec.x = startVec.x + cos(angle)*scale*x - sin(angle)*scale*y;
    newVec.y = startVec.y + sin(angle)*scale*x + cos(angle)*scale*y;

    return newVec;
}
