#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
#include "vector_lib.h"
using namespace std;

struct coord2D{
    double x;
    double y;
};

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    void update_links(vector<double>& coords);
    void update_joint_forces(vector<vec>& vectors);
    void update_joint_torques(vector<vec>& vectors);
    int scale = 300;
    double scaling = 1.0/300.0;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;

    void draw_axis();
    QPoint render_coord(double x, double y);
    coord2D real_coord(double x, double y);
    vector<double> robotLinks;
    vector<vec> jointForces;
    vector<vec> jointTorques;
    void draw_links();
    void draw_joint_forces();
    void draw_joint_torques();

    int render_width;
    int render_height;
    int x_margin = 100;
    int y_margin = 100;

private:

    void draw_line(double x1, double y1, double x2, double y2);
    void draw_force(vec startVec, vec fVec);
    void draw_torque(vec startVec, vec tVec);
    QBrush brush;

    QPoint m_lastPos;

};

#endif // RENDERAREA_H
