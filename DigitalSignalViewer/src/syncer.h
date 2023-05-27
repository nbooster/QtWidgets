#pragma once

#include "customqwtplot.h"

#include <qwt_scale_div.h>

class Syncer : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(Syncer)

public:
    Syncer(QWidget *parent = nullptr);
    ~Syncer() = default;
    void addPlot(CustomQwtPlot *);

public slots:
    void updatedMinMax(double min, double max);
    void updatedAxisDiv(QwtScaleDiv div);
    void updatedPrevBounds(double plb, double pub);
    void updatedLastX(double lastx);

private:
    std::vector<CustomQwtPlot *> _plots;
};
