#pragma once

#include "legendlabel.h"

#include <QWidget>
#include <qwt_plot_curve.h>

class LegendWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(LegendWidget)

public:
    LegendWidget(QWidget *parent);
    ~LegendWidget() = default;
    void addCurve(QwtPlotCurve *const curve);

public slots:
    void curveClicked(QwtPlotCurve *);
    void legendClicked(LegendLabel *);

private:
    LegendLabel *_selectedLegend = nullptr;
};
