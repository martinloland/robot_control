#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H



class Transformation
{
public:
    Transformation();
    Transformation(double a, double alpha, double d, double theta);

    double T[4][4] = {0};

    void print();
};

#endif // TRANSFORMATION_H
