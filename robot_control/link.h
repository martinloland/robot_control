#ifndef LINK_H
#define LINK_H
#include "transformation.h"
#include <string>
#include <map>
#include <time.h>
#include "vector_lib.h"
using namespace std;

class Link
{
public:

    Transformation A;
    Link();
    Link(double a, double alpha, double d, double theta);
    void print();
    string name;
    void change_theta(double theta);
    void move_theta(double d_theta);
    double theta_start = 0;
    double theta_end = 0;
    void animate(double per);
    map<string, double> getLinkMap();

private:
    // DH parameters
    double _DHa;
    double _DHalpha;
    double _DHd;
    double _theta;
    void update_A();

    // dynamic properties
    int last_calc;
    vec _omega;
    vec _alpha;
    vec _ae;
    vec _ac;
    vec _f;
    vec _t;
    double _m;
    inertia _I;

};


#endif // LINK_H
