#include "TableModel.h"
#include "Contstants.h"

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
    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
                   ? m_hash[index]
                   : QVariant();
}

QVariant TableModel::getVal(const Property& var,const int column) const
{
    QVariant res;
    switch(TypeColumn(column))
    {
    case COL_NAME:
        res = var.getName(); break;
    case COL_VALUE:
        res = var.getCurVal(); break;
    }
    return res;
}

bool TableModel::setData(const QVector<QPair<QString, QVariant> > prop)
{
    for(int row = 0; row < NumOfProp; ++row)
    {
        for(int column = 0; column < NumOfColumn; ++column)
        {
            QModelIndex index = this->index(row, column);
            if(TypeColumn(column) == COL_NAME)
            {
                this->setData(index, QVariant(prop[row].first), Qt::EditRole);
            }
            else if(TypeColumn(column) == COL_VALUE)
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
