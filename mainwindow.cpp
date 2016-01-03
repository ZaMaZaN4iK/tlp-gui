#include "mainwindow.h"
#include "SystemTray.h"

MainWindows::MainWindows(QWidget* parent) : QWidget(parent)
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
    pbar = new QMenuBar;
    ptable = new QTableWidget(80, 2, this);
    st = new SystemTray(this);

    connect(pbtn, SIGNAL(clicked()), SLOT(slotCallEditor()));
    connect(pAC, SIGNAL(clicked()), SLOT(slotAC()));
    connect(pBAT, SIGNAL(clicked()), SLOT(slotBAT()));

    ptable->setHorizontalHeaderLabels(QStringList() << tr("Property") << tr("Value"));
    lbl.setTextInteractionFlags(Qt::TextEditable | Qt::TextEditorInteraction);
    fillTable();
    createQMenuBar();
    pvbx->addWidget(pbar);
    phbx->addWidget(pbtn);
    phbx->addWidget(pAC);
    phbx->addWidget(pBAT);
    pvbx->addLayout(phbx);
    pvbx->addWidget(&lbl);
    pvbx->addWidget(ptable);
    setLayout(pvbx);
    setWindowTitle("TLP GUI v.0.0.1");
    readSettings();
}

MainWindows::~MainWindows()
{
    writeSettings();
}

void MainWindows::writeSettings()
{
    m_sett.beginGroup("/Settings");
    m_sett.setValue("/geometry", geometry());
    m_sett.setValue("/pathToProf", pathToProf);
    m_sett.setValue("/lastProfile", curProf);
    m_sett.endGroup();
}

void MainWindows::readSettings()
{
    m_sett.beginGroup("/Settings");
    QRect geom = m_sett.value("/geometry", QRect()).toRect();
    pathToProf = m_sett.value("/pathToProf", QDir::homePath() + "/tlp_profiles").toString();
    curProf = m_sett.value("/lastProfile", "AC").toString();
    m_sett.endGroup();
    setGeometry(geom);
}

void MainWindows::createQMenuBar()
{
    QMenu* pmenu = new QMenu(tr("&File"));
    QMenu* phelp = new QMenu(tr("&Help"));
    createQMenuFile(pmenu);
    createQMenuHelp(phelp);
    pbar->addMenu(pmenu);
    pbar->addMenu(phelp);
}

void MainWindows::createQMenuFile(QMenu* pmenu)
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

void MainWindows::createQMenuHelp(QMenu* phelp)
{
    phelp->addAction(tr("&About QT"), qApp, SLOT(aboutQt()));
}

void MainWindows::loadTempFile(QMap<QString, QStringList>& val)
{
//    QFile prop("/home/zamazan4ik/listOfProperties.txt");
//    if(prop.open(QIODevice::ReadOnly))
//    {
//        QTextStream s_prop(&prop);
//        QString for_prop;
//        while(s_prop.readLineInto(&for_prop))
//        {
//            val.insert(for_prop,)
//        }
//    }
}

void MainWindows::fillTable()
{
    QFile prop("/home/zamazan4ik/listOfProperties.txt"),
          values("/home/zamazan4ik/listOfValues.txt");
    if(prop.open(QIODevice::ReadOnly) && values.open(QIODevice::ReadOnly))
    {
        QTextStream s_prop(&prop), s_val(&values);
        QString for_prop, for_val;
        int row = 0;
        QMap<QString, QStringList> val;
        loadTempFile(val);
        while(s_prop.readLineInto(&for_prop) && s_val.readLineInto(&for_val))
        {
            QTableWidgetItem* tProp = new QTableWidgetItem(for_prop);
            QLineEdit* pbox = new QLineEdit;
            pbox->setText(for_val);
            ptable->setItem(row, 0, tProp);
            ptable->setCellWidget(row, 1, pbox);
            ++row;
        }
    }
}

void MainWindows::slotSaveFile()
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
}

void MainWindows::slotOpenFile()
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
        QTextStream in(&filename);
        lbl.setText(in.readAll());
        filename.close();
    }
}

void MainWindows::slotCallEditor()
{
    QFile file("/etc/default/tlp");
    QFileInfo info(file);
    QString filepath = info.absoluteFilePath();
    QUrl fileurl = QUrl::fromUserInput(filepath);
    QDesktopServices::openUrl(fileurl);
}

void MainWindows::slotAC()
{
    QProcess proc;
    proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp ac");
    proc.waitForFinished();
    QByteArray arr = proc.readAll();
    qDebug() << arr;
    QMessageBox::information(this, "Notification", "AC mode activated");
}

void MainWindows::slotBAT()
{
    QProcess proc;
    proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp bat");
    proc.waitForFinished();
    QByteArray arr = proc.readAll();
    qDebug() << arr;
    QMessageBox::information(this, "Notification", "Battery mode activated");
}

void MainWindows::slotSwitchMode()
{

}

void MainWindows::slotSettings()
{

}
