#include "Backend.h"

Backend::Backend()
{
//    keyword  << "TLP_ENABLE" << "TLP_DEFAULT_MODE" << "DISK_IDLE_SECS_ON_AC" << "MAX_LOST_WORK_SECS_ON_AC"
//             << "CPU_SCALING_GOVERNOR_ON_AC" << "CPU_SCALING_MIN_FREQ_ON_AC" << "CPU_SCALING_MAX_FREQ_ON_AC"
//             << "CPU_MIN_PERF_ON_AC" << "CPU_MAX_PERF_ON_AC" << "CPU_BOOST_ON_AC" << "SCHED_POWERSAVE_ON_AC"
//             << "NMI_WATCHDOG" << "PHC_CONTROLS" << "ENERGY_PERF_POLICY_ON_AC" << "DISK_DEVICES" << "DISK_APM_LEVEL_ON_AC"
//             << "DISK_SPINDOWN_TIMEOUT_ON_AC" << "DISK_IOSCHED" << "SATA_LINKPWR_ON_AC" << "PCIE_ASPM_ON_AC"
//             << "RADEON_POWER_PROFILE_ON_AC" << "RADEON_DPM_STATE_ON_AC" << "RADEON_DPM_PERF_LEVEL_ON_AC" << "WIFI_PWR_ON_AC"
//             << "WOL_DISABLE" << "SOUND_POWER_SAVE_ON_AC" << "SOUND_POWER_SAVE_CONTROLLER" << "BAY_POWEROFF_ON_BAT"
//             << "BAY_DEVICE" << "RUNTIME_PM_ON_AC" << "RUNTIME_PM_ALL" << "RUNTIME_PM_BLACKLIST" << "RUNTIME_PM_DRIVER_BLACKLIST"
//             << "USB_AUTOSUSPEND" << "USB_BLACKLIST" << "USB_BLACKLIST_WWAN" << "USB_WHITELIST" << "USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN"
//             << "RESTORE_DEVICE_STATE_ON_STARTUP" << "DEVICES_TO_DISABLE_ON_STARTUP" << "DEVICES_TO_ENABLE_ON_STARTUP"
//             << "DEVICES_TO_DISABLE_ON_SHUTDOWN" << "DEVICES_TO_ENABLE_ON_SHUTDOWN" << "DEVICES_TO_ENABLE_ON_AC"
//             << "DEVICES_TO_DISABLE_ON_BAT" << "DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE" << "START_CHARGE_THRESH_BAT0"
//             << "STOP_CHARGE_THRESH_BAT0" << "START_CHARGE_THRESH_BAT1" << "STOP_CHARGE_THRESH_BAT1"
//             << "DEVICES_TO_DISABLE_ON_LAN_CONNECT" << "DEVICES_TO_DISABLE_ON_WIFI_CONNECT" << "DEVICES_TO_DISABLE_ON_WWAN_CONNECT"
//             << "DEVICES_TO_ENABLE_ON_LAN_DISCONNECT" << "DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT" << "DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT"
//             << "DEVICES_TO_ENABLE_ON_DOCK" << "DEVICES_TO_DISABLE_ON_DOCK" << "DEVICES_TO_ENABLE_ON_UNDOCK"
//             << "DEVICES_TO_DISABLE_ON_UNDOCK" << "DEVICES_TO_DISABLE_ON_UNDOCK";

    keyword << QPair<QString, QStringList>("TLP_ENABLE", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("DISK_IDLE_SECS_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("MAX_LOST_WORK_SECS_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("CPU_SCALING_GOVERNOR_ON_AC", QStringList() << "QComboBox" << "ondemand" << "powersave" << "performance" << "conservative")
            << QPair<QString, QStringList>("CPU_SCALING_MIN_FREQ_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("CPU_SCALING_MAX_FREQ_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("CPU_MIN_PERF_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("CPU_MAX_PERF_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("CPU_BOOST_ON_AC", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("SCHED_POWERSAVE_ON_AC", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("NMI_WATCHDOG", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("PHC_CONTROLS", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("ENERGY_PERF_POLICY_ON_AC", QStringList() << "QComboBox" << "performance" << "normal" << "powersave")
            << QPair<QString, QStringList>("DISK_DEVICES", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("DISK_APM_LEVEL_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("DISK_SPINDOWN_TIMEOUT_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("DISK_IOSCHED", QStringList() << "QComboBox" << "noop" << "deadline" << "cfq")
            << QPair<QString, QStringList>("SATA_LINKPWR_ON_AC", QStringList() << "QComboBox" << "min_power" << "medium_power" << "max_performance")
            << QPair<QString, QStringList>("PCIE_ASPM_ON_AC", QStringList() << "QComboBox" << "default" << "performance" << "powersave")
            << QPair<QString, QStringList>("RADEON_POWER_PROFILE_ON_AC", QStringList() << "QComboBox" << "low" << "mid" << "high" << "auto" << "default")
            << QPair<QString, QStringList>("RADEON_DPM_STATE_ON_AC", QStringList() << "QComboBox" << "battery" << "performance")
            << QPair<QString, QStringList>("RADEON_DPM_PERF_LEVEL_ON_AC", QStringList() << "QComboBox" << "auto" << "low" << "high")
            << QPair<QString, QStringList>("WIFI_PWR_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("WOL_DISABLE", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("SOUND_POWER_SAVE_ON_AC", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("SOUND_POWER_SAVE_CONTROLLER", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("BAY_POWEROFF_ON_BAT", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("BAY_DEVICE", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("RUNTIME_PM_ON_AC", QStringList() << "QComboBox" << "on" << "auto")
            << QPair<QString, QStringList>("RUNTIME_PM_ALL", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("RUNTIME_PM_BLACKLIST", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("RUNTIME_PM_DRIVER_BLACKLIST", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("USB_AUTOSUSPEND", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("USB_BLACKLIST", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("USB_BLACKLIST_WWAN", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("USB_WHITELIST", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("USB_AUTOSUSPEND_DISABLE_ON_SHUTDOWN", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("RESTORE_DEVICE_STATE_ON_STARTUP", QStringList() << "QCheckBox")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_STARTUP", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_STARTUP", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_SHUTDOWN", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_SHUTDOWN", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_AC", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_BAT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_BAT_NOT_IN_USE", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("START_CHARGE_THRESH_BAT0", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("STOP_CHARGE_THRESH_BAT0", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("START_CHARGE_THRESH_BAT1", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("STOP_CHARGE_THRESH_BAT1", QStringList() << "QLineEdit")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_LAN_CONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_WIFI_CONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_WWAN_CONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_LAN_DISCONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_WIFI_DISCONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_WWAN_DISCONNECT", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_DOCK", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_DOCK", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_ENABLE_ON_UNDOCK", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan")
            << QPair<QString, QStringList>("DEVICES_TO_DISABLE_ON_UNDOCK", QStringList() << "QComboBox" << "bluetooth" << "wifi" << "wwan");
}

