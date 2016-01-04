#ifndef PROPERTY_H
#define PROPERTY_H

#include <QString>
#include <QObject>

class Property
{
private:
    QString m_name, m_defVal;
    QStringList m_variants;
    bool m_isImp;
public:
    Property(const QString name, const QString defVal, const QStringList variants,
             const bool isImp = false);
    Property(const Property&val);

    QString getName() const;
    QString getDefVal() const;
    QStringList getVariants() const;
    bool isImportant() const;

    void setName(const QString& name);
    void setDefVal(const QString& defVal);
    void setVariants(const QStringList& variants);
    void setIsImportant(bool flag);
};

#endif // PROPERTY_H
