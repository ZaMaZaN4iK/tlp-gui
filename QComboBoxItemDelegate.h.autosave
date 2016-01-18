#ifndef QCOMBOBOXDELEGATE_H
#define QCOMBOBOXDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

class QComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    QComboBoxItemDelegate(QObject *parent);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;

};

#endif // QCOMBOBOXDELEGATE_H
