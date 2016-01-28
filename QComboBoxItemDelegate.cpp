#include <QComboBox>
#include <QtGui>
#include <QCheckBox>
#include "QComboBoxItemDelegate.h"
#include "Contstants.h"
#include "TableModel.h"
#include "GroupQCheckBox.h"

QComboBoxItemDelegate::QComboBoxItemDelegate(QObject* parent) : QStyledItemDelegate(parent)
{
}

QWidget* QComboBoxItemDelegate::createEditor(QWidget *parent,
                            const QStyleOptionViewItem &option,
                            const QModelIndex &index) const
{
    if (index.column() == COL_VALUE)
    {
        const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
        if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QComboBox)
        {
            QStringList values = ptr->data1(index,Qt::EditRole).getVariants();
            QComboBox* comboBox = new QComboBox(parent);
            comboBox->addItems(values);
            comboBox->setCurrentIndex(1);
            return comboBox;
        }
        else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
        {
            QCheckBox* checkbox = new QCheckBox(parent);
            checkbox->setChecked(ptr->data1(index, Qt::EditRole).isActive());
            return checkbox;
        }
        else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::GroupQCheckBox)
        {
            GroupQCheckBox* groupBox = new GroupQCheckBox(parent);
            QString str = ptr->data1(index, Qt::EditRole).getCurVal();

            if(str.indexOf("bluetooth") != -1)  groupBox->setValue(GroupQCheckBox::BLUETOOTH, true);
            if(str.indexOf("wifi") != -1)  groupBox->setValue(GroupQCheckBox::WIFI, true);
            if(str.indexOf("wwan") != -1)  groupBox->setValue(GroupQCheckBox::WWAN, true);

            return groupBox;
        }
        else
        {
            QLineEdit* line = new QLineEdit(parent);
            line->setText(ptr->data1(index, Qt::EditRole).getDefVal());
            if(ptr->data1(index, Qt::EditRole).getValidator().type == "Digit")
            {
                Property::AboutValidator temp = ptr->data1(index, Qt::EditRole).getValidator();
                line->setValidator(new QIntValidator(temp.min, temp.max, parent));
            }
            else if(ptr->data1(index, Qt::EditRole).getValidator().type == "other")
            {
                line->setValidator(new QIntValidator(0, (1 << 29), parent));
            }
            else if(ptr->data1(index, Qt::EditRole).getValidator().type == "string")
            {
                //line->setValidator();
            }
            return line;
        }
    }
    else if(index.column() == COL_ACTIVE)
    {
        const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
        QCheckBox* checkbox = new QCheckBox(parent);
        checkbox->setChecked(ptr->data1(index, Qt::EditRole).isActive());
        return checkbox;
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
        const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
        if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QComboBox)
        {
            QComboBox* combobox = qobject_cast<QComboBox*>(editor);
            QString value = combobox->currentText();
            model->setData(index, value, Qt::EditRole);
        }
        else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
        {
            QCheckBox* checkbox = qobject_cast<QCheckBox*>(editor);
            model->setData(index, checkbox->isChecked(), Qt::EditRole);
        }
        else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::GroupQCheckBox)
        {
            qDebug() << "Group to model\n";
            GroupQCheckBox* groupBox = qobject_cast<GroupQCheckBox*>(editor);
            QString str;
            if(groupBox->getValue(GroupQCheckBox::BLUETOOTH))    str += "bluetooth ";
            if(groupBox->getValue(GroupQCheckBox::WIFI))    str += "wifi ";
            if(groupBox->getValue(GroupQCheckBox::WWAN))    str += "wwan ";
            model->setData(index, str, Qt::EditRole);
        }
        else
        {
            QLineEdit* line = qobject_cast<QLineEdit*>(editor);
            model->setData(index, line->text(), Qt::EditRole);
        }
    }
    else if(index.column() == COL_ACTIVE)
    {
        const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
        if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
        {
            QCheckBox* checkbox = qobject_cast<QCheckBox*>(editor);
            model->setData(index, checkbox->isChecked(), Qt::EditRole);
        }

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
            const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
            if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QComboBox)
            {
                QComboBox* combobox = qobject_cast<QComboBox*>(editor);
                combobox->setCurrentText(ptr->data(index, Qt::EditRole).toString());
            }
            else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
            {
                QCheckBox* checkbox = qobject_cast<QCheckBox*>(editor);
                checkbox->setChecked(ptr->data1(index, Qt::EditRole).isActive());
            }
            else if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::GroupQCheckBox)
            {
                GroupQCheckBox* groupBox = qobject_cast<GroupQCheckBox*>(editor);
                QString str = ptr->data1(index, Qt::EditRole).getCurVal();

                if(str.indexOf("bluetooth") != -1)  groupBox->setValue(GroupQCheckBox::BLUETOOTH, true);
                if(str.indexOf("wifi") != -1)  groupBox->setValue(GroupQCheckBox::WIFI, true);
                if(str.indexOf("wwan") != -1)  groupBox->setValue(GroupQCheckBox::WWAN, true);
            }
            else
            {
                QLineEdit* line = qobject_cast<QLineEdit*>(editor);
                line->setText(ptr->data1(index, Qt::EditRole).getCurVal());
            }
        }
        else if(index.column() == COL_ACTIVE)
        {
            const TableModel* ptr = qobject_cast<const TableModel*>(index.model());
            if(ptr->data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
            {
                QCheckBox* checkbox = qobject_cast<QCheckBox*>(editor);
                checkbox->setChecked(ptr->data1(index, Qt::EditRole).isActive());
            }
        }
        else
        {
            QStyledItemDelegate::setEditorData(editor, index);
        }
}
