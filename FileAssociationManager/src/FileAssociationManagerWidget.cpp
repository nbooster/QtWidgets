#include "fileassociationmanagerwidget.h"
#include "csv_parser/csvdocument.h"
#include "filedatahelpers.h"
#include "recordstableview.h"

#include <QFileDialog>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QSettings>
#include <QTableView>

/*! Main widget Constructor */
FileAssociationManagerWidget::FileAssociationManagerWidget()
{
    initData();
    initUi();
}

/*! Creates the main GUI elements (title, header & tableview).*/
void FileAssociationManagerWidget::initUi()
{
    setWindowTitle(QStringLiteral("File Association Manager"));

    auto layout = new QVBoxLayout;
    layout->setAlignment(Qt::AlignCenter);

    {
        auto headerLabel = new QLabel;
        headerLabel->setAlignment(Qt::AlignHCenter);
        headerLabel->setText(QStringLiteral("<h1>File Association Manager</h1>"));
        headerLabel->setTextFormat(Qt::TextFormat(1));
        layout->addWidget(headerLabel);
    }

    auto tablesLayout = new QHBoxLayout;
    tablesLayout->setAlignment(Qt::AlignCenter);

    {
        auto table = new RecordsTableView(_tableModel.get());
        tablesLayout->addWidget(table);
    }

    layout->addLayout(tablesLayout);
    setLayout(layout);
}

/*! Initializes the model data. */
void FileAssociationManagerWidget::initData()
{
    _tableModel = std::make_unique<RecordsTableModel>();
    _tableModel->initData();
}

/*! Pops up a window for selecting a file in the system, and returns its path. */
QString FileAssociationManagerWidget::getFilePathDialog()
{
    QFileDialog fileDialog;
    fileDialog.setFileMode(QFileDialog::ExistingFile);
    fileDialog.setNameFilter("All Files (*) ;; JSON (*.json) ;; CSV (*.csv)");
    fileDialog.setWindowModality(Qt::WindowModal);
    fileDialog.setDirectory(QDir::homePath());
    if (fileDialog.exec())
    {
        QStringList fileNames = fileDialog.selectedFiles();
        if (fileNames.size() == 1)
            return fileNames[0];
    }
    return QString("");
}

/*! Loads data from a JSON file to the model data and updates the GUI. */
void FileAssociationManagerWidget::loadDataFromJsonFile()
{
    bool error = false;
    QByteArray bytes = readDataFromFile(getFilePathDialog(), error);
    if (error)
    {
        qWarning("FILE ERROR: File could not be read.");
        return;
    }
    std::vector<Record> data = parseFromJsonData(bytes, error);
    if (error)
    {
        qWarning("PARSING ERROR: JSON file format is broken.");
        return;
    }
    _tableModel->resetData(std::move(data));
}

/*! Saves the model data to a JSON file. */
void FileAssociationManagerWidget::saveDataToJsonFile()
{
    if (!writeDataToFile(parseToJsonData(_tableModel->getData()),
                         QFileDialog::getSaveFileName(this, tr("Save File"), "data.json",
                                                      tr("JSON (*.json) ;; All Files (*)"))))
        qWarning("FILE ERROR: File could not be saved.");
}

/*! Loads data from a CSV file to the model data and updates the GUI. */
void FileAssociationManagerWidget::loadDataFromCSVFile()
{
    bool error = false;
    QtCSV::CsvDocument csv = QtCSV::fromFile(getFilePathDialog(), &error);
    if (error)
    {
        qWarning("FILE ERROR: File could not be read.");
        return;
    }
    std::vector<Record> data = parseFromCSVData(csv.getData(), error);
    if (error)
    {
        qWarning("PARSING ERROR: CSV file format is broken.");
        return;
    }
    _tableModel->resetData(std::move(data));
}

/*! Saves the model data to a CSV file. */
void FileAssociationManagerWidget::saveDataToCSVFile()
{
    bool error = false;
    QtCSV::CsvDocument csv = QtCSV::fromByteArray(parseToCSVData(_tableModel->getData()), &error);
    if (error
        || !toFile(csv, QFileDialog::getSaveFileName(this, tr("Save File"), "data.csv",
                                                     tr("CSV (*.csv) ;; All Files (*)"))))
        qDebug("FILE ERROR: File could not be saved.");
}

/*! Saves the model data to the Windows Registry. */
void FileAssociationManagerWidget::saveDataToWin64Registry()
{
    QSettings settings(QSettings::UserScope);
    settings.setDefaultFormat(QSettings::Registry64Format);
    const std::vector<Record> &data = _tableModel->getData();
    settings.beginWriteArray("Records", data.size());
    for (int i = 0; i < data.size(); ++i)
    {
        settings.setArrayIndex(i);
        settings.setValue("checked", data[i].checked);
        settings.setValue("iconFileName", data[i].iconFileName);
        settings.setValue("extension", data[i].extension);
        settings.setValue("appName", data[i].appName);
        settings.setValue("fullExePath", data[i].fullExePath);
    }
    settings.endArray();
}
