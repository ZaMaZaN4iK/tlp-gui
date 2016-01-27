#ifndef GROUPQCHECKBOX_H
#define GROUPQCHECKBOX_H

#include <QWidget>
#include <QCheckBox>
#include <QVector>
#include <QHBoxLayout>
#include <QString>
#include <QEvent>
#include <QObject>
#include <QApplication>
#include <QFocusEvent>

class GroupQCheckBox : public QWidget
{
    Q_OBJECT
private:
    static const int CountOfCheckBox = 3;
    QVector<QCheckBox*> check;
    static const QVector<QString> name;
public:
    enum TypeCheckBox{BLUETOOTH, WIFI, WWAN};

    GroupQCheckBox(QWidget* parent);
    bool getValue(TypeCheckBox value) const;
    unsigned int getValues() const;
    void setValue(TypeCheckBox value, bool key);
    void setValues(unsigned int mask);

    //FIXME : Fix Event bug
    bool eventFilter( QObject* o, QEvent* e )
    {
        if( (o == check[0] || o == check[1] || o == check[2]) && e->type() == QEvent::FocusOut )
        {
            QFocusEvent* fe = static_cast< QFocusEvent* >( e );
            QApplication::sendEvent( this, fe );
        }
        return QWidget::eventFilter( o, e );
    }
};

#endif // GROUPQCHECKBOX_H
