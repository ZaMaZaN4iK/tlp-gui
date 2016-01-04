#include "Property.h"

Property::Property(const QString name, const QString defVal, const QStringList variants,
                   const bool isImp) : m_name(name), m_defVal(defVal), m_variants(variants),
                                             m_isImp(isImp)
{
}



QString Property::getName() const
{
    return m_name;
}

QString Property::getDefVal() const
{
    return m_defVal;
}

QStringList Property::getVariants() const
{
    return m_variants;
}

bool Property::isImportant() const
{
    return m_isImp;
}




void Property::setName(const QString& name)
{
    m_name = name;
}

void Property::setDefVal(const QString& defVal)
{
    m_defVal = defVal;
}

void Property::setVariants(const QStringList& variants)
{
    m_variants = variants;
}

void Property::setIsImportant(bool flag)
{
    m_isImp = flag;
}
