#include "GroupQCheckBox.h"

GroupQCheckBox::GroupQCheckBox()
{
    phbx = new QHBoxLayout;
    check.resize(CountOfCheckBox);
    for(auto &x : check)
    {
        x = new QCheckBox;
        phbx->addWidget(x);
    }
    setLayout(phbx);
}
