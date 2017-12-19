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
    void update_link_vectors(vector<vec>& vectors);
    void update_end_eff_vectors(vector<vec>& vectors);
    int scale = 300;
    double scaling = 1.0/300.0;
    bool disp_force = 1;
    bool disp_torque = 1;
    bool disp_velocity = 1;
    bool disp_acceleration = 1;

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
    vector<vec> link_vectors;
    vector<vec> end_eff_vectors;
    void draw_links();
    void draw_link_vectors();
    void draw_end_effector();

    int render_width;
    int render_height;
    int x_margin = 200;
    int y_margin = 200;

private:

    void draw_line(double x1, double y1, double x2, double y2);
    void draw_arrow(vec startVec, vec fVec, QColor color, double scale);
    void draw_circle(vec startVec, vec tVec, QColor color, double scale);
    QBrush brush;

    QPoint m_lastPos;

};

#endif // RENDERAREA_H
