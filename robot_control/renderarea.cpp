#include "renderarea.h"
#include <iostream>
#include <QMouseEvent>
using namespace std;

RenderArea::RenderArea(QWidget *parent)
    : QWidget(parent)
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
}

void RenderArea::resizeEvent(QResizeEvent *event)
{
    render_width = width();
    render_height = height();
    update();
}

void RenderArea::mousePressEvent(QMouseEvent *event){
    coord2D real = real_coord(event->x(), event->y());
    cout << "(" << real.x << ", " << real.y << ")" << endl;
}

void RenderArea::paintEvent(QPaintEvent *e)
{
    draw_axis();
    draw_links();
    draw_joint_forces();
    vec fVec;
    fVec.x = 1;
    fVec.y = 1;
    fVec.z = 1;
    draw_torque(fVec, fVec);
}

void RenderArea::update_joint_forces(vector<vec>& vectors){
    jointForces.clear();
    for (vec n : vectors){
        jointForces.push_back(n);
    }
    repaint();
}

void RenderArea::draw_joint_forces(){
    if (jointForces.size() >= 2){
        for (int i=0; i<=jointForces.size()-2; i+=2){
            draw_force(jointForces.at(i), jointForces.at(i+1));
        }
    }
}

void RenderArea::draw_links(){
    if (robotLinks.size() >= 4){
        for (int i=0; i<robotLinks.size()-2; i+=2){
            draw_line(robotLinks.at(i), robotLinks.at(i+1),
                      robotLinks.at(i+2), robotLinks.at(i+3));
        }
    }
}

void RenderArea::update_links(vector<double>& coords){
    robotLinks.clear();
    for (double n : coords){
        robotLinks.push_back(n);
    }
    repaint();
}

void RenderArea::draw_line(double x1, double y1, double x2, double y2){
    QPainter painter(this);
    painter.drawLine(render_coord(x1,y1),
                     render_coord(x2,y2));
}

void RenderArea::draw_force(vec startVec, vec fVec){
    double k = sqrt(pow(fVec.x,2) + pow(fVec.y,2))/2000.0;
    double ang = atan2(fVec.y, fVec.x);
    QPainter painter(this);
    QPen pen(Qt::green, 3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(pen);
    vec p1 = transform_2Dvector(0.0, 0.0, startVec, ang, k);
    vec p2 = transform_2Dvector(3.0, 0.0, startVec, ang, k);
    vec p3 = transform_2Dvector(2.5, 0.5, startVec, ang, k);
    vec p4 = transform_2Dvector(2.5, -0.5, startVec, ang, k);

    painter.drawLine(render_coord(p1.x, p1.y),
                     render_coord(p2.x, p2.y));
    painter.drawLine(render_coord(p2.x, p2.y),
                     render_coord(p3.x, p3.y));
    painter.drawLine(render_coord(p2.x, p2.y),
                     render_coord(p4.x, p4.y));
}

void RenderArea::draw_torque(vec startVec, vec tVec){
    double k = abs(tVec.z/10.0);
    QPainter painter(this);
    QPen pen(Qt::red, 3, Qt::SolidLine, Qt::SquareCap, Qt::RoundJoin);
    painter.setPen(pen);
    vec p1, p2, p3;
    vec tl = transform_2Dvector(-1.0, 1.0, startVec, 0.0, k);
    vec br = transform_2Dvector(1.0, -1.0, startVec, 0.0, k);
    p1 = transform_2Dvector(0.3, 1.3, startVec, 0.0, k);
    p2 = transform_2Dvector(0.0, 1.0, startVec, 0.0, k);
    p3 = transform_2Dvector(0.3, 0.7, startVec, 0.0, k);
    QRectF rect(render_coord(tl.x, tl.y), render_coord(br.x, br.y));
    int startAngle = 180 * 16;
    int spanAngle = 270 * 16;
    if (tVec.z < 0){
        startAngle = 90 * 16;
        spanAngle = 270 * 16;
        p1 = transform_2Dvector(-0.3, 1.3, startVec, 0.0, k);
        p3 = transform_2Dvector(-0.3, 0.7, startVec, 0.0, k);
    }
    painter.drawLine(render_coord(p1.x, p1.y),
                     render_coord(p2.x, p2.y));
    painter.drawLine(render_coord(p2.x, p2.y),
                     render_coord(p3.x, p3.y));
    painter.drawArc(rect, startAngle, spanAngle);
}

void RenderArea::draw_axis(){
    QPainter painter(this);
    int margin=axis_margin;
    QPoint points[3] = {
        QPoint(margin, margin),
        QPoint(margin, render_height-margin),
        QPoint(render_width-margin, render_height-margin)
    };
    painter.drawPolyline(points, 3);

    brush = QBrush(Qt::SolidPattern);
    painter.setBrush(brush);

    int width=10;
    QPoint arrow1[3] = {
        QPoint(margin-width/2, margin),
        QPoint(margin, margin-width),
        QPoint(margin+width/2, margin)
    };
    QPoint arrow2[3] = {
        QPoint(render_width-margin, render_height-margin-width/2),
        QPoint(render_width-margin+width, render_height-margin),
        QPoint(render_width-margin, render_height-margin+width/2)
    };
    painter.drawPolygon(arrow1, 3);
    painter.drawPolygon(arrow2, 3);
}

QPoint RenderArea::render_coord(double x, double y){
    return QPoint(x/scaling+axis_margin,
                  render_height-y/scaling-axis_margin);
}

coord2D RenderArea::real_coord(double x, double y){
    coord2D cor;
    cor.x = (x-axis_margin)*scaling;
    cor.y = (render_height-y-axis_margin)*scaling;
    return cor;
}
