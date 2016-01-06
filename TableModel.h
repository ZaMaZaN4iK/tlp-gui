#ifndef TABLEMODEL_H
#define TABLEMODEL_H


#include <QtWidgets>
#include "Property.h"


class TableModel : public QAbstractTableModel
{
    Q_OBJECT
private:
    int m_nRows, m_nColumns;
    QVector<Property> m_prop;
    QHash<QModelIndex, QVariant> m_hash;

public:
    TableModel(int nRows, int nColumns, QObject* pobj = 0);

    QVariant data(const QModelIndex& index, int nRole) const;
    bool setData(const QModelIndex& index,
                 const QVariant&    value,
                 int                nRole);

    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

};
#endif // TABLEMODEL_H
