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

    return a.exec();
}
