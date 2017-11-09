#include "link.h"
#include <iostream>
using namespace std;

Link::Link()
{
    cout << "created undefined link\n";
}

Link::Link(double a, double alpha, double d, double theta){
    A.change(a, alpha, d, theta);
    _a = a;
    _alpha = alpha;
    _d = d;
    _theta = theta;
    cout << "created link from DH param\n";
}

void Link::print(){
    A.print();
}
