#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H

class Transformation
{
public:
    Transformation();
    Transformation(double a, double alpha, double d, double theta);

    double T[4][4] = {0};
    void print();
    void change(double a, double alpha, double d, double theta);
    void identity();
    void zero();
    void replace(const Transformation& t);
    void displace(double x, double y, double z);

    double x();
    double y();
    double z();

    Transformation operator*(const Transformation& b);
    void operator*=(const Transformation& b);
};

#endif // TRANSFORMATION_H
