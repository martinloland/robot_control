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

vector<vec> Robot::get_joint_forces(){
    vector<vec> force_vectors;

    for (int i = 0; i < links.size(); i++){
        force_vectors.push_back(links.at(i)->ps);
        force_vectors.push_back(links.at(i)->force);
    }
    return force_vectors;
}

vector<vec> Robot::get_joint_torques(){
    vector<vec> torque_vectors;

    for (int i = 0; i < links.size(); i++){
        torque_vectors.push_back(links.at(i)->ps);
        torque_vectors.push_back(links.at(i)->torque);
    }
    return torque_vectors;
}

vector<vec> Robot::get_link_velocities(){
    vector<vec> link_velocities;

    for (int i = 0; i < links.size(); i++){
        link_velocities.push_back(links.at(i)->pc);
        link_velocities.push_back(links.at(i)->vc);
    }
    return link_velocities;
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

    T.identity();
    for (Link* n : links){
        T *= n->A;
        n->A_global = T;
        n->newton_euler_forward();
    }

    // Backward Newton Euler
    vec endEffectorLoad;
    vec endEffectorTorque;
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
