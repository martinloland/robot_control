#include "robot.h"
#include <iostream>
#include <sstream>
using namespace std;

Robot::Robot()
{

}

void Robot::print(){
    cout << "total links in robot: " << n_links << ", T:" << endl;
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
        }
    }
}

vector<double> Robot::get_coords(){
    Transformation homo;
    homo.identity();
    vector<double> coords;
    for (Link* n : links){
        homo *= n->A;
        coords.push_back(homo.T[0][3]);
        coords.push_back(homo.T[1][3]);
    }
    return coords;
}
