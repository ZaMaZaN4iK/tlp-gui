#include "TableModel.h"
#include "Contstants.h"

TableModel::TableModel(int nRows, int nColumns, QObject* pobj)
    : QAbstractTableModel(pobj)
    , m_nRows(nRows)
    , m_nColumns(nColumns)
{
    m_prop = QVector<Property>({Property("TLP_ENABLE", "1", QStringList(), "Enable\\Disable TLP", Property::QCheckBox, Property::MAIN, false, true, true, false),
                                Property("DISK_IDLE_SECS_ON_AC", "0", QStringList(), "Seconds laptop mode has to wait after the disk goes idle before doing a sync.\nNon-zero value enables, zero disables laptop mode", Property::QLineEdit, Property::DISK, false, true, true, false),
                                Property("MAX_LOST_WORK_SECS_ON_AC", "15", QStringList(), "Dirty page values (timeouts in secs)", Property::QLineEdit, Property::OTHER, false, true, true, false),
                                Property("CPU_SCALING_GOVERNOR_ON_AC", "ondemand", QStringList() << "ondemand" << "powersave" << "performance" << "conservative", "Select a CPU frequency scaling governor:\n   ondemand, powersave, performance, conservative\nIntel Core i processor with intel_pstate driver:\n   powersave, performance\nImportant : You *must* disable your distribution's governor settings or conflicts will occur\nondemand is sufficient for *almost all* workloads,\nyou should know what you're doing!", Property::QComboBox, Property::CPU, false, false, false, false),
                                Property("CPU_SCALING_MIN_FREQ_ON_AC", "0", QStringList(), "Set the min frequency available for the scaling governor\nPossible values strongly depend on your CPU. For available frequencies see\ntlp-stat output, Section \"+++ Processor\"", Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_SCALING_MAX_FREQ_ON_AC", "0", QStringList(), "Set the max frequency available for the scaling governor\nPossible values strongly depend on your CPU. For available frequencies see\ntlp-stat output, Section \"+++ Processor\"", Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_MIN_PERF_ON_AC", "0", QStringList(), "Set Intel P-state performance: 0..100 (%)\nLimit the min P-state to control the power dissipation of the CPU.\nValues are stated as a percentage of the available performance.\nRequires an Intel Core i processor with intel_pstate driver", Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_MAX_PERF_ON_AC", "100", QStringList(), "Set Intel P-state performance: 0..100 (%)\nLimit the max P-state to control the power dissipation of the CPU.\nValues are stated as a percentage of the available performance.\nRequires an Intel Core i processor with intel_pstate driver", Property::QLineEdit, Property::CPU, false, false, false, false),
                                Property("CPU_BOOST_ON_AC", "1", QStringList(), "Allow\\Disallow the CPU Turbo Boost feature\nRequires an Intel Core i processor.\n- This may conflict with your distribution's governor settings", Property::QCheckBox, Property::CPU, false, false, false, false),
                                Property("SCHED_POWERSAVE_ON_AC", "0", QStringList(), "Minimize number of used CPU cores/hyper-threads under light load conditions", Property::QCheckBox, Property::CPU, false, false, true, false),
                                Property("NMI_WATCHDOG", "0", QStringList(), "Enable\\Disable Kernel NMI Watchdog:\nDefault : Disable, saves power)\nEnable onlu for kernel debugging", Property::QCheckBox, Property::OTHER, true, false, false, false),
                                Property("PHC_CONTROLS", "", QStringList(), "Change CPU voltages aka \"undervolting\" - Kernel with PHC patch required\nFrequency voltage pairs are written to:\n   /sys/devices/system/cpu/cpu0/cpufreq/phc_controls\nCAUTION: only use this, if you thoroughly understand what you are doing!", Property::QLineEdit, Property::OTHER, true, false, false, true),
                                Property("ENERGY_PERF_POLICY_ON_AC", "performance", QStringList() << "performance" << "normal" << "powersave", "Set CPU performance versus energy savings policy:\n   performance, normal, powersave\nRequires kernel module msr and x86_energy_perf_policy from linux-tools", Property::QComboBox, Property::OTHER, false, false, false, false),
                                Property("DISK_DEVICES", "sda", QStringList(), "Hard disk devices; separate multiple devices with spaces (default: sda)\nDevices can be specified by disk ID also (lookup with: tlp diskid)", Property::QLineEdit, Property::DISK, false, false, true, true),
                                Property("DISK_APM_LEVEL_ON_AC", "254", QStringList(), "Hard disk advanced power management level: 1..254, 255 (max saving, min, off)\nLevels 1..127 may spin down the disk\n255 allowable on most drives\nSeparate values for multiple devices with spaces", Property::QLineEdit, Property::DISK, false, false, true, true),
                                Property("DISK_SPINDOWN_TIMEOUT_ON_AC", "0", QStringList(), "Hard disk spin down timeout:\n0 : spin down disabled\n1..240 : timeouts from 5s to 20min (in units of 5s)\n241..251 : timeouts from 30min to 5.5 hours (in units of 30min)\nSee 'man hdparm' for details", Property::QLineEdit, Property::DISK, false, false, false, true),
                                Property("DISK_IOSCHED", "cfq", QStringList() << "noop" << "deadline" << "cfq", "Select IO scheduler for the disk devices\n(Default: cfq)", Property::QComboBox, Property::DISK, false, false, false, true),
                                Property("SATA_LINKPWR_ON_AC", "max_performance", QStringList() << "min_power" << "medium_power" << "max_performance", "SATA aggressive link power management (ALPM)", Property::QComboBox, Property::OTHER, false, true, true, false),
                                Property("PCIE_ASPM_ON_AC", "performance", QStringList() << "default" << "performance" << "powersave", "PCI Express Active State Power Management (PCIe ASPM):", Property::QComboBox, Property::PCI, false, false, true, false),
                                Property("RADEON_POWER_PROFILE_ON_AC", "high", QStringList() << "low" << "mid" << "high" << "auto" << "default", "Radeon graphics clock speed (profile method)\nauto = mid on BAT, high on AC; default = use hardware defaults\n(Kernel >= 2.6.35 only, open-source radeon driver explicitly)", Property::QComboBox, Property::RADEON, false, false, false, false),
                                Property("RADEON_DPM_STATE_ON_AC", "performance", QStringList() << "battery" << "performance", "Radeon dynamic power management method (DPM).\n(Kernel >= 3.11 only, requires boot option radeon.dpm=1)", Property::QComboBox, Property::OTHER, false, false, false, false),
                                Property("RADEON_DPM_PERF_LEVEL_ON_AC", "auto", QStringList() << "auto" << "low" << "high", "Radeon DPM performance level.\nAuto is recommended", Property::QComboBox, Property::RADEON, false, false, false, false),
                                Property("WIFI_PWR_ON_AC", "1", QStringList(), "WiFi power saving mode: 1=disable, 5=enable; not supported by all adapters", Property::QLineEdit, Property::RADIO, false, false, true, false),
                                Property("WOL_DISABLE", "Y", QStringList(), "Enable\\Disable wake on LAN", Property::QCheckBox, Property::RADIO, false, false, true, false),
                                Property("SOUND_POWER_SAVE_ON_AC", "0", QStringList(), "Enable audio power saving for Intel HDA, AC97 devices (timeout in secs)\nA value of 0 disables, >=1 enables power save", Property::QLineEdit, Property::OTHER, false, false, false, false),
                                Property("SOUND_POWER_SAVE_CONTROLLER", "Y", QStringList(), "Disable sound controller (HDA only)", Property::QCheckBox, Property::OTHER, false, false, true, false),
                                Property("BAY_POWEROFF_ON_BAT", "0", QStringList(), "Enable to power off optical drive in UltraBay/MediaBay when running on battery.\nDrive can be powered on again by releasing (and reinserting) the eject lever\nor by pressing the disc eject button on newer models.\nNote: an UltraBay/MediaBay hard disk is never powered off", Property::QCheckBox, Property::OTHER, false, false, false, false),
                                Property("BAY_DEVICE", "sr0", QStringList(), "Optical drive device to power off (default sr0)", Property::QLineEdit, Property::OTHER, false, false, false, true),
                                Property("RUNTIME_PM_ON_AC", "on", QStringList() << "on" << "auto", "Runtime Power Management for PCI(e) bus devices", Property::QComboBox, Property::PCI, false, false, true, false),
                                Property("RUNTIME_PM_ALL", "1", QStringList(), "Runtime PM for *all* PCI(e) bus devices, except blacklisted ones", Property::QCheckBox, Property::PCI, false, false, true, false),
                                Property("RUNTIME_PM_BLACKLIST", "", QStringList(), "Exclude PCI(e) device adresses the following list from Runtime PM (separate with spaces)\nUse lspci to get the adresses (1st column)", Property::QLineEdit, Property::PCI, false, false, false, true),
                                Property("RUNTIME_PM_DRIVER_BLACKLIST", "radeon", QStringList(), "Exclude PCI(e) devices assigned to the listed drivers from Runtime PM\n(should prevent accidential power on of hybrid graphics' discrete part)\nDefault is \"radeon nouveau\"\nuse \"\" to disable the feature completely\nSeparate multiple drivers with spaces", Property::QLineEdit, Property::RADEON, false, false, false, true),
                                Property("USB_AUTOSUSPEND", "0", QStringList(), "Enable\\Disable USB autosuspend feature", Property::QCheckBox, Property::USB, false, false, true, false),
                                Property("USB_BLACKLIST", "", QStringList(), "Exclude listed devices from USB autosuspend (separate with spaces)\nUse lsusb to get the ids\nNote: input devices (usbhid) are excluded automatically (see below)", Property::QLineEdit, Property::USB, false, false, false, true),
                                Property("USB_BLACKLIST_WWAN", "1", QStringList(), "Enable\\Disable excluding WWAN devices from USB autosuspend", Property::QCheckBox, Property::USB, false, false, true, false),
                                Property("USB_WHITELIST", "", QStringList(), "Include listed devices into USB autosuspend even if already excluded\nby the driver or WWAN blacklists above (separate with spaces)\nUse lsusb to get the ids", Property::QLineEdit, Property::USB, false, false, false, true),
                                Property("USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN", "1", QStringList(), "Enable\\Disable stopping autosuspend before shutdown\n(workaround for USB devices that cause shutdown problems)", Property::QCheckBox, Property::USB, false, false, false, false),
                                Property("RESTORE_DEVICE_STATE_ON_STARTUP", "0", QStringList(), "Restore radio device state (Bluetooth, WiFi, WWAN) from previous shutdown\non system startup: 0=disable, 1=enable\nHint: the parameters DEVICES_TO_DISABLE/ENABLE_ON_STARTUP/SHUTDOWN below\nare ignored when this is enabled!", Property::QCheckBox, Property::RADIO, false, false, true, false),
                                Property("DEVICES_TO_DISABLE_ON_STARTUP", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on startup", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_STARTUP", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on startup", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_SHUTDOWN", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on shutdown (workaround for devices that are blocking shutdown)", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_SHUTDOWN", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on shutdown (to prevent other operating systems from missing radios)", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_AC", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on AC", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_BAT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on battery", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on battery when not in use (not connected)", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("START_CHARGE_THRESH_BAT0", "75", QStringList(), "Charging starts when the remaining capacity falls below the value (ThinkPad only)", Property::QLineEdit, Property::THINKPAD, false, false, false, false, Property::AboutValidator("Digit", 0, 100)),
                                Property("STOP_CHARGE_THRESH_BAT0", "80", QStringList(), "Charging stops when the remaining capacity exceeding the value (ThinkPad only)", Property::QLineEdit, Property::THINKPAD, false, false, false, false, Property::AboutValidator("Digit", 0, 100)),
                                Property("START_CHARGE_THRESH_BAT1", "75", QStringList(), "Ultrabay / Slice / Replaceable battery (values in %)\nSee previous property", Property::QLineEdit, Property::THINKPAD, false, false, false, false, Property::AboutValidator("Digit", 0, 100)),
                                Property("STOP_CHARGE_THRESH_BAT1", "80", QStringList(), "Ultrabay / Slice / Replaceable battery (values in %)\nSee previous property", Property::QLineEdit, Property::THINKPAD, false, false, false, false, Property::AboutValidator("Digit", 0, 100)),
                                Property("DEVICES_TO_DISABLE_ON_LAN_CONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on LAN connect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_WIFI_CONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on Wi-Fi connect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_WWAN_CONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable on WWAN connect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_LAN_DISCONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on LAN disconnect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on Wi-Fi disconnect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable on WWAN disconnect", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_DOCK", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable when docked", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_DOCK", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable when docked", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_ENABLE_ON_UNDOCK", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to enable when undocked", Property::GroupQCheckBox, Property::RADIO, false, false, false, true),
                                Property("DEVICES_TO_DISABLE_ON_UNDOCK", "bluetooth", QStringList() << "bluetooth" << "wifi" << "wwan", "Radio devices to disable when undocked", Property::GroupQCheckBox, Property::RADIO, false, false, false, true)});
    headerList << "Active" << "Property" << "Values";
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
    if(nRole == Qt::ToolTipRole)
    {
        return m_prop[index.row()].getComment();
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
        if(var.getTypeWidget() != Property::GroupQCheckBox) res = var.getCurVal();
        break;
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
    return index.isValid() && (index.column() == COL_VALUE || index.column() == COL_ACTIVE) ? (flags | Qt::ItemIsEditable)
                           : flags;
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    return orientation == Qt::Horizontal && role == Qt::DisplayRole
            ? headerList[section] : QVariant();
}

bool TableModel::Save(QTextStream & out) const
{
    for(int i = 0; i < m_prop.size(); ++i)
    {
        out << (m_prop[i].isActive() ? "" : "#") << m_prop[i].getName() << "=" << (m_prop[i].isText() ? "\"" : "")
            << m_prop[i].getCurVal() << (m_prop[i].isText() ? "\"" : "") << '\n';
    }
}
