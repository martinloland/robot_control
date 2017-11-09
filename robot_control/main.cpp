#include <QCoreApplication>
#include <iostream>
#include "link.h"
#include "robot.h"
#include "transformation.h"

using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Robot robot;
    Link link1(1.2, 0, 0, 3.14/8);
    Link link2(0.7, 0, 0, 3.14/4);
    robot.addLink(&link1);
    robot.addLink(&link2);

    robot.print();
    robot.print_coord();

    return a.exec();
}
