#ifndef LINK_H
#define LINK_H
#include "transformation.h"
#include <string>
using namespace std;

class Link
{
public:

    Transformation A;
    Link();
    Link(double a, double alpha, double d, double theta);
    void print();
    string name;
    void change_theta(double theta);
    void move_theta(double d_theta);

private:
    // DH parameters
    double _a;
    double _alpha;
    double _d;
    double _theta;
    void update_A();
};


#endif // LINK_H
