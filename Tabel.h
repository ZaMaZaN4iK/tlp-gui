#ifndef TABEL_H
#define TABEL_H

#include "TableModel.h"
#include "QComboBoxItemDelegate.h"

class Tabel
{
private:
    TableModel* p_table;
    QComboBoxItemDelegate* delegate;
public:
    Tabel();
};

#endif // TABEL_H
