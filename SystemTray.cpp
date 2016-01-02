#include <QtWidgets>
#include "SystemTray.h"
#include "mainwindow.h"

// ----------------------------------------------------------------------
SystemTray::SystemTray(QWidget* pwgt /*=0*/) : QWidget(pwgt)
{
    setWindowTitle("System Tray");

    QAction* pactShowHide =
        new QAction("&Show/Hide Application Window", this);

    connect(pactShowHide, SIGNAL(triggered()),
            this,         SLOT(slotShowHide())
           );

    QAction* pactShowMessage = new QAction("S&how Message", this);
    connect(pactShowMessage, SIGNAL(triggered()),
            this,            SLOT(slotShowMessage())
           );

    QAction* pactQuit = new QAction("&Quit", this);
    connect(pactQuit, SIGNAL(triggered()), qApp, SLOT(quit()));

    m_ptrayIconMenu = new QMenu(this);
    m_ptrayIconMenu->addAction(pactShowHide);
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
    m_ptrayIcon->showMessage("Information",
                             "You have selected the " + qobject_cast<MainWindows*>(this->parent())->curProf + "\"Show Message!\" option",
                             QSystemTrayIcon::Information,
                             3000
                            );
}

// ----------------------------------------------------------------------

