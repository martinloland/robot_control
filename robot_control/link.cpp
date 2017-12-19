#include "link.h"
#include <iostream>
#include <math.h>
using namespace std;

Link::Link()
{
    g.y = -9.81;
}

Link::Link(double a, double alpha, double d, double theta){
    DHa = a;
    DHalpha = alpha;
    DHd = d;
    q = theta;
    update_A();
    g.y = -9.81;
}

void Link::print(){
    A.print();
}

void Link::update_A(){
    A.change(DHa, DHalpha, DHd, q);
    rici_loc.x = DHa/2.0;
    rjci_loc.x = -DHa/2.0;
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

    values["force"] = sqrt(pow(force.x,2)+pow(force.y,2));
    values["torque"] = torque.z;
    values["omega"] = q_d;
    values["alpha"] = q_dd;
    values["pcx"] = pc.x;
    values["pcy"] = pc.y;
    values["vc"] = sqrt(pow(vc.x,2)+pow(vc.y,2));;
    values["ac"] = sqrt(pow(ac.x,2)+pow(ac.y,2));;

    return values;
}

void Link::set_weight(double mass,
                double ixx,
                double ixy,
                double ixz,
                double iyy,
                double iyz,
                double izz){
    m = mass;
    I = {ixx, ixy, ixz,
         ixy, iyy, iyz,
         ixz, iyz, izz};
}

// NEWTON EULER FUNCTIONS START //

void Link::newton_euler_forward(vec alpha_h_link){
    delta_time = (double)(clock()-last_update)/CLOCKS_PER_SEC;
    calculate_translation();
    calculate_rotation(alpha_h_link);
}

void Link::newton_euler_backward(vec f_j_link, vec t_j_link, int inc_dynamic_eff){
    calculate_momentum();
    calculate_force(f_j_link, inc_dynamic_eff);
    calculate_torque(f_j_link, t_j_link, inc_dynamic_eff);
    last_update = clock();
}

void Link::calculate_momentum(){
    // rather change in momentum, therefore denoted d
    pd = ac*m; //(4.19)
    hd = I*alpha; //(4.20) Not finished
}

void Link::calculate_rotation(vec alpha_h_link){
    // Joint varaibles
    q_d = (q - q_prev)/delta_time; // (5.1)
    q_dd = (q_d - q_d_prev)/delta_time;
    q_prev = q;
    q_d_prev = q_d;

    // Global variables
    alpha = alpha_h_link + vec(0,0,q_dd);

}

void Link::calculate_translation(){
    rotMat R(A_global);
    rici = R*rici_loc;
    rjci = R*rjci_loc;
    pe = vec(A_global);
    pc = pe + rjci;
    ps = pe + rjci*2;

    vc = (pc - pc_prev)/delta_time;  // (4.15)
    ve = (pe - pe_prev)/delta_time;  // (4.15)
    ac = (vc - vc_prev)/delta_time;  // (4.16)
    ae = (ve - ve_prev)/delta_time;  // (4.16)

    pc_prev = pc;
    pe_prev = pe;
    vc_prev = vc;
    ve_prev = ve;
}

void Link::calculate_force(vec f_j_link, int inc_dynamic_eff){
    if (inc_dynamic_eff){
        force = pd + f_j_link - g*m; // (4.25)
    } else{
        force = f_j_link - g*m; // (4.25)
    }
}

void Link::calculate_torque(vec f_j_link, vec t_j_link, int inc_dynamic_eff){
    if (inc_dynamic_eff){
        torque = hd + t_j_link - force.cross(rici) +
                f_j_link.cross(rjci); // (4.26)
    } else{
        torque = t_j_link - force.cross(rici) +
                f_j_link.cross(rjci); // (4.26)
    }
}
