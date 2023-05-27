#pragma once

#include "recordstablemodel.h"

#include <QWidget>

class QStandardItemModel;
struct Record;

/*! The main widget class that holds everything else inside it. */
class FileAssociationManagerWidget : public QWidget
{
private:
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(FileAssociationManagerWidget)

public:
    FileAssociationManagerWidget();
    ~FileAssociationManagerWidget() = default;

private:
    void initUi();
    void initData();
    QString getFilePathDialog();
    void loadDataFromJsonFile();
    void saveDataToJsonFile();
    void loadDataFromCSVFile();
    void saveDataToCSVFile();
    void saveDataToWin64Registry();
    void getFileAssociations();

private:
    std::unique_ptr<RecordsTableModel> _tableModel = nullptr;
};
