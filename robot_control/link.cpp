#include "link.h"
#include <iostream>
#include <math.h>
using namespace std;

Link::Link()
{
}

Link::Link(double a, double alpha, double d, double theta){
    _DHa = a;
    _DHalpha = alpha;
    _DHd = d;
    _theta = theta;
    update_A();
}

void Link::print(){
    A.print();
}

void Link::update_A(){
    A.change(_DHa, _DHalpha, _DHd, _theta);
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

map<string, double> Link::getLinkMap(){
    map<string, double> values;
    values["DHa"] = _DHa;
    values["DHalpha"] = _DHalpha;
    values["DHd"] = _DHd;
    values["theta"] = _theta;
    return values;
}
