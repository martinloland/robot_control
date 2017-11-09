#ifndef LINK_H
#define LINK_H


class Link
{
public:

    Link();
    Link(double a, double alpha, double d, double theta);

private:
    // DH parameters
    double _a;
    double _alpha;
    double _d;
    double _theta;
};

#endif // LINK_H
