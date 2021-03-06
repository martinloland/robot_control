#include "window.h"
#include "ui_window.h"
#include <iostream>
#include <time.h>
#include <Windows.h>
#include "link.h"
#include "vector_lib.h"
#include <fstream>

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
    cout << "=======================" << endl;
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
    update_robot(0);
}

void window::on_ui_scale_valueChanged(int value)
{
    ui->renderArea->scaling = 1.0/value;
    ui->renderArea->update();
}

void window::on_btn_add_default_clicked()
{
    Link* link1 = new Link(1.0, 0, 0, 1.4);
    Link* link2 = new Link(0.8, 0, 0, -2.0);
    Link* link3 = new Link(0.5, 0, 0, -1.92);
    link1->q_start = 1.4;
    link1->q_end = 0.17;
    link1->m = 1.2;
    link2->q_start = -2.0;
    link2->q_end = 1.9;
    link2->m = 0.8;
    link3->q_start = -1.92;
    link3->q_end = 1.0;
    link3->m = 0.6;

    robot.addLink(link1);
    QString qstr = QString::fromStdString(link1->name);
    ui->links_list->addItem(qstr);

    robot.addLink(link2);
    QString qstr2 = QString::fromStdString(link2->name);
    ui->links_list->addItem(qstr2);

    robot.addLink(link3);
    QString qstr3 = QString::fromStdString(link3->name);
    ui->links_list->addItem(qstr3);

    vector<double> coords = robot.get_coords();
    ui->renderArea->update_links(coords);
    update_robot(0);
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
    double tot_anim_time = ui->anim_time->text().toDouble()*1000.0;
    int start_time = clock();
    int last_step = 0;
    double anim_percent = 0.0;
    double frames;
    ofstream myfile;
    char buf[256];

    if (exportData){
        char filename[100];
        sprintf(filename,"%s",ui->exportPath->text().toUtf8().constData());
        cout << filename << endl;
        myfile.open (filename);
        myfile << "total time: " << tot_anim_time << " ms\n";
        myfile << "per";
        for (int i = 0; i < robot.n_links; i++){
            sprintf(buf,",q%d,qd%d,qdd%d,f%d,t%d,v%d,a%d",i+1,i+1,i+1,i+1,i+1,i+1,i+1);
            myfile << buf;
        }
        myfile << "\n";
    }

    while (clock()-start_time < tot_anim_time){
        if (clock() - last_step > 25){ // Aprox constant fps
            if (forward){
                anim_percent = ((double)clock()-(double)start_time)/tot_anim_time;
            }else{
                anim_percent = 1.0-((double)clock()-(double)start_time)/tot_anim_time;
            }
            robot.animate(anim_percent);
            update_robot(ui->incDynEff->isChecked());
            if (exportData){
                myfile << anim_percent;
                for (int i = 0; i < robot.n_links; i++){
                    map<string, double> val = robot.get_link_map(i);
                    sprintf(buf, ",%f,%f,%f,%f,%f,%f,%f",val["theta"],val["omega"],val["alpha"],val["force"],val["torque"],val["vc"],val["ac"]);
                    myfile << buf;
                }
                myfile << "\n";
            }
            frames+=1.0;
            last_step = clock();
        }
    }
    // smooth out
    for(int i=1; i <4; i++){
        robot.animate(forward);
        update_robot(ui->incDynEff->isChecked());
    }
    if (exportData){
        myfile.close();
    }
//    cout << "fps:" << (frames / tot_anim_time) * 1000.0 << endl;
}

void window::update_robot(int inc_dynamic_eff){
    robot.newtonEuler(inc_dynamic_eff);
    vector<double> coords = robot.get_coords();
    ui->renderArea->update_links(coords);
    vector<vec> vectors = robot.get_link_vectors();
    ui->renderArea->update_link_vectors(vectors);
    vector<vec> endeffvec = robot.get_end_eff_vectors();
    ui->renderArea->update_end_eff_vectors(endeffvec);
    ui->renderArea->repaint();
    update_table_text();
}


void window::on_links_list_clicked(const QModelIndex &index)
{
    update_variables(index.row());
}

void window::update_table_text(){
    char buf[256];
    ui->table->clear();
    sprintf(buf, "%-6s %-8s %-8s %-8s %-8s %-8s",
            "Link", "Force", "Torque", "Theta", "Velocity", "Accel.");
    ui->table->append(QString(buf));


    for (int i = 0; i < robot.n_links; i++){
        map<string, double> val;
        val = robot.get_link_map(i);
        sprintf(buf, "%-6d %8.2f %8.2f %8.2f %8.2f %8.2f",
                i+1, val["force"], val["torque"],
                val["theta"], val["omega"], val["alpha"]);
        ui->table->append(QString(buf));
    }
    sprintf(buf, "%-6s %-8s %-8s %-8s %-8s %-8s",
            "#", "N", "Nm", "rad", "rad/s", "rad/s^2");
    ui->table->append(QString(buf));
}

void window::update_variables(int link_index){
    map<string, double> values;
    values = robot.get_link_map(link_index);
    ui->for_theta_sli->setValue(values["theta"]*180.0/3.14159265359);
    ui->dh_a->setText(QString::number(values["DHa"]));
    ui->dh_alpha->setText(QString::number(values["DHalpha"]));
    ui->dh_d->setText(QString::number(values["DHd"]));
    ui->dh_theta->setText(QString::number(values["theta"]));
    ui->mass->setText(QString::number(values["m"]));
    ui->ixx->setText(QString::number(values["ixx"]));
    ui->ixy->setText(QString::number(values["ixy"]));
    ui->ixz->setText(QString::number(values["ixz"]));
    ui->iyy->setText(QString::number(values["iyy"]));
    ui->iyz->setText(QString::number(values["iyz"]));
    ui->izz->setText(QString::number(values["izz"]));
}

void window::on_btn_setWeight_clicked()
{
    int link_index = ui->links_list->currentRow();
    if (link_index >= 0){
        robot.set_weight(
                    ui->mass->text().toDouble(),
                    ui->ixx->text().toDouble(),
                    ui->ixy->text().toDouble(),
                    ui->ixz->text().toDouble(),
                    ui->iyy->text().toDouble(),
                    ui->iyz->text().toDouble(),
                    ui->izz->text().toDouble(),
                    link_index);
    }
    update_robot(0);
}

void window::on_disp_for_clicked(bool checked)
{
    ui->renderArea->disp_force = checked;
}

void window::on_disp_tor_clicked(bool checked)
{
    ui->renderArea->disp_torque = checked;
}

void window::on_disp_vel_clicked(bool checked)
{
    ui->renderArea->disp_velocity = checked;
}

void window::on_disp_acc_clicked(bool checked)
{
    ui->renderArea->disp_acceleration = checked;
}

void window::on_checkBox_clicked(bool checked)
{
    exportData = checked;
}

void window::on_set_end_eff_load_clicked()
{
    robot.set_end_effector_load(-ui->efx->text().toDouble(),
                                -ui->efy->text().toDouble(),
                                -ui->efz->text().toDouble(),
                                -ui->etx->text().toDouble(),
                                -ui->ety->text().toDouble(),
                                -ui->etz->text().toDouble());
    update_robot(0);
}
