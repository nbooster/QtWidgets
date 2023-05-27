#pragma once

#include <QTableView>

/*! The view class that decorates our table model.  */
class RecordsTableView : public QTableView
{
    Q_OBJECT
public:
    RecordsTableView(QAbstractItemModel *tableModel);
    static constexpr size_t fontSize = 12;
    const QString tableStyleSheet = QStringLiteral(
        "QHeaderView::section { background-color: lightgrey; font: bold; font-size: 15px }");
};
