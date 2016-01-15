#include "MainWindow.h"
#include "SystemTray.h"
#include "TableModel.h"
#include "QComboBoxItemDelegate.h"
#include <QtAlgorithms>
#include "Contstants.h"
#include "Parser.h"

MainWindow::MainWindow(QWidget* parent) : QWidget(parent)
{
    QCoreApplication::setApplicationName("TLP GUI");
    QCoreApplication::setApplicationVersion("0.0.1");
    QCoreApplication::setOrganizationDomain("https://github.com/ZaMaZaN4iK/tlp-gui");
    //Create the interface
    pvbx = new QVBoxLayout;
    phbx = new QHBoxLayout;
    pbtn = new QPushButton(tr("&Open current profile"));
    pAC = new QPushButton(tr("&AC mode"));
    pBAT = new QPushButton(tr("&Battery mode"));
    pbtnTab = new QPushButton(tr("&Save Table to File"));
    pbar = new QMenuBar;



    ptab = new TableModel(80, 2, this);
    ptable = new QTableView(this);
    st = new SystemTray(this);

    QSignalMapper* mapper = new QSignalMapper(this);

    connect(pbtnTab, SIGNAL(clicked()), SLOT(slotSaveTable()));
    connect(pbtn, SIGNAL(clicked()), SLOT(slotCallEditor()));

    connect(pAC, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(pAC, "AC");
    connect(pBAT, SIGNAL(clicked()), mapper, SLOT(map()));
    mapper->setMapping(pBAT, "Battery");

    connect(mapper, SIGNAL(mapped(QString)), SLOT(slotSwitchMode(QString)));


    ptable->setModel(ptab);
    ptable->setItemDelegate(new QComboBoxItemDelegate(ptable));
    lbl.setTextInteractionFlags(Qt::TextEditable | Qt::TextEditorInteraction);




    for(int i = 0; i < ptab->rowCount(QModelIndex()); ++i)
    {
        ptable->openPersistentEditor(ptab->index(i, 1));
    }


    //----------------------------------------------------------------
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
    //----------------------------------------------------------------

    //fillTable();
    createQMenuBar();
    pvbx->addWidget(pbar);
    phbx->addWidget(pbtn);
    phbx->addWidget(pAC);
    phbx->addWidget(pBAT);
    phbx->addWidget(pbtnTab);
    pvbx->addLayout(phbx);
    pvbx->addWidget(&lbl);
    pvbx->addWidget(ptable);
    setLayout(pvbx);
    setWindowTitle("TLP GUI v.0.0.1");
    readSettings();
}

MainWindow::~MainWindow()
{
    writeSettings();
}

void MainWindow::writeSettings()
{
    m_sett.beginGroup("/Settings");
    m_sett.setValue("/geometry", geometry());
    m_sett.setValue("/pathToProf", pathToProf);
    m_sett.setValue("/lastProfile", curProf);
    m_sett.endGroup();
}

void MainWindow::readSettings()
{
    m_sett.beginGroup("/Settings");
    QRect geom = m_sett.value("/geometry", QRect()).toRect();
    pathToProf = m_sett.value("/pathToProf", QDir::homePath() + "/tlp_profiles").toString();
    curProf = m_sett.value("/lastProfile", "AC").toString();
    m_sett.endGroup();
    setGeometry(geom);
}

void MainWindow::createQMenuBar()
{
    QMenu* pmenu = new QMenu(tr("&File"));
    QMenu* phelp = new QMenu(tr("&Help"));
    createQMenuFile(pmenu);
    createQMenuHelp(phelp);
    pbar->addMenu(pmenu);
    pbar->addMenu(phelp);
}

void MainWindow::createQMenuFile(QMenu* pmenu)
{
    QAction* popn = pmenu->addAction(tr("&Open..."));
    popn->setShortcut(Qt::CTRL + Qt::Key_O);
    connect(popn, SIGNAL(triggered()), SLOT(slotOpenFile()));

    QAction* psv = pmenu->addAction(tr("&Save"));
    psv->setShortcut(Qt::CTRL + Qt::Key_S);
    connect(psv, SIGNAL(triggered()), SLOT(slotSaveFile()));

    QAction* psett = pmenu->addAction(tr("&Settings"));
    psv->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(psett, SIGNAL(triggered()), SLOT(slotSettings()));

    pmenu->addAction(tr("&Exit"), qApp, SLOT(quit()));
}

void MainWindow::createQMenuHelp(QMenu* phelp)
{
    phelp->addAction(tr("&About QT"), qApp, SLOT(aboutQt()));
}


void MainWindow::slotSaveTable()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save Dialog"), "/etc/default", "");
    //AdminAuthorization::execute(this, "/home/zamazan4ik/build-tlp-gui-Desktop_Qt_5_5_1_GCC_64bit-Debug/tlp-gui", QStringList());
    if(str != "")
    {
        QFile file(str);
        if(!file.open(QIODevice::WriteOnly | QFile::Truncate))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not create the file"));
            return;
        }
        QTextStream out(&file);
        auto it = keyword.begin();
        for(int i = 0; i < 80; ++i)
        {
            QModelIndex index1 = ptab->index(i, 0);
            QModelIndex index2 = ptab->index(i, 1);
            out << ptab->data(index1, Qt::DisplayRole).toString()
                << "=" << ptab->data(index2, Qt::DisplayRole).toString() << '\n';
        }
        file.close();
    }
}

