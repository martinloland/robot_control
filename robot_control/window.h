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

private:
    Ui::window *ui;
};

#endif // WINDOW_H
