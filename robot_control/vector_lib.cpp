#include "vector_lib.h"

vec::vec(){
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

vec::vec(double x, double y, double z){
    this->x = x;
    this->y = y;
    this->z = z;
}

vec vec::operator -(const vec& b)
{
    vec newVec;
    newVec.x = x-b.x;
    newVec.y = y-b.y;
    newVec.z = z-b.z;
    return newVec;
}

vec vec::operator +(const vec& b)
{
    vec newVec;
    newVec.x = x+b.x;
    newVec.y = y+b.y;
    newVec.z = z+b.z;
    return newVec;
}

vec vec::operator =(const vec& b)
{
    x = b.x;
    y = b.y;
    z = b.z;
    return *this;
}

vec vec::operator /(const double b)
{
    vec newVec;
    newVec.x = x/b;
    newVec.y = y/b;
    newVec.z = z/b;
    return newVec;
}

vec vec::operator *(const double b)
{
    vec newVec;
    newVec.x = x*b;
    newVec.y = y*b;
    newVec.z = z*b;
    return newVec;
}

vec transform_2Dvector(double x, double y, vec startVec, double angle, double scale){
    vec newVec;
    newVec.z =  startVec.z;

    newVec.x = startVec.x + cos(angle)*scale*x - sin(angle)*scale*y;
    newVec.y = startVec.y + sin(angle)*scale*x + cos(angle)*scale*y;

    return newVec;
}

rotMat::rotMat(Transformation tran){
    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            R[i][j] = tran.T[i][j];
        }
    }
}

vec rotMat::operator *(const vec& b){
    vec newVec;
    newVec.x = this->R[0][0]*b.x + this->R[0][1]*b.y + this->R[0][2]*b.z;
    newVec.y = this->R[1][0]*b.x + this->R[1][1]*b.y + this->R[1][2]*b.z;
    newVec.z = this->R[2][0]*b.x + this->R[2][1]*b.y + this->R[2][2]*b.z;
    return newVec;
}

void rotMat::print(){
    for(int i=0; i<=2; i++){
        for(int j=0; j<=2; j++){
            cout << R[i][j] << "  ";
        }
        cout << endl;
    }
}

