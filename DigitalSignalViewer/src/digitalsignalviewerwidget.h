#pragma once

#include "customqwtplot.h"
#include "legendwidget.h"
#include "scrollareawidget.h"
#include "syncer.h"

#include <QWidget>
#include <qmenu.h>
#include <qscrollarea.h>

#include <qwt_scale_div.h>

class DigitalSignal;
class CustomQwtPlot;
class Syncer;
class ScrollAreaWidget;

/*! The main widget class that holds everything else inside it. */
class DigitalSignalViewerWidget : public QWidget
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(DigitalSignalViewerWidget)

public:
    DigitalSignalViewerWidget();
    ~DigitalSignalViewerWidget() = default;
    QString nextColor();

private:
    void initWidget();
    void createNewPlot(const DigitalSignal &);
    void loadFromFile();
    void saveToFile(CustomQwtPlot *const);
    QString getFilePathDialog();
    DigitalSignal readSignalFromTextFile(const QString filePath, bool &error);

private slots:
    void hoverMenu();

private:
    size_t _plots = 0;
    QMenuBar *_menuBar = nullptr;
    QMenu *_menu = nullptr;
    QMenu *_exportFileMenu = nullptr;
    ScrollAreaWidget *_scrollAreaWidget = nullptr;
    LegendWidget *_legendWidget = nullptr;
    QList<double> _plotsTicks;
    QList<double> _allTicks;
    Syncer *_syncer = nullptr;
    const QStringList _colors = { "lime", "magenta", "orange", "cyan", "red", "yellow" };
};
