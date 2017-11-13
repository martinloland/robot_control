#include "link.h"
#include <iostream>
using namespace std;

Link::Link()
{
}

Link::Link(double a, double alpha, double d, double theta){
    A.change(a, alpha, d, theta);
    _a = a;
    _alpha = alpha;
    _d = d;
    theta = theta;
}

void Link::print(){
    A.print();
}
