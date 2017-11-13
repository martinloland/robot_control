#include "window.h"
#include "ui_window.h"
#include <iostream>
using namespace std;

window::window(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);
}

window::~window()
{
    delete ui;
}

void window::on_btn_add_link_clicked()
{
    double a =ui->dh_a->text().toDouble();
    double alpha =ui->dh_alpha->text().toDouble();
    double d =ui->dh_d->text().toDouble();
    double theta =ui->dh_theta->text().toDouble();
    alpha *= 3.14159265359/180.0;
    theta *= 3.14159265359/180.0;
    Link* link = new Link(a, alpha, d, theta);
    robot.addLink(link);

    QString qstr = QString::fromStdString(link->name);

    ui->links_list->addItem(qstr);

    vector<double> coords = robot.get_coords();


    ui->renderArea->update_links(coords);

//    for (vector<double>::iterator it = coords.begin();
//         it != coords.end();
//         it++){
//        double x = *it;
//        it++;
//        double y = *it;
//        cout << "(" << x << ", " << y << ")" << endl;
//    }
}

void window::on_pushButton_clicked()
{
    robot.print_links();
    cout << "Robot :" << endl;
    robot.print();
    cout << endl;
}
