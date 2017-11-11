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

    Link link(a, alpha, d, theta);
    robot.addLink(&link);
    robot.print();

    QString qstr = QString::fromStdString(link.name);

    ui->links_list->addItem(qstr);
//    ui->renderArea.drawLines(robot.get_points())

    vector<double> coords = robot.get_coords();
    for (double n : coords){
        cout << n << endl;
    }
}
