#include "link.h"
#include <iostream>
#include <math.h>
using namespace std;

Link::Link()
{
}

Link::Link(double a, double alpha, double d, double theta){
    _a = a;
    _alpha = alpha;
    _d = d;
    _theta = theta;
    update_A();
}

void Link::print(){
    A.print();
}

void Link::update_A(){
    A.change(_a, _alpha, _d, _theta);
}

void Link::change_theta(double theta){
    _theta = theta;
    update_A();
}

void Link::move_theta(double d_theta){
    _theta += d_theta;
    update_A();
}

void Link::animate(double per){
    double q = theta_start + (theta_end-theta_start)*(6*pow(per,5)-15*pow(per,4)+10*pow(per,3));
    change_theta(q);
    update_A();
}
