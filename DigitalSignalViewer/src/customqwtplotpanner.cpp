#include "customqwtplotpanner.h"

#include <qcoreevent.h>
#include <qevent.h>

#include <qwt_scale_div.h>

CustomQwtPlotPanner::CustomQwtPlotPanner(QWidget *canvas) : QwtPlotPanner(canvas)
{
    setOrientations(Qt::Horizontal);
}

bool CustomQwtPlotPanner::eventFilter(QObject *const object, QEvent *const event)
{
    if (object == nullptr || object != parentWidget())
        return false;
    switch (event->type())
    {
    case QEvent::MouseButtonPress:
    {
        widgetMousePressEvent(static_cast<QMouseEvent *>(event));
        break;
    }
    case QEvent::MouseMove:
    {
        QMouseEvent *evr = static_cast<QMouseEvent *>(event);
        widgetMouseMoveEvent(evr);
        widgetMouseReleaseEvent(evr);
        setMouseButton(evr->button(), evr->modifiers());
        widgetMousePressEvent(evr);
        break;
    }
    case QEvent::MouseButtonRelease:
    {
        widgetMouseReleaseEvent(static_cast<QMouseEvent *>(event));
        grab();
        break;
    }
    case QEvent::KeyPress:
    {
        widgetKeyPressEvent(static_cast<QKeyEvent *>(event));
        break;
    }
    case QEvent::KeyRelease:
    {
        widgetKeyReleaseEvent(static_cast<QKeyEvent *>(event));
        break;
    }
    case QEvent::Paint:
    {
        if (isVisible())
            return true;
        break;
    }
    default:
        break;
    }
    return false;
}
