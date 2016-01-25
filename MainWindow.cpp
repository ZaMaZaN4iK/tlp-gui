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


    QVector<QString> list({"Active", "Property", "Values"});

    ptab = new TableModel(59, NumOfColumn, this);
    for(int i = 0;i < 3;++i)
    {
        qDebug() << ptab->setHeaderData(i, Qt::Horizontal, list[i], Qt::DisplayRole);
    }
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
    for(int i = 0; i < ptab->rowCount(QModelIndex()); ++i)
    {
        ptable->openPersistentEditor(ptab->index(i, 0));
        //ptable->openPersistentEditor(ptab->index(i, 1));
        ptable->openPersistentEditor(ptab->index(i, 2));
    }


    createQMenuBar();
    pvbx->addWidget(pbar);
    phbx->addWidget(pbtn);
    phbx->addWidget(pAC);
    phbx->addWidget(pBAT);
    phbx->addWidget(pbtnTab);
    pvbx->addLayout(phbx);
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
    for(int i = 0; i < ptable->colorCount(); ++i)
    {
        m_sett.setValue("/geometry/" + QString::number(i), ptable->columnWidth(i));
    }

    m_sett.setValue("/pathToProf", pathToProf);
    m_sett.setValue("/lastProfile", curProf);
    m_sett.endGroup();
}

void MainWindow::readSettings()
{
    m_sett.beginGroup("/Settings");
    QRect geom = m_sett.value("/geometry", QRect()).toRect();
    for(int i = 0; i < ptable->colorCount(); ++i)
    {
        ptable->setColumnWidth(i, m_sett.value("/geometry/" + QString::number(i), 100).toInt());
    }

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
    psett->setShortcut(Qt::CTRL + Qt::Key_P);
    connect(psett, SIGNAL(triggered()), SLOT(slotSettings()));

    pmenu->addAction(tr("&Exit"), qApp, SLOT(quit()));
}

void MainWindow::createQMenuHelp(QMenu* phelp)
{
    QAction* about = phelp->addAction(tr("&About program"));
    connect(about, SIGNAL(triggered()), SLOT(slotAboutProgram()));
    phelp->addAction(tr("&About QT"), qApp, SLOT(aboutQt()));
}


void MainWindow::slotSaveTable()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save Dialog"), "/home/zamazan4ik/", "");
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
        ptab->Save(out);
        file.close();
    }
}

void MainWindow::slotSaveFile()
{
    QString str = QFileDialog::getSaveFileName(0, tr("Save Dialog"), "/home/zamazan4ik", "");
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
    QMessageBox::information(this, "Notification", "Battery mode activated");
}

void MainWindow::slotSwitchMode(QString mode)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("cp-866"));
    QProcess proc;
    mode == "AC" ? proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp ac")
                 : proc.start("/bin/sh", QStringList() << "-c" << "kdesudo tlp bat");
    proc.waitForFinished(-1);
    QString str = proc.readAll();
    if(str.indexOf("TLP") == -1)
    {
        mode == "AC" ? QMessageBox::information(this, "Notification", "AC mode hasn't activated")
                     : QMessageBox::information(this, "Notification", "Battery mode hasn't activated");
        return;
    }
    mode == "AC" ? QMessageBox::information(this, "Notification", "AC mode has activated")
                 : QMessageBox::information(this, "Notification", "Battery mode has activated");
}

void MainWindow::slotAboutProgram()
{
    QMessageBox::about(this, "About", "Author : Zaitsev Alexander\nTranslator : Zaitsev Alexander");
}

void MainWindow::slotSettings()
{

}
