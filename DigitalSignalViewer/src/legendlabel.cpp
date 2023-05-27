#include "legendlabel.h"
#include "customqwtplot.h"

#include <qevent.h>

LegendLabel::LegendLabel(QwtPlotCurve *curve, QWidget *parent)
    : QLabel(curve->title().text(), parent), _curve(curve)
{
    setFont(QFont("Times", 10));
    setLineWidth(3);
    setFrameStyle(QFrame::Panel | QFrame::Raised);
    setStyleSheet("QLabel { font: bold; color : black; background-color: white;}");
}

bool LegendLabel::isClicked() { return _clicked; }

void LegendLabel::setClicked(bool clickedArg)
{
    _clicked = clickedArg;
    if (clickedArg)
        _curve->setPen(_curve->pen().color(), selectedCurvePenSize);
    else
        _curve->setPen(_curve->pen().color(), unselectedCurvePenSize);
    update();
}

void LegendLabel::mousePressEvent(QMouseEvent *const event)
{
    if (event->button() != Qt::LeftButton)
        return;
    if (!_clicked)
    {
        _curve->setPen(_curve->pen().color(), selectedCurvePenSize);
        _clicked = true;
        emit clicked(this);
    }
    else
    {
        _curve->setPen(_curve->pen().color(), unselectedCurvePenSize);
        _clicked = false;
    }
    update();
}

void LegendLabel::paintEvent(QPaintEvent *const event)
{
    QPainter painter(this);
    static int width = size().width();
    static int height = size().height();
    painter.fillRect(0, 0, 7, height, _curve->pen().color());
    if (_clicked)
        painter.fillRect(7, 0, width, height, QColor("#D0D3D4"));
    else
        painter.fillRect(7, 0, width, height, QColor("white"));
    painter.drawText(10, 15, _curve->title().text());
}
