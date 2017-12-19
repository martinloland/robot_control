#include "robot.h"
#include <iostream>
#include <sstream>
using namespace std;

Robot::Robot()
{
}

void Robot::print(){
    T.print();
}

void Robot::print_coord(){
    cout.precision(2);
    cout << "(x,y,z) = ";
    cout << "(" << T.x() << ", " << T.y() << ", " << T.z() << ")" << endl;
}

void Robot::addLink(Link* link){
    stringstream ss;
    ss << "Link " << n_links+1;
    link->name = ss.str();
    links.push_back(link);
    n_links += 1;
    newtonEuler(0);
}

void Robot::print_links(){
    for (Link* n : links){
        cout << n->name << " :" << endl;
        n->print();
        cout << endl;
    }
}

vector<double> Robot::get_coords(){
    Transformation homo;
    homo.identity();
    vector<double> coords;
    coords.push_back(0);
    coords.push_back(0);
    for (Link* n : links){
        homo *= n->A;
        coords.push_back(homo.T[0][3]);
        coords.push_back(homo.T[1][3]);
    }
    return coords;
}

vector<vec> Robot::get_link_vectors(){
    vector<vec> vectors;
    for (int i = 0; i < links.size(); i++){
        vectors.push_back(links.at(i)->ps);
        vectors.push_back(links.at(i)->pc);
        vectors.push_back(links.at(i)->force);
        vectors.push_back(links.at(i)->torque);
        vectors.push_back(links.at(i)->vc);
        vectors.push_back(links.at(i)->ac);
    }
    return vectors;
}


vector<vec> Robot::get_end_eff_vectors(){
    vector<vec> vectors;
    vec pos_end_eff = vec(T);
    vectors.push_back(pos_end_eff);
    vectors.push_back(endEffectorLoad);
    vectors.push_back(endEffectorTorque);
    return vectors;
}

void Robot::change_theta(double theta, int link_index){
    links.at(link_index)->change_theta(theta);
    newtonEuler(0);
}

void Robot::set_theta_start(double theta, int link_index){
    links.at(link_index)->q_start = theta;
}

void Robot::set_theta_end(double theta, int link_index){
    links.at(link_index)->q_end = theta;
}

void Robot::animate(double percentage){
    for (Link* n : links){
        n->animate(percentage);
    }
}

void Robot::newtonEuler(int inc_dynamic_eff){
    // Forward Newton Euler
    vec alpha_h_link(0.0, 0.0, 0.0);
    T.identity();
    for (Link* n : links){
        T *= n->A;
        n->A_global = T;
        n->newton_euler_forward(alpha_h_link);
        alpha_h_link = n->alpha;
    }

    // Backward Newton Euler
    for (int i = links.size()-1; i >= 0; i--){
        if (i == (int)links.size()-1){
            links.at(i)->newton_euler_backward(endEffectorLoad,
                                               endEffectorTorque,
                                               inc_dynamic_eff);
        } else {
            links.at(i)->newton_euler_backward(links.at(i+1)->force,
                                               links.at(i+1)->torque,
                                               inc_dynamic_eff);
        }
    }
}

map<string, double> Robot::get_link_map(int link_index){
    return links.at(link_index)->getLinkMap();
}


void Robot::set_end_effector_load(double efx, double efy, double efz,
                          double etx, double ety, double etz){
    endEffectorLoad.x = efx;
    endEffectorLoad.y = efy;
    endEffectorLoad.z = efz;

    endEffectorTorque.x = etx;
    endEffectorTorque.y = ety;
    endEffectorTorque.z = etz;
}

void Robot::set_weight(double m,
                double ixx,
                double ixy,
                double ixz,
                double iyy,
                double iyz,
                double izz,
                int link_index){
    links.at(link_index)->set_weight(m, ixx, ixy, ixz, iyy, iyz, izz);

}

void Robot::print_link_global(int link_index){
    rotMat R(links.at(link_index)->A_global);
    R.print();
}