void MainWindow::slotSaveFile()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save Dialog"), "/etc/default", "");
    //AdminAuthorization::execute(this, "/home/zamazan4ik/build-tlp-gui-Desktop_Qt_5_5_1_GCC_64bit-Debug/tlp-gui", QStringList());
    if(str != "")
    {
        QFile file(str);
        if(!file.open(QIODevice::WriteOnly | QFile::Truncate))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not create the file"));
            return;
        }
        QTextStream out(&file);
        out << lbl.toPlainText();
        file.close();
    }
    slotSaveTable();
}

void MainWindow::slotOpenFile()
{
    QString str = QFileDialog::getOpenFileName(0, tr("Open Dialog"), "/etc/default/", "");
    if(str != "")
    {
        QFile filename(str);
        if(!filename.open(QIODevice::ReadOnly))
        {
            QMessageBox::critical(this, tr("Error"), tr("Could not open the file"));
            return;
        }
        Parser out(filename);
        ptab->setData(out.getVector());
        filename.reset();
        QTextStream in(&filename);
        lbl.setText(in.readAll());

    }
}

void MainWindow::slotCallEditor()
{
    QFile file("/etc/default/tlp");
    QFileInfo info(file);
    QString filepath = info.absoluteFilePath();
    QUrl fileurl = QUrl::fromUserInput(filepath);
    QDesktopServices::openUrl(fileurl);
}

void MainWindow::slotAC()
{
    QProcess proc;
    proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp ac");
    proc.waitForFinished();
    QByteArray arr = proc.readAll();
    QString str = arr.data();
    qDebug() << str << QString("TLP started in AC mode.\n");
    if(qFind(str, QString("TLP started in AC mode.\n")) != str.end())
    {
        QMessageBox::information(this, "Notification", "AC mode has activated");
    }
    else
    {
        QMessageBox::warning(this, "Warning", "AC mode hasn't activated");
    }
}

void MainWindow::slotBAT()
{
    QProcess proc;
    proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp bat");
    proc.waitForFinished();
    QByteArray arr = proc.readAll();
    qDebug() << arr;
    QMessageBox::information(this, "Notification", "Battery mode activated");
}

void MainWindow::slotSwitchMode(QString mode)
{
    QProcess proc;
    mode == "AC" ? proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp ac")
                 : proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp bat");
    proc.waitForFinished();
    QByteArray arr = proc.readAll();
    qDebug() << arr;
    mode == "AC" ? QMessageBox::information(this, "Notification", "AC mode has activated")
                 : QMessageBox::information(this, "Notification", "Battery mode activated");
}

void MainWindow::slotSettings()
{

}
