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
    void print_links();
    Transformation T;
    void print_coord();
    vector<double> get_coords();
    vector<vec> get_joint_forces();
    vector<vec> get_joint_torques();
    vec joint_vector(int link_index);

    void change_theta(double theta, int link_index);
    void set_theta_start(double theta, int link_index);
    void set_theta_end(double theta, int link_index);
    void animate(double percentage);
    map<string, double> get_link_map(int link_index);
    void set_weight(double m,
                    double ixx,
                    double ixy,
                    double ixz,
                    double iyy,
                    double iyz,
                    double izz,
                    int link_index);
    void print_link_global(int link_index);
    void newtonEuler();
    int n_links = 0;

private:
    vector<Link*> links;
    void update_T();
};

#endif // ROBOT_H
