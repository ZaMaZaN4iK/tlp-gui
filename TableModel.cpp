#include "TableModel.h"

TableModel::TableModel(int nRows, int nColumns, QObject* pobj)
    : QAbstractTableModel(pobj)
    , m_nRows(nRows)
    , m_nColumns(nColumns)
{
//    Property(const QString name, const QString defVal, const QStringList variants,
//             const TypeOfWidget flag, const PropertyGroup group = OTHER, const bool danger = false);
    //m_prop << Property()
}

QVariant TableModel::data(const QModelIndex& index, int nRole) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    QString str = QString("%1,%2").arg(index.row() + 1).arg(index.column() + 1);
//    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
//           ? m_hash.value(index, QVariant(str))
//           : QVariant();
    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
                       ? m_hash[index]
                       : QVariant();
}

bool TableModel::setData(const QVector<QPair<QString, QVariant> > prop)
{
//    QModelIndex index = model2.index(row, column);
//    int value = (row+1) * (column+1);
//    model2.setData(index, QVariant(value), Qt::EditRole);
    for(int row = 0; row < prop.size(); ++row)
    {
        for(int column = 0; column < 2; ++column)
        {
            QModelIndex index = this->index(row, column);
            if(column == 0)
            {
                this->setData(index, QVariant(prop[row].first), Qt::EditRole);
            }
            else
            {
                this->setData(index, QVariant(prop[row].second), Qt::EditRole);
            }
            emit dataChanged(index, index);
        }
    }
    return true;
}

bool TableModel::setData(const QModelIndex& index,
             const QVariant&    value,
             int                nRole
            )
{
    if (index.isValid() && nRole == Qt::EditRole)
    {
        m_hash[index] = value;
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int TableModel::rowCount(const QModelIndex&) const
{
    return m_nRows;
}

int TableModel::columnCount(const QModelIndex&) const
{
    return m_nColumns;
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable)
                           : flags;
}
