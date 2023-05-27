#pragma once

#include "customqwtplot.h"

#include <QWidget>
#include <qwt_plot.h>
#include <qwt_scale_widget.h>

class QwtScaleWidget;

class ScrollAreaWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(ScrollAreaWidget)

public:
    ScrollAreaWidget(QWidget *parent = nullptr);
    ~ScrollAreaWidget() = default;
    void addScale(QwtScaleWidget *const);
    void addWidget(CustomQwtPlot *const);

public slots:
    void changeScale(const QwtScaleDiv); // CustomQwtPlot *const);

private:
    QwtScaleWidget *_scale = nullptr;
    std::vector<QwtPlot *> _plots;
};
