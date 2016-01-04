#ifndef QCOMBOBOXDELEGATE_H
#define QCOMBOBOXDELEGATE_H

#include <QWidget>
#include <QStyledItemDelegate>

class QComboBoxItemDelegate : public QStyledItemDelegate
{
    Q_OBJECT
private:
    enum
    {
        COL_PROPERTY,
        COL_VALUE
    };
public:
    QComboBoxItemDelegate(QObject *parent);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index);
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index);
    void setEditorData(QWidget *editor, const QModelIndex &index);

};

#endif // QCOMBOBOXDELEGATE_H
