#include "Property.h"

Property::Property(const QString name, const QString defVal, const QStringList variants,
                   const TypeOfWidget flag, const PropertyGroup group, const bool danger,
                   const bool importance, const bool active, const bool isText) : m_name(name),
                   m_defVal(defVal), m_variants(variants), m_type(flag), m_group(group),
                   m_isDanger(danger), m_isImp(importance), m_isActive(active), m_isText(isText)
{
    m_curVal = m_defVal;
}

Property::Property()
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

QString Property::getCurVal() const
{
    return m_curVal;
}

QStringList Property::getVariants() const
{
    return m_variants;
}

Property::TypeOfWidget Property::getTypeWidget() const
{
    return m_type;
}

Property::PropertyGroup Property::getGroup() const
{
    return m_group;
}

bool Property::isDanger() const
{
    return m_isDanger;
}

bool Property::isActive() const
{
    return m_isActive;
}

bool Property::isImportant() const
{
    return m_isImp;
}

bool Property::isText() const
{
    return m_isText;
}



void Property::setName(const QString& name)
{
    m_name = name;
}

void Property::setDefVal(const QString& defVal)
{
    m_defVal = defVal;
}

void Property::setCurVal(const QString &curVal)
{
    m_curVal = curVal;
}

void Property::setVariants(const QStringList& variants)
{
    m_variants = variants;
}

void Property::setTypeWidget(const TypeOfWidget type)
{
    m_type = type;
}

void Property::setGroup(const PropertyGroup group)
{
    m_group = group;
}

void Property::setIsDanger(bool flag)
{
    m_isDanger = flag;
}

void Property::setIsActive(bool flag)
{
    m_isActive = flag;
}

void Property::setIsImportant(bool flag)
{
    m_isImp = flag;
}

void Property::setIsText(bool flag)
{
    m_isText = flag;
}


