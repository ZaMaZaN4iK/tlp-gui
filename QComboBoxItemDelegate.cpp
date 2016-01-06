#include <QComboBox>
#include "QComboBoxItemDelegate.h"

QComboBoxItemDelegate::QComboBoxItemDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

QWidget* QComboBoxItemDelegate::createEditor(QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    if (index.column() == COL_VALUE)
    {
        QStringList values;
        values << "Enabled" << "Disabled";

        QComboBox* comboBox = new QComboBox(parent);
        comboBox->addItems(values);
        return comboBox;
    }
    else
    {
        return QStyledItemDelegate::createEditor(parent, option, index);
    }
}

void QComboBoxItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                         const QModelIndex &index) const
{
    if(index.column() == COL_VALUE)
    {
        QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
        QString value = comboBox->currentText();
        model->setData(index, value, Qt::EditRole);
    }
    else
    {
        QStyledItemDelegate::setModelData(editor, model, index);
    }
}

void QComboBoxItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    if(index.column() == COL_VALUE)
    {
        QString value = index.model()->data(index, Qt::EditRole).toString();
        //qDebug() << "Value:" << value;
        QComboBox* comboBox = qobject_cast<QComboBox*>(editor);
        comboBox->setCurrentIndex(comboBox->findText(value));
    }
    else
    {
        QStyledItemDelegate::setEditorData(editor, index);
    }
}
