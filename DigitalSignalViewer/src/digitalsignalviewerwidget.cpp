#include "digitalsignalviewerwidget.h"
#include "customqwtscaledraw.h"
#include "scrollareawidget.h"

#include <QFileDialog>
#include <QMenuBar>
#include <QVBoxLayout>
#include <qscrollarea.h>
#include <qwt_scale_widget.h>

#include <qwt_plot_curve.h>

#include <fstream>

DigitalSignalViewerWidget::DigitalSignalViewerWidget()
{
    initWidget();
    resize(1000, 300);
}

/*! Initializes the widget. */
void DigitalSignalViewerWidget::initWidget()
{
    setWindowTitle(QStringLiteral("Digital Signal Viewer"));

    auto layout = new QHBoxLayout;

    _menuBar = new QMenuBar();
    _menuBar->setFont({ "Times", 13 });
    _menuBar->setStyleSheet("QMenuBar::item:selected{background-color: rgb(0,172,230)}");
    connect(_menuBar, &QMenuBar::hovered, this, &DigitalSignalViewerWidget::hoverMenu);
    {
        _menu = new QMenu("File");
        _menu->setFont({ "Times", 12 });
        _menu->setStyleSheet(
            "QMenu::item:selected{"
            "background-color: rgb(0,172,230); "
            "border-left:5px solid rgb(0,230,57);"
            "font-size: 18px;"
            "font: bold;"
            "color: rgb(255,255,255);}");
        {
            auto importFileAction = new QAction("Import Signal From File");
            connect(importFileAction, &QAction::triggered, this,
                    &DigitalSignalViewerWidget::loadFromFile);
            _menu->addAction(importFileAction);

            _exportFileMenu = new QMenu("Export Signal To File");
            _exportFileMenu->setFont({ "Times", 12 });
            _menu->addMenu(_exportFileMenu);
        }
        _menuBar->addMenu(_menu);
    }

    layout->setAlignment(Qt::AlignTop);
    layout->setMenuBar(_menuBar);
    layout->setContentsMargins(0, 0, 0, 0);

    auto scrollArea = new QScrollArea;
    scrollArea->setWidgetResizable(true);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    _scrollAreaWidget = new ScrollAreaWidget(this);
    scrollArea->setWidget(_scrollAreaWidget);
    layout->addWidget(scrollArea);

    _legendWidget = new LegendWidget(this);
    layout->addWidget(_legendWidget);

    setLayout(layout);

    auto xaxisdiv = QwtScaleDiv(QwtPlot::xBottom);
    xaxisdiv.setTicks(QwtScaleDiv::MajorTick, {});
    xaxisdiv.setTicks(QwtScaleDiv::MediumTick, {});
    xaxisdiv.setTicks(QwtScaleDiv::MinorTick, {});

    auto draw = new CustomQwtScaleDraw(xaxisdiv, xAxisRebaseStep);

    auto scale = new QwtScaleWidget(QwtScaleDraw::BottomScale);
    scale->setScaleDraw(draw);
    _scrollAreaWidget->addScale(scale);

    _syncer = new Syncer();
}

/*! Creates a new CustomQwtPlot and inserts it in the widget. */
void DigitalSignalViewerWidget::createNewPlot(const DigitalSignal &signal)
{
    const auto name = std::string("Signal ") + std::to_string(_plots + 1);

    auto plot = new CustomQwtPlot(QwtText(name.c_str()), signal, &_plotsTicks, &_allTicks, this);
    plot->setMinimumHeight(100);
    _plots += 1;

    _legendWidget->addCurve(static_cast<QwtPlotCurve *>(plot->itemList()[0])); // plot curve
    _scrollAreaWidget->addWidget(plot);
    _syncer->addPlot(plot);

    auto exportFileAction = new QAction(name.c_str(), plot);
    connect(exportFileAction, &QAction::triggered, this,
            [this, plot]() { return saveToFile(plot); });
    _exportFileMenu->addAction(exportFileAction);

    auto xaxisdiv = plot->axisScaleDiv(QwtPlot::xBottom);
    emit plot->updateMinMax(xaxisdiv.lowerBound(), xaxisdiv.upperBound());
    emit plot->updatePrevBounds(xaxisdiv.lowerBound(), xaxisdiv.upperBound());
    emit plot->updateAxisDiv(xaxisdiv);
}

/*! Hover Effect Slot */
void DigitalSignalViewerWidget::hoverMenu()
{
    _menu->exec(mapToGlobal(_menuBar->pos()) + QPoint(0, 25));
}

QString DigitalSignalViewerWidget::nextColor()
{
    static int i = 0;
    return _colors[i++ % _colors.size()];
}

/*! Saves the signal (1 curve) data from the plot a TXT file. */
void DigitalSignalViewerWidget::saveToFile(CustomQwtPlot *const plot)
{
    QString result;
    auto curve = static_cast<QwtPlotCurve *>(plot->itemList()[0]);
    auto data = curve->data();
    for (size_t index = 0; index < data->size(); ++index)
    {
        auto point = data->sample(index);
        result += QString::fromStdString(std::to_string(std::lround(point.x()))) + QString(" ")
                  + QString::fromStdString(std::to_string(std::lround(point.y()))) + QString("\n");
    }
    const auto path = QFileDialog::getSaveFileName(this, QStringLiteral("Save File"),
                                                   QStringLiteral("%1.txt").arg(
                                                       curve->title().text()),
                                                   QStringLiteral("TXT (*.txt) ;; All Files (*)"));
    QFile file(path);
    if (file.open(QIODevice::WriteOnly))
    {
        QTextStream out(&file);
        out << result;
        file.close();
    }
}

/*! Loads signal from a file.
 */
void DigitalSignalViewerWidget::loadFromFile()
{
    bool error = false;
    DigitalSignal signal = readSignalFromTextFile(getFilePathDialog(), error);
    if (error)
        return;
    createNewPlot(signal);
}

/*! Pops up a window for selecting a file in the system, and returns its path.
 */
QString DigitalSignalViewerWidget::getFilePathDialog()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter(QStringLiteral("All Files (*) ;; TXT (*.txt)"));
    fileDialog.setWindowModality(Qt::WindowModal);
    fileDialog.setDirectory(QDir::homePath());
    if (fileDialog.exec())
    {
        QStringList fileNames = fileDialog.selectedFiles();
        if (fileNames.size() == 1)
            return fileNames[0];
    }
    return {};
}

/*! Reads one signal data from a text file. */
DigitalSignal DigitalSignalViewerWidget::readSignalFromTextFile(const QString filePath, bool &error)
{
    std::vector<std::pair<int, bool>> data;
    std::ifstream file(filePath.toStdString().c_str());
    if (!file.is_open())
    {
        error = true;
        return DigitalSignal(data);
    }
    error = false;
    std::string line;
    while (getline(file, line))
    {
        if (line.size() == 0)
            continue;
        QString dataLine(line.c_str());
        QStringList dataCols = dataLine.split(' ', Qt::SkipEmptyParts);
        if (dataCols.size() != 2)
        {
            error = true;
            break;
        }
        data.emplace_back(std::make_pair(dataCols[0].toInt(), dataCols[1].toInt()));
    }
    return DigitalSignal(data);
}
