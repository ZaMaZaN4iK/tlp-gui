#include "GroupQCheckBox.h"

GroupQCheckBox::GroupQCheckBox()
{
    widg = new QWidget;
    phbx = new QHBoxLayout;
    check.resize(CountOfCheckBox);
    for(auto &x : check)
    {
        x = new QCheckBox;
        phbx->addWidget(x);
    }
    widg->setLayout(phbx);
}
