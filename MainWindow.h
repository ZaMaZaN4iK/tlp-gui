#pragma once

#include <QtWidgets>
#include <QSettings>
#include "SystemTray.h"
#include "TableModel.h"

class SystemTray;

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    friend SystemTray;

    static const int columnTable = 2;

    QList<QPair<QString, QStringList> > keyword;

    QVBoxLayout* pvbx;
    QHBoxLayout* phbx;
    QPushButton* pbtn, *pAC, *pBAT, *pbtnTab;
    QMenuBar* pbar;
    TableModel* ptab;
    QTableView* ptable;
    SystemTray* st;
    QSettings m_sett;

    bool state;
    QString curProf;
    QString pathToProf;

    void readSettings();
    void writeSettings();
    void createQMenuBar();
    void createQMenuFile(QMenu*);
    void createQMenuHelp(QMenu*);
    //void fillTable();
    void loadTempFile(QMap<QString, QStringList>&);//TODO : Only for studying and testing

public :
    MainWindow(QWidget* parent = 0);
    ~MainWindow();

public slots:
    //void slotSaveTable();
    void slotOpenFile();
    void slotSaveFile();
    void slotSaveTable();
    void slotCallEditor();
    void slotSwitchMode(QString mode);
    void slotSettings();
    void slotAC();
    void slotBAT();
    void slotAboutProgram();
};
