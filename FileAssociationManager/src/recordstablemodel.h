#pragma once

#include "filedatahelpers.h"
#include "record.h"

#include <QAbstractTableModel>

/*! The model class that organizes and brings to GUI life all the data we want to show. */
class RecordsTableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit RecordsTableModel(QObject *parent = nullptr);

    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::CheckStateRole) override;

    Qt::ItemFlags flags(const QModelIndex &index) const override;

    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const override;

    void initData();
    const std::vector<Record> &getData() const;
    void resetData(std::vector<Record> newData);

private:
    std::vector<Record> _data;
    QStringList _header;
    static inline const QStringList _columnNames = { "Status", "Icon", "Extension",
                                                     "Default Application", "Full Path" };
};
