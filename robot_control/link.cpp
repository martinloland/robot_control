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
    values["m"] = _m;
    values["ixx"] = _I.M[0][0];
    values["ixy"] = _I.M[0][1];
    values["ixz"] = _I.M[0][2];
    values["iyy"] = _I.M[1][1];
    values["iyz"] = _I.M[1][2];
    values["izz"] = _I.M[2][2];
    return values;
}

void Link::set_weight(double m,
                double ixx,
                double ixy,
                double ixz,
                double iyy,
                double iyz,
                double izz){
    _m = m;
    _I = {ixx, ixy, ixz,
         ixy, iyy, iyz,
         ixz, iyz, izz};
}

void Link::update_dynamics(){
    double delta_time = (double)(clock()-last_update)/1000.0;
    _omega.z = (_theta - _theta_prev)/delta_time;
    _alpha = (_omega - _omega_prev)/delta_time;

    _theta_prev = _theta;
    last_update = clock();
}

void Link::calculate_force(vec force_from_next_link){
    vec grav;
    grav.x = 0.0;
    grav.y = -9.81;
    force = force_from_next_link - grav*_m;
}

void Link::calculate_torque(vec force_from_next_link,
                      vec torque_from_next_link){
    calculate_geometry();
}

void Link::calculate_geometry(){
    vec re(_DHa/2.0, 0.0, 0.0);
    vec rf(-_DHa/2.0, 0.0, 0.0);
    rotMat R(A_global);
    rici = R*re;
    rjci = R*rf;
}
