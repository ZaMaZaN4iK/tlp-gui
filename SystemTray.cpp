#include <QtWidgets>
#include "SystemTray.h"
#include "MainWindow.h"

// ----------------------------------------------------------------------
SystemTray::SystemTray(QWidget* pwgt /*=0*/) : QWidget(pwgt)
{
    setWindowTitle(tr("System Tray"));

    QAction* pactShowHide =
        new QAction(tr("&Show/Hide Application Window"), this);

    connect(pactShowHide, SIGNAL(triggered()),
            this,         SLOT(slotShowHide())
           );

    QAction* pactShowMessage = new QAction(tr("S&how Message"), this);
    connect(pactShowMessage, SIGNAL(triggered()),
            this,            SLOT(slotShowMessage())
           );

    QAction* pactQuit = new QAction(tr("&Quit"), this);
    connect(pactQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QAction* pactAC = new QAction(tr("Switch to AC Mode"), this);
    connect(pactAC, SIGNAL(triggered()), this->parent(), SLOT(slotAC()));

    QAction* pactBat = new QAction(tr("Switch to Battery Mode"), this);
    connect(pactBat, SIGNAL(triggered()), this->parent(), SLOT(slotBAT()));

    m_ptrayIconMenu = new QMenu(this);
    m_ptrayIconMenu->addAction(pactShowHide);
    m_ptrayIconMenu->addAction(pactAC);
    m_ptrayIconMenu->addAction(pactBat);
    m_ptrayIconMenu->addAction(pactShowMessage);
    m_ptrayIconMenu->addAction(pactQuit);

    m_ptrayIcon = new QSystemTrayIcon(this);
    m_ptrayIcon->setContextMenu(m_ptrayIconMenu);
    m_ptrayIcon->setToolTip(QCoreApplication::applicationName());


    m_ptrayIcon->setIcon(QPixmap("://images/IconForTray.png"));
    //slotChangeIcon();

    m_ptrayIcon->show();
}

// ----------------------------------------------------------------------
/*virtual*/void SystemTray::closeEvent(QCloseEvent*)
{
    if (m_ptrayIcon->isVisible())
    {
        this->parentWidget()->hide();
    }
}

// ----------------------------------------------------------------------
void SystemTray::slotShowHide()
{
    this->parentWidget()->setVisible(!isVisible());
}

// ----------------------------------------------------------------------
void SystemTray::slotShowMessage()
{
    m_ptrayIcon->showMessage(tr("Information"),
                             tr("You have selected the ") + qobject_cast<MainWindow*>(this->parent())->curProf +
                             tr("\"Show Message!\" option"),
                             QSystemTrayIcon::Information,
                             3000
                            );
}

// ----------------------------------------------------------------------

