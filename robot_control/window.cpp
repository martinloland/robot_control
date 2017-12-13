#include "window.h"
#include "ui_window.h"
#include <iostream>
#include <time.h>
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
    ui->for_theta_sli->setValue(ui->for_theta->text().toDouble());
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

void window::on_for_theta_sli_valueChanged(int value)
{
    ui->for_theta->clear();
    ui->for_theta->insert(QString::number(value));
    on_btn_for_move_clicked();
}

void window::on_btn_setStart_clicked()
{
    int link_index = ui->links_list->currentRow();
    if (link_index >= 0){
        double theta = ui->for_theta->text().toDouble()*3.14159265359/180.0;
        robot.set_theta_start(theta, link_index);
    }
}

void window::on_btn_setEnd_clicked()
{
    int link_index = ui->links_list->currentRow();
    if (link_index >= 0){
        double theta = ui->for_theta->text().toDouble()*3.14159265359/180.0;
        robot.set_theta_end(theta, link_index);
    }

}

void window::on_animForward_clicked()
{
    start_animation(1);
}

void window::on_animBack_clicked()
{
    start_animation(0);
}

void window::start_animation(int forward){
    int tot_anim_time = ui->anim_time->text().toInt()*1000;
    int start_time = clock();
    double anim_percent = 0.0;
    while (clock()-start_time < tot_anim_time){
        if (forward){
            anim_percent = ((double)clock()-(double)start_time)/(double)tot_anim_time;
        }else{
            anim_percent = 1.0-((double)clock()-(double)start_time)/(double)tot_anim_time;
        }
        cout << anim_percent << endl;
    }
}
