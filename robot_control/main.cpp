#include <QCoreApplication>
#include <iostream>
#include "link.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    Link link1;
    Link link2(0.1, 0.4, 60.0, 0.45);

    return a.exec();
}
