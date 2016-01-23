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
    //QHash<QModelIndex, QVariant> m_hash;

    QVariant getVal(const Property&, const int column) const;

public:
    TableModel(int nRows, int nColumns, QObject* pobj = 0);

    Property data1(const QModelIndex& index, int nRole) const;
    QVariant data(const QModelIndex& index, int nRole) const;
    bool setData(const QModelIndex& index,
                 const QVariant&    value,
                 int                nRole);
    bool setData(const QVector<QPair<QString, QVariant> >);
    int rowCount(const QModelIndex&) const;
    int columnCount(const QModelIndex&) const;
    Qt::ItemFlags flags(const QModelIndex& index) const;

    bool Save(QTextStream& out) const;

};
#endif // TABLEMODEL_H
