#pragma once

#include "scrollareawidget.h"
#include "customqwtscaledraw.h"

#include <QVBoxLayout>

ScrollAreaWidget::ScrollAreaWidget(QWidget *parent) : QWidget(parent)
{
    auto layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignTop);
    layout->setContentsMargins(0, 0, 0, 10);
    setLayout(layout);
}

void ScrollAreaWidget::addScale(QwtScaleWidget *const scale)
{
    layout()->addWidget(scale);
    _scale = scale;
    _scale->setContentsMargins(0, 0, 0, 0); // ?
}

void ScrollAreaWidget::addWidget(CustomQwtPlot *const plot)
{
    _plots.push_back(plot);
    connect(plot, &CustomQwtPlot::updateAxisDiv, this, &ScrollAreaWidget::changeScale);
    if (_scale)
    {
        _scale->setFont(plot->axisFont(QwtPlot::xBottom));
        static_cast<QVBoxLayout *>(layout())->insertWidget(layout()->count() - 1, plot);
        plot->setContentsMargins(0, 0, 0, 0);
        _scale->setScaleDiv(plot->axisScaleDiv(QwtPlot::xBottom));
        static_cast<CustomQwtScaleDraw *>(_scale->scaleDraw())
            ->update(plot->axisScaleDiv(QwtPlot::xBottom));
        auto firstTickBoundRect
            = _scale->scaleDraw()->boundingLabelRect(_scale->font(),
                                                     _scale->scaleDraw()->scaleDiv().lowerBound());
        auto lastTickBoundRect
            = _scale->scaleDraw()->boundingLabelRect(_scale->font(),
                                                     _scale->scaleDraw()->scaleDiv().upperBound());
        auto leftMargin = firstTickBoundRect.center().x() - firstTickBoundRect.left();
        auto rightMargin = lastTickBoundRect.right() - lastTickBoundRect.center().x();
        for (auto plot : _plots)
            plot->setContentsMargins(leftMargin - 4, 0, rightMargin - 4, 0);
    }
    else
    {
        layout()->addWidget(plot);
    }
}

void ScrollAreaWidget::changeScale(const QwtScaleDiv div) { _scale->setScaleDiv(div); }
