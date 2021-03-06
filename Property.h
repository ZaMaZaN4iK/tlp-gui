#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>
#include <QObject>
#include <QIntValidator>
#include "Contstants.h"

class Property
{
public :
    enum TypeOfWidget{QLineEdit, QCheckBox, QComboBox, GroupQCheckBox};
    enum PropertyGroup{MAIN, CPU, DISK, THINKPAD, RADIO, RADEON, USB, PCI, OTHER};
    struct AboutValidator
    {
        QString type;
        int min, max;
        AboutValidator(const char* str = "other", int t_min = 0, int t_max = (1 << 29)) : type(str), min(t_min), max(t_max){}
    };
private:
    QString m_name, m_comment;
    QString m_defVal, m_curVal;
    QStringList m_variants;
    TypeOfWidget m_type;
    PropertyGroup m_group;
    bool m_isDanger, m_isImp, m_isActive, m_isText;



    AboutValidator val;

public:
    Property();
    Property(const QString name, const QString defVal, const QStringList variants, const QString comment,
             const TypeOfWidget flag, const PropertyGroup group = OTHER,
             const bool danger = false, const bool importance = false, const bool active = true,
             const bool isText = false, const AboutValidator valid = AboutValidator());

    QString getName() const;
    QString getDefVal() const;
    QString getCurVal() const;
    QString getComment() const;
    AboutValidator getValidator() const;
    QStringList getVariants() const;
    TypeOfWidget getTypeWidget() const;
    PropertyGroup getGroup() const;
    bool isDanger() const;
    bool isImportant() const;
    bool isActive() const;
    bool isText() const;

    void setName(const QString& name);
    void setDefVal(const QString& defVal);
    void setCurVal(const QString& curVal);
    void setVariants(const QStringList& variants);
    void setTypeWidget(const TypeOfWidget type);
    void setGroup(const PropertyGroup group);
    void setIsDanger(bool flag);
    void setIsActive(bool flag);
    void setIsImportant(bool flag);
    void setIsText(bool flag);
};

#endif // PROPERTY_H
