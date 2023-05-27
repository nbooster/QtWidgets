#include "recordstableview.h"

#include <QHeaderView>

/*! Creates our custom tableview from a model. */
RecordsTableView::RecordsTableView(QAbstractItemModel *tableModel) : QTableView()
{
    setModel(tableModel);
    this->verticalHeader()->hide();
    setStyleSheet(tableStyleSheet);
    resizeColumnsToContents();
    resizeRowsToContents();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    auto tableFont = font();
    tableFont.setBold(true);
    tableFont.setPointSize(fontSize);
    setFont(tableFont);
    setIconSize(QSize(64, 64));
}
