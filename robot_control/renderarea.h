#ifndef RENDERAREA_H
#define RENDERAREA_H

#include <QWidget>
#include <QPainter>

class RenderArea : public QWidget
{
    Q_OBJECT

public:
    explicit RenderArea(QWidget *parent = nullptr);
    void draw_line(double x1, double y1, double x2, double y2);
    void draw_polyline(double *array, int n_points);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

    void draw_axis();
    QPoint render_coord(double x, double y);

    int render_width;
    int render_height;
    int axis_margin = 20;
    double scaling = 1.0/300.0;

private:

    QBrush brush;

};

#endif // RENDERAREA_H
