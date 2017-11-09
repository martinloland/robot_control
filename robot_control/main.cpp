#include <QCoreApplication>
#include <iostream>
#include "link.h"
#include "transformation.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link link1;
    Link link2(0.1, 0.4, 60.0, 0.45);
    Transformation t(1.2, 0, 0, 3.14/8);

    t.print();

    return a.exec();
}
