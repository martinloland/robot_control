#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>
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
    void draw_line(double x1, double y1, double x2, double y2);
    void update_links(vector<double>& coords);
    double scaling = 1.0/300.0;

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

    void draw_axis();
    QPoint render_coord(double x, double y);
    coord2D real_coord(double x, double y);
    vector<double> robotLinks;
    void draw_links();

    int render_width;
    int render_height;
    int axis_margin = 20;

private:

    QBrush brush;

};

#endif // RENDERAREA_H
