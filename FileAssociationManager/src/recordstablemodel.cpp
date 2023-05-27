#include "recordstablemodel.h"

RecordsTableModel::RecordsTableModel(QObject *parent) : QAbstractTableModel(parent) {}

QVariant RecordsTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole && !_columnNames.empty())
        return _columnNames.at(section);
    return QVariant();
}

int RecordsTableModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _data.size();
}

int RecordsTableModel::columnCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _columnNames.size();
}

QVariant RecordsTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return {};
    switch (role)
    {
    case Qt::DisplayRole:
        if (index.column() == 2)
            return _data[index.row()].extension;
        if (index.column() == 3)
            return _data[index.row()].appName;
        if (index.column() == 4)
            return _data[index.row()].fullExePath;
        break;
    case Qt::CheckStateRole:
        if (index.column() == 0)
            return _data[index.row()].checked ? Qt::Checked : Qt::Unchecked;
        break;
    case Qt::DecorationRole:
        if (index.column() == 1)
            return _data[index.row()].icon;
        break;
    }
    return {};
}

bool RecordsTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (data(index, role) == value)
        return false;
    if (role == Qt::CheckStateRole)
    {
        if (index.column() != 0 || !value.canConvert(QMetaType::Bool))
            return false;
        _data[index.row()].checked = value.toBool();
        emit dataChanged(index, index, { role });
        return true;
    }
    return false;
}

Qt::ItemFlags RecordsTableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;
    if (index.column() == 0)
        return QAbstractItemModel::flags(index); // | Qt::ItemIsUserCheckable;
    return QAbstractItemModel::flags(index);
}

QModelIndex RecordsTableModel::index(int row, int column, const QModelIndex &parent) const
{
    if (row < 0 || column < 0 || row >= _data.size() || column >= _columnNames.size())
        return QModelIndex();
    return createIndex(row, column);
}

/*! Initializes our table model with the necessary data. */
void RecordsTableModel::initData()
{
    // const QString iconFileName = QStringLiteral("generic-icon.png");
    const QStringList extensions = { ".aap", ".can", ".ffpga", ".gp3", ".gp4",
                                     ".gp5", ".gp6", ".hvp",   ".ldo", ".ppak" };
    _data.reserve(extensions.size());
    for (int i = 0; i < extensions.size(); ++i)
    {
        QString iconFileName = extensions[i].section('.', 1, 1) + ".ico";
        QString appName(getFileTypeProgram(extensions[i].toStdString().c_str(), 4).c_str());
        QString fullExePath(getFileTypeProgram(extensions[i].toStdString().c_str(), 2).c_str());
        _data.emplace_back(false, extensions[i], iconFileName, appName, fullExePath);
    }
}

const std::vector<Record> &RecordsTableModel::getData() const { return _data; }

/*! Updates the data in the table model and signals the GUI for that. */
void RecordsTableModel::resetData(std::vector<Record> newData)
{
    beginResetModel();
    _data = std::move(newData);
    endResetModel();
}
