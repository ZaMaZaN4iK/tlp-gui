#include "Property.h"

Property::Property(const QString name, const QString defVal, const QStringList variants,
                   const TypeOfWidget flag, const PropertyGroup group, const bool danger) : m_name(name),
                   m_defVal(defVal), m_variants(variants), m_type(flag), m_group(group),
                                       m_isDanger(danger)
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
