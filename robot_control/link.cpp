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
    values["omega"] = q_d;
    values["alpha"] = q_dd;
    values["pcx"] = pc.x;
    values["pcy"] = pc.y;

//    values["pd"] = sqrt(pow(pd.x,2)+pow(pd.y,2));

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

// NEWTON EULER FUNCTIONS START //

void Link::newton_euler_forward(){
    delta_time = (double)(clock()-last_update)/1000.0;
    calculate_translation();
    calculate_rotation();
}

void Link::newton_euler_backward(vec f_j_link, vec t_j_link){
    calculate_momentum();
    calculate_force(f_j_link);
    calculate_torque(f_j_link, t_j_link);

    last_update = clock();
}

void Link::calculate_momentum(){
    // rather change in momentum, therefore denoted d
    pd = ac*m;
}

void Link::calculate_rotation(){
    // Joint varaibles
    q_d = (q - q_prev)/delta_time;
    q_dd = (q_d - q_d_prev)/delta_time;
    q_prev = q;
    q_d_prev = q_d;

    // Global variables

}

void Link::calculate_translation(){
    vec re(DHa/2.0, 0.0, 0.0);
    vec rf(-DHa/2.0, 0.0, 0.0);
    rotMat R(A_global);
    rici = R*re;
    rjci = R*rf;
    pc = vec(A_global) + rjci;
    pe = vec(A_global);

    vc = (pc - pc_prev)/delta_time;
    ve = (pe - pe_prev)/delta_time;
    ac = (vc - vc_prev)/delta_time;
    ae = (ve - ve_prev)/delta_time;

    pc_prev = pc;
    pe_prev = pe;
}

void Link::calculate_force(vec f_j_link){
    vec grav;
    grav.x = 0.0;
    grav.y = -9.81;
    force = f_j_link - grav*m;
}

void Link::calculate_torque(vec f_j_link, vec t_j_link){
    torque = t_j_link - force.cross(rici) +
            f_j_link.cross(rjci);
}
