#ifndef ROBOT_H
#define ROBOT_H

#include "link.h"
#include "transformation.h"
#include <iostream>
#include <vector>

using namespace std;

class Robot
{
public:
    Robot();

    void addLink(Link* link);
    void print();
    Transformation T;
    void print_coord();


private:
    int n_links = 0;
    vector<Link*> links;
    void update_T();
};

#endif // ROBOT_H
