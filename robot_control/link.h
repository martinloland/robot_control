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
    Link();
    Link(double a, double alpha, double d, double theta);

    // Local values
    Transformation A;

    // Global values
    Transformation A_global;
    vec force;
    vec torque;
    vec alpha;
    vec ps;
    vec pc;
    vec vc;
    vec ac;
    void calculate_translation();

    string name;
    double q_start = 0;
    double q_end = 0;
    double m = 0.8;
    map<string, double> getLinkMap();
    void change_theta(double theta);
    void animate(double per);
    void set_weight(double m,
                    double ixx, double ixy, double ixz,
                    double iyy, double iyz, double izz);
    void print();

    void newton_euler_forward(vec alpha_h_link);
    void newton_euler_backward(vec f_j_link, vec t_j_link, int inc_dynamic_eff);

private:
    void update_A();

    // Time
    clock_t last_update = clock();
    double delta_time;

    // DH parameters
    double DHa;
    double DHalpha;
    double DHd;

    // Local values
    double q;
    double q_prev;
    double q_d;
    double q_d_prev;
    double q_dd;
    inertia I;
    vec rici_loc;
    vec rjci_loc;

    // Global values
    vec omega;
    vec omega_prev;
    vec g;
    vec rici;
    vec rjci;
    // Linear position, velocity and acceleration
    vec pc_prev;
    vec pe;
    vec pe_prev;
    vec vc_prev;
    vec ve;
    vec ve_prev;
    vec ae;
    // Linear and angular momentum
    vec pd;
    vec hd;

    // Helper methods for newton euler
    void calculate_rotation(vec alpha_h_link);
    void calculate_momentum();
    void calculate_force(vec force_from_next_link, int inc_dynamic_eff);
    void calculate_torque(vec force_from_next_link,
                          vec torque_from_next_link, int inc_dynamic_eff);
};


#endif // LINK_H
