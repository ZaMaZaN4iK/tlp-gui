#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>
#include <QObject>

class Property
{
private:
    enum TypeOfWidget{QLineEdit, QCheckBox, QComboBox};
    enum PropertyGroup{MAIN, CPU, DISK, THINKPAD, RADIO, RADEON, USB, PCI, OTHER};
    QString m_name, m_defVal;
    QStringList m_variants;
    TypeOfWidget m_type;
    PropertyGroup m_group;
    bool m_isDanger;
public:
    Property(const QString name, const QString defVal, const QStringList variants,
             const TypeOfWidget flag, const PropertyGroup group = OTHER, const bool danger = false);

    QString getName() const;
    QString getDefVal() const;
    QStringList getVariants() const;
    TypeOfWidget getTypeWidget() const;
    PropertyGroup getGroup() const;
    bool isDanger() const;

    void setName(const QString& name);
    void setDefVal(const QString& defVal);
    void setVariants(const QStringList& variants);
    void setTypeWidget(const TypeOfWidget type);
    void setGroup(const PropertyGroup group);
    void setIsDanger(bool flag);
};

#endif // PROPERTY_H
