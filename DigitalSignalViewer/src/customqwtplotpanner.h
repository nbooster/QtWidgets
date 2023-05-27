#pragma once

#include <qwt_plot_panner.h>

class CustomQwtPlotPanner : public QwtPlotPanner
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(CustomQwtPlotPanner)

public:
    explicit CustomQwtPlotPanner(QWidget *canvas);
    virtual ~CustomQwtPlotPanner() = default;

protected:
    virtual bool eventFilter(QObject *const, QEvent *const) override;
};
