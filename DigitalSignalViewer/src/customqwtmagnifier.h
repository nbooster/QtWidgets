#pragma once

#include <QWidget>
#include <qwt_plot_magnifier.h>

class CustomQwtPlotMagnifier : public QwtPlotMagnifier
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(CustomQwtPlotMagnifier)

public:
    explicit CustomQwtPlotMagnifier(QWidget *canvas);
    virtual ~CustomQwtPlotMagnifier() = default;
};
