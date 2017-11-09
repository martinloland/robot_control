#include "transformation.h"
#include <iostream>
#include <iomanip>
#include <math.h>
using namespace std;

Transformation::Transformation()
{
    cout << "created undefined transformation\n";
    identity();
}

Transformation::Transformation(double a, double alpha, double d, double theta){
    change(a, alpha, d, theta);
}

coord3D Transformation::coord(){
    coord3D_.x = T[1][4];
    coord3D_.x = T[2][4];
    coord3D_.x = T[3][4];
    return coord3D_;
}

double Transformation::x(){
    return T[1][4];
}
double Transformation::y(){
    return T[2][4];
}
double Transformation::z(){
    return T[3][4];
}

void Transformation::identity(){
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            if (i==j){
                T[i][j] = 1.0;
            }else{
                T[i][j] = 0.0;
            }
        }
    }
}

void Transformation::zero(){
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            T[i][j] = 0.0;
        }
    }
}

void Transformation::change(double a, double alpha, double d, double theta){
    double a11 = cos(theta);
    double a12 = -sin(theta)*cos(alpha);
    double a13 = sin(theta)*sin(alpha);
    double a14 = a*cos(theta);

    double a21 = sin(theta);
    double a22 = cos(theta)*cos(alpha);
    double a23 = -cos(theta)*sin(alpha);
    double a24 = a*sin(theta);

    double a31 = 0.0;
    double a32 = sin(alpha);
    double a33 = cos(alpha);
    double a34 = d;

    double a41 = 0.0;
    double a42 = 0.0;
    double a43 = 0.0;
    double a44 = 1.0;

    double A[16] = {a11, a12, a13, a14,
         a21, a22, a23, a24,
         a31, a32, a33, a34,
         a41, a42, a43, a44};
    int pos = 0;

    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            T[i][j] = A[pos];
            pos++;
        }
    }
}

Transformation Transformation::operator*(const Transformation& b){
    Transformation t;

    // Multiplying matrix firstMatrix and secondMatrix and storing in array mult.
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            for(int k=0; k<4; ++k)
            {
                t.T[i][j] += T[i][k] * b.T[k][j];
            }
        }
    }
    return t;
}

void Transformation::operator*=(const Transformation& b){
    Transformation t;
    t.zero();
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            for(int k=0; k<4; ++k)
            {
                t.T[i][j] += this->T[i][k] * b.T[k][j];
            }
        }
    }
    replace(t);
}

void Transformation::replace(const Transformation& t){
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            this->T[i][j] = t.T[i][j];
        }
    }
}

void Transformation::print()
{
    cout.precision(2);
    for(int i = 0; i < 4; ++i)
    {
        for(int j = 0; j < 4; ++j)
        {
            cout<< fixed << setw(5) << T[i][j] << " ";
        }
        cout << endl;
    }
}
