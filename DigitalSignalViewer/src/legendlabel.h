#pragma once

#include <qwt_plot_curve.h>

#include <QLabel>

class LegendLabel : public QLabel
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LegendLabel)

public:
    LegendLabel(QwtPlotCurve *, QWidget *parent = nullptr);
    ~LegendLabel() = default;
    void mousePressEvent(QMouseEvent *const event);
    void setClicked(bool legend);
    bool isClicked();
    void paintEvent(QPaintEvent *const event);

signals:
    void clicked(LegendLabel *);

private:
    QwtPlotCurve *_curve = nullptr;
    bool _clicked = false;
};
