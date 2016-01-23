#include "TableModel.h"
#include "Contstants.h"

TableModel::TableModel(int nRows, int nColumns, QObject* pobj)
    : QAbstractTableModel(pobj)
    , m_nRows(nRows)
    , m_nColumns(nColumns)
{
    m_prop = QVector<Property>({Property("TLP_ENABLE", "1", QStringList(), Property::QCheckBox, Property::MAIN, false, true, true, false),
                                Property("DISK_IDLE_SECS_ON_AC", "0", QStringList(), Property::QLineEdit, Property::DISK, false, true, true, false),
                                Property("MAX_LOST_WORK_SECS_ON_AC", "15", QStringList(), Property::QLineEdit, Property::OTHER, false, true, true, false),
                                Property("CPU_SCALING_GOVERNOR_ON_AC", "ondemand", QStringList() << "ondemand" << "powersave" << "performance" << "conservative", Property::QComboBox, Property::CPU, false, false, false, false),
                                Property("CPU_SCALING_MIN_FREQ_ON_AC", "0", QStringList(), Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_SCALING_MAX_FREQ_ON_AC", "0", QStringList(), Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_MIN_PERF_ON_AC", "0", QStringList(), Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_MAX_PERF_ON_AC", "100", QStringList(), Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_BOOST_ON_AC", "1", QStringList(), Property::QCheckBox, Property::CPU, false, false, false, false),
                                Property("SCHED_POWERSAVE_ON_AC", "0", QStringList(), Property::QCheckBox, Property::CPU, false, false, true, false),
                                Property("NMI_WATCHDOG", "0", QStringList(), Property::QCheckBox, Property::OTHER, true, false, false, false),
                                Property("PHC_CONTROLS", "", QStringList(), Property::QLineEdit, Property::OTHER, true, false, false, true),
                                Property("ENERGY_PERF_POLICY_ON_AC", "performance", QStringList() << "performance" << "normal" << "powersave", Property::QComboBox, Property::OTHER, false, false, false, false),
                                Property("DISK_DEVICES", "sda", QStringList(), Property::QLineEdit, Property::DISK, false, false, true, true),
                                Property("DISK_APM_LEVEL_ON_AC", "254", QStringList(), Property::QLineEdit, Property::DISK, false, false, true, true),
                                Property("DISK_SPINDOWN_TIMEOUT_ON_AC", "0", QStringList(), Property::QLineEdit, Property::DISK, false, false, false, true),
                                Property("DISK_IOSCHED", "cfq", QStringList() << "noop" << "deadline" << "cfq", Property::QComboBox, Property::DISK, false, false, false, true),
                                Property("SATA_LINKPWR_ON_AC", "max_performance", QStringList() << "min_power" << "medium_power" << "max_performance", Property::QComboBox, Property::OTHER, false, true, true, false),
                                Property("PCIE_ASPM_ON_AC", "performance", QStringList() << "default" << "performance" << "powersave", Property::QComboBox, Property::PCI, false, false, true, false),
                                Property("RADEON_POWER_PROFILE_ON_AC", "high", QStringList() << "low" << "mid" << "high" << "auto" << "default", Property::QComboBox, Property::RADEON, false, false, false, false),
                                Property("RADEON_DPM_STATE_ON_AC", "performance", QStringList() << "battery" << "performance", Property::QComboBox, Property::OTHER, false, false, false, false),
                                Property("RADEON_DPM_PERF_LEVEL_ON_AC", "auto", QStringList() << "auto" << "low" << "high", Property::QComboBox, Property::RADEON, false, false, false, false),
                                Property("WIFI_PWR_ON_AC", "1", QStringList(), Property::QLineEdit, Property::RADIO, false, false, true, false),
                                Property("WOL_DISABLE", "Y", QStringList(), Property::QCheckBox, Property::RADIO, false, false, true, false),
                                Property("SOUND_POWER_SAVE_ON_AC", "0", QStringList(), Property::QLineEdit, Property::OTHER, false, false, false, false),
                                Property("SOUND_POWER_SAVE_CONTROLLER", "Y", QStringList(), Property::QCheckBox, Property::OTHER, false, false, true, false),
                                Property("BAY_POWEROFF_ON_BAT", "0", QStringList(), Property::QCheckBox, Property::OTHER, false, false, false, false),
                                Property("BAY_DEVICE", "sr0", QStringList(), Property::QLineEdit, Property::OTHER, false, false, false, true),
                                Property("RUNTIME_PM_ON_AC", "on", QStringList() << "on" << "auto", Property::QComboBox, Property::PCI, false, false, true, false),
                                Property("RUNTIME_PM_ALL", "1", QStringList(), Property::QCheckBox, Property::PCI, false, false, true, false),
                                Property("RUNTIME_PM_BLACKLIST", "", QStringList(), Property::QLineEdit, Property::PCI, false, false, false, true),
                                Property("RUNTIME_PM_DRIVER_BLACKLIST", "radeo", QStringList(), Property::QLineEdit, Property::RADEON, false, false, false, true),
                                Property("USB_AUTOSUSPEND", "0", QStringList(), Property::QCheckBox, Property::USB, false, false, true, false),
                                Property("USB_BLACKLIST", "", QStringList(), Property::QLineEdit, Property::USB, false, false, false, true),
                                Property("USB_BLACKLIST_WWAN", "1", QStringList(), Property::QCheckBox, Property::USB, false, false, true, false),
                                Property("USB_WHITELIST", "", QStringList(), Property::QLineEdit, Property::USB, false, false, false, true),
                                Property("USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN", "1", QStringList(), Property::QCheckBox, Property::USB, false, false, false, false),
                                Property("RESTORE_DEVICE_STATE_ON_STARTUP", "0", QStringList(), Property::QCheckBox, Property::RADIO, false, false, true, false),
                                Property("DEVICES_TO_DISABLE_ON_STARTUP", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_STARTUP", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_SHUTDOWN", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_SHUTDOWN", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_AC", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_BAT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("START_CHARGE_THRESH_BAT0", "75", QStringList(), Property::QLineEdit, Property::THINKPAD, false, false, false, false),
                                Property("STOP_CHARGE_THRESH_BAT0", "80", QStringList(), Property::QLineEdit, Property::THINKPAD, false, false, false, false),
                                Property("START_CHARGE_THRESH_BAT1", "75", QStringList(), Property::QLineEdit, Property::THINKPAD, false, false, false, false),
                                Property("STOP_CHARGE_THRESH_BAT1", "80", QStringList(), Property::QLineEdit, Property::THINKPAD, false, false, false, false),
                                Property("DEVICES_TO_DISABLE_ON_LAN_CONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_WIFI_CONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_WWAN_CONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_LAN_DISCONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_DOCK", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_DOCK", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_UNDOCK", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_UNDOCK", "", QStringList() << "bluetooth" << "wifi" << "wwan", Property::QComboBox, Property::RADIO, false, false, false, true)});
}

Property TableModel::data1(const QModelIndex& index, int nRole) const
{
    if (!index.isValid())
    {
        return Property();
    }
    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
                   ? m_prop[index.row()]
                   : Property();
}

QVariant TableModel::data(const QModelIndex& index, int nRole) const
{
    if (!index.isValid())
    {
        return QVariant();
    }
    return (nRole == Qt::DisplayRole || nRole == Qt::EditRole)
                   ? getVal(m_prop[index.row()], index.column())
                   : QVariant();
}

QVariant TableModel::getVal(const Property& var,const int column) const
{
    QVariant res;
    switch(TypeColumn(column))
    {
    case COL_NAME:
        res = var.getName(); break;
    case COL_VALUE:
        res = var.getCurVal(); break;
    }
    return res;
}

bool TableModel::setData(const QVector<QPair<QString, QVariant> > prop)
{
    for(int row = 0; row < NumOfProp; ++row)
    {
        for(int column = 0; column < NumOfColumn; ++column)
        {
            QModelIndex index = this->index(row, column);
            if(TypeColumn(column) == COL_NAME)
            {
                this->setData(index, QVariant(prop[row].first), Qt::EditRole);
            }
            else if(TypeColumn(column) == COL_VALUE)
            {
                this->setData(index, QVariant(prop[row].second), Qt::EditRole);
            }
            emit dataChanged(index, index);
        }
    }
    return true;
}

bool TableModel::setData(const QModelIndex& index,
                         const QVariant&    value,
                         int                nRole
                        )
{
    if (index.isValid() && nRole == Qt::EditRole)
    {
        if(data1(index, Qt::EditRole).getTypeWidget() == Property::QComboBox)
        {
            m_prop[index.row()].setCurVal(value.toString());
        }
        else if(data1(index, Qt::EditRole).getTypeWidget() == Property::QCheckBox)
        {
            m_prop[index.row()].setIsActive(value.toBool());
        }
        else
        {
            m_prop[index.row()].setCurVal(value.toString());
        }
        emit dataChanged(index, index);
        return true;
    }
    return false;
}

int TableModel::rowCount(const QModelIndex&) const
{
    return m_nRows;
}

int TableModel::columnCount(const QModelIndex&) const
{
    return m_nColumns;
}

Qt::ItemFlags TableModel::flags(const QModelIndex& index) const
{
    Qt::ItemFlags flags = QAbstractTableModel::flags(index);
    return index.isValid() ? (flags | Qt::ItemIsEditable)
                           : flags;
}

bool TableModel::Save(QTextStream & out) const
{
    for(int i = 0; i < m_prop.size(); ++i)
    {
        out << m_prop[i].getName() << "=" << (m_prop[i].isText() ? "\"" : "")
            << m_prop[i].getCurVal() << (m_prop[i].isText() ? "\"" : "") << '\n';
    }
}
