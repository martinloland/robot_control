#include "window.h"
#include "link.h"
#include <QApplication>
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    window w;
    w.show();

//    Link l1(0.2, 0, 0, 0.785398163);
//    Link l2(0.2, 0, 0, -0.785398163);
//    Transformation t;
//    Robot r;
//    r.addLink(&l1);
//    r.addLink(&l2);
//    r.T.print();

//    l1.print();
//    cout << endl;
//    l2.print();
//    cout << endl;
//    t.print();
//    t *= l1.A;
//    cout << endl;
//    t.print();
//    t *= l1.A;
//    cout << endl;
//    t.print();


    return a.exec();
}
