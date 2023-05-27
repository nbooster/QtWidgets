#include "legendwidget.h"
#include "customqwtplot.h"
#include "legendlabel.h"

#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

LegendWidget::LegendWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 5, 0);
    setLayout(layout);
}

void LegendWidget::addCurve(QwtPlotCurve *const curve)
{
    auto label = new LegendLabel(curve, this);
    layout()->addWidget(label);
    static_cast<CustomQwtPlot *>(curve->plot())->setLegend(label);
    connect(label, &LegendLabel::clicked, this, &LegendWidget::legendClicked);
    connect(static_cast<CustomQwtPlot *>(curve->plot()), &CustomQwtPlot::clickCurve, this,
            &LegendWidget::curveClicked);
}

void LegendWidget::legendClicked(LegendLabel *legend)
{
    if (legend->isClicked())
    {
        if (_selectedLegend && legend != _selectedLegend)
            _selectedLegend->setClicked(false);
        _selectedLegend = legend;
    }
    else
    {
        _selectedLegend = nullptr;
    }
}

void LegendWidget::curveClicked(QwtPlotCurve *curve)
{
    if (curve->pen().width() == selectedCurvePenSize)
    {
        if (_selectedLegend)
        {
            _selectedLegend->setClicked(false);
            _selectedLegend = static_cast<CustomQwtPlot *>(curve->plot())->legend();
            _selectedLegend->setClicked(true);
        }
        else
        {
            _selectedLegend = static_cast<CustomQwtPlot *>(curve->plot())->legend();
            _selectedLegend->setClicked(true);
        }
    }
    else
    {
        if (_selectedLegend)
            _selectedLegend->setClicked(false);
        _selectedLegend = nullptr;
    }
}
