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
    update_T();
}

void Robot::update_T(){
    T.identity();
    if (n_links>0){
        for (Link* n : links){
            T *= n->A;
            n->A_global = T;
        }
    }
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

vec Robot::joint_vector(int link_index){
    Transformation to_joint_T;
    to_joint_T.identity();
    for (int i = 0; i < link_index; i++){
        to_joint_T *= links.at(i)->A;
    }
    vec to_joint_vec;
    to_joint_vec.x = to_joint_T.T[0][3];
    to_joint_vec.y = to_joint_T.T[1][3];
    return to_joint_vec;
}

vector<vec> Robot::get_joint_forces(){
    vector<vec> force_vectors;

    for (int i = 0; i < links.size(); i++){
        force_vectors.push_back(joint_vector(i));
        force_vectors.push_back(links.at(i)->force);
    }
    return force_vectors;
}

vector<vec> Robot::get_joint_torques(){
    vector<vec> torque_vectors;

    for (int i = 0; i < links.size(); i++){
        torque_vectors.push_back(joint_vector(i));
        torque_vectors.push_back(links.at(i)->torque);
    }
    return torque_vectors;
}

void Robot::change_theta(double theta, int link_index){
    links.at(link_index)->change_theta(theta);
    update_T();
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

void Robot::newtonEuler(){
    // Forward Newton Euler
    for (Link* n : links){
        n->newton_euler_forward();
    }

    // Backward Newton Euler
    vec endEffectorLoad;
    vec endEffectorTorque;
    for (int i = links.size()-1; i >= 0; i--){
        if (i == (int)links.size()-1){
            links.at(i)->newton_euler_backward(endEffectorLoad,
                                               endEffectorTorque);
        } else {
            links.at(i)->newton_euler_backward(links.at(i+1)->force,
                                               links.at(i+1)->torque);
        }
    }
    update_T();
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
