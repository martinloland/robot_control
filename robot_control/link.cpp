#include "link.h"
#include <iostream>
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
