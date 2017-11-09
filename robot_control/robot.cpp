#include "robot.h"
#include <iostream>
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

    cout << "(" << T.x() << "," << T.y() << "," << T.z() << ")" << endl;
}

void Robot::addLink(Link* link){
    links.push_back(link);
    n_links += 1;
    cout << "total links in robot: " << n_links << endl;
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
