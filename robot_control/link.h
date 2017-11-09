#ifndef LINK_H
#define LINK_H
#include "transformation.h"

class Link
{
public:

    Transformation A;
    Link();
    Link(double a, double alpha, double d, double theta);
    void print();

private:
    // DH parameters
    double _a;
    double _alpha;
    double _d;
    double _theta;
};


#endif // LINK_H
