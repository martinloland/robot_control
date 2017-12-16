#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include "link.h"
#include "robot.h"

namespace Ui {
class window;
}

class window : public QMainWindow
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0);
    ~window();
    Robot robot;

private slots:
    void on_btn_add_link_clicked();

    void on_print_robot_clicked();

    void on_btn_for_move_clicked();

    void on_ui_scale_valueChanged(int value);

    void on_btn_add_default_clicked();

    void on_for_theta_sli_valueChanged(int value);

    void on_btn_setStart_clicked();

    void on_btn_setEnd_clicked();

    void on_animForward_clicked();

    void on_animBack_clicked();

    void on_links_list_clicked(const QModelIndex &index);

    void on_btn_setWeight_clicked();

    void on_disp_for_clicked(bool checked);

    void on_disp_tor_clicked(bool checked);

    void on_disp_vel_clicked(bool checked);

    void on_disp_acc_clicked(bool checked);

private:
    Ui::window *ui;
    void start_animation(int forward);
    void update_variables(int link_index);
    void update_robot(int inc_dynamic_eff);
    void update_table_text();

};

#endif // WINDOW_H
