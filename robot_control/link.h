#ifndef LINK_H
#define LINK_H
#include <string>
#include <map>
#include <time.h>
#include "vector_lib.h"
#include "transformation.h"
using namespace std;

class Link
{
public:

    Transformation A;
    Transformation A_global;
    Link();
    Link(double a, double alpha, double d, double theta);
    void print();
    string name;
    void change_theta(double theta);
    void move_theta(double d_theta);
    double theta_start = 0;
    double theta_end = 0;
    void animate(double per);
    map<string, double> getLinkMap();
    void set_weight(double m,
                    double ixx,
                    double ixy,
                    double ixz,
                    double iyy,
                    double iyz,
                    double izz);
    void update_dynamics();
    vec force;
    vec torque;
    void calculate_force(vec force_from_next_link);
    void calculate_torque(vec force_from_next_link,
                          vec torque_from_next_link);
    vec rici;
    vec rjci;
    double _m = 0;

private:
    // DH parameters
    double _DHa;
    double _DHalpha;
    double _DHd;
    double _theta;
    double _theta_prev;
    void update_A();

    // dynamic properties
    int last_update = 0;
    vec _omega;
    vec _omega_prev;
    vec _alpha;
    vec _ae;
    vec _ac;
    inertia _I;

    // geometry
    void calculate_geometry();

};


#endif // LINK_H
