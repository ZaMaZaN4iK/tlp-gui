#include "GroupQCheckBox.h"
#include <QLabel>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QDebug>

const QVector<QString> GroupQCheckBox::name = {"Bluetooth", "Wi-Fi", "Wwan"};

GroupQCheckBox::GroupQCheckBox(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* mainLayout = new QHBoxLayout(parent);
    check.resize(CountOfCheckBox);
    for(int i = 0; i < CountOfCheckBox; ++i)
    {
        check[i] = new QCheckBox(name[i], parent);
        mainLayout->addWidget(check[i]);
        setFocusProxy(check[i]);
        check[i]->installEventFilter(this);
    }
    setLayout(mainLayout);
}

bool GroupQCheckBox::getValue(TypeCheckBox value) const
{
    return check[value]->isChecked();
}

unsigned int GroupQCheckBox::getValues() const
{
    unsigned int res = 0;
    for(int i = 0; i < CountOfCheckBox; ++i, res <<= 1)
    {
        if(check[i]->isChecked())   res |= 1;
    }
    return res;
}

void GroupQCheckBox::setValue(TypeCheckBox value, bool key)
{
    check[value]->setChecked(key);
}

void GroupQCheckBox::setValues(unsigned int mask)
{
    for(int i = 0; i < CountOfCheckBox; ++i, mask >>= 1)
    {
        check[i]->setChecked(mask & 1 ? true : false);
    }
}
