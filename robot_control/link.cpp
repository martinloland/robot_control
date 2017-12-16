#include "link.h"
#include <iostream>
#include <math.h>
using namespace std;

Link::Link()
{
}

Link::Link(double a, double alpha, double d, double theta){
    DHa = a;
    DHalpha = alpha;
    DHd = d;
    q = theta;
    update_A();
}

void Link::print(){
    A.print();
}

void Link::update_A(){
    A.change(DHa, DHalpha, DHd, q);
}

void Link::change_theta(double theta){
    q = theta;
    update_A();
}

void Link::animate(double per){
    double q = q_start + (q_end-q_start)*(6*pow(per,5)-15*pow(per,4)+10*pow(per,3));
    change_theta(q);
    update_A();
}

map<string, double> Link::getLinkMap(){
    map<string, double> values;
    values["DHa"] = DHa;
    values["DHalpha"] = DHalpha;
    values["DHd"] = DHd;
    values["theta"] = q;
    values["m"] = m;
    values["ixx"] = I.M[0][0];
    values["ixy"] = I.M[0][1];
    values["ixz"] = I.M[0][2];
    values["iyy"] = I.M[1][1];
    values["iyz"] = I.M[1][2];
    values["izz"] = I.M[2][2];

    values["force"] = force.y;
    values["torque"] = torque.z;
    values["omega"] = omega.z;
    values["alpha"] = alpha.z;

    return values;
}

void Link::set_weight(double m,
                double ixx,
                double ixy,
                double ixz,
                double iyy,
                double iyz,
                double izz){
    m = m;
    I = {ixx, ixy, ixz,
         ixy, iyy, iyz,
         ixz, iyz, izz};
}

void Link::update_dynamics(){
    double delta_time = (double)(clock()-last_update)/1000.0;
    omega.z = (q - q_prev)/delta_time;
    alpha = (omega - omega_prev)/delta_time;
    q_prev = q;
    omega_prev = omega;
    last_update = clock();
}

void Link::calculate_force(vec force_from_next_link){
    vec grav;
    grav.x = 0.0;
    grav.y = -9.81;
    force = force_from_next_link - grav*m;
}

void Link::calculate_torque(vec force_from_next_link,
                      vec torque_from_next_link){
    calculate_geometry();
    torque = torque_from_next_link - force.cross(rici) +
            force_from_next_link.cross(rjci);
}

void Link::calculate_geometry(){
    vec re(DHa/2.0, 0.0, 0.0);
    vec rf(-DHa/2.0, 0.0, 0.0);
    rotMat R(A_global);
    rici = R*re;
    rjci = R*rf;
}
