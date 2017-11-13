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
}

void window::on_print_robot_clicked()
{
    robot.print_links();
    cout << "Robot :" << endl;
    robot.print();
    cout << endl;
}

void window::on_btn_for_move_clicked()
{
    int link_index = ui->links_list->currentRow();
    double theta = ui->for_theta->text().toDouble()*3.14159265359/180.0;
    if (link_index >=0){
        robot.change_theta(theta, link_index);
    }
    vector<double> coords = robot.get_coords();
    ui->renderArea->update_links(coords);
}

void window::on_ui_scale_valueChanged(int value)
{
    ui->renderArea->scaling = 1.0/value;
    ui->renderArea->update();
}

void window::on_btn_add_default_clicked()
{
    Link* link1 = new Link(1.0, 0, 0, 45.0*3.14159265359/180.0);
    Link* link2 = new Link(0.8, 0, 0, -45.0*3.14159265359/180.0);

    robot.addLink(link1);
    QString qstr = QString::fromStdString(link1->name);
    ui->links_list->addItem(qstr);

    robot.addLink(link2);
    QString qstr2 = QString::fromStdString(link2->name);
    ui->links_list->addItem(qstr2);

    vector<double> coords = robot.get_coords();
    ui->renderArea->update_links(coords);
}

void window::on_btn_inv_move_clicked()
{
    Transformation t;
    t.displace(ui->inv_x->text().toDouble(),
                ui->inv_y->text().toDouble(),
                ui->inv_z->text().toDouble());
    robot.inverse(&t);
}
