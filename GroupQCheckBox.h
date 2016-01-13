#ifndef GROUPQCHECKBOX_H
#define GROUPQCHECKBOX_H

#include <QWidget>
#include <QCheckBox>
#include <QVector>
#include <QHBoxLayout>

class GroupQCheckBox : public QWidget
{
    Q_OBJECT
private:
    const int CountOfCheckBox = 3;

    QWidget* widg;
    QHBoxLayout* phbx;
    QVector<QCheckBox*> check;
public:
    GroupQCheckBox();

    QWidget* widget(int ind) const;

    void setWidget(QWidget*, int ind);
};

#endif // GROUPQCHECKBOX_H
