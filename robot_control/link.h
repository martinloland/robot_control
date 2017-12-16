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

    string name;
    vec force;
    vec torque;
    vec rici;
    vec rjci;
    double q_start = 0;
    double q_end = 0;
    double m = 0.8;

    map<string, double> getLinkMap();
    void change_theta(double theta);
    void animate(double per);
    void set_weight(double m,
                    double ixx, double ixy, double ixz,
                    double iyy, double iyz, double izz);
    void update_dynamics();
    void calculate_force(vec force_from_next_link);
    void calculate_torque(vec force_from_next_link,
                          vec torque_from_next_link);
    void print();

private:
    void update_A();

    // DH parameters
    double DHa;
    double DHalpha;
    double DHd;
    double q;
    double q_prev;

    // dynamic properties
    int last_update = 0;
    vec omega;
    vec omega_prev;
    vec alpha;
    vec ae;
    vec ac;
    inertia I;

    // geometry
    void calculate_geometry();
};


#endif // LINK_H
