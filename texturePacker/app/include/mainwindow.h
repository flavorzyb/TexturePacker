#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QString>

#include "common/include/settingsvo.h"
#include "include/publishthread.h"

class TpApplication;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setApp(TpApplication *app);

private slots:
    void updatePublishInfo(QString info);
    void onPublishFinished();

private:
    void initUI();
    void initMenu();
    void initAction();
    void initInputSettingsGroup();
    void initOutputSettingGroup();
    void initOpGroup();
    void initOutputGroup();
    void initStatusBar();

private slots:
    void onToolsAction();
    void onAboutMeAction();
    void onSettingInputPathEvent();
    void onSettingOutputPathEvent();
    void onPublishEvent();

private:
    QAction         * m_aAboutMe;
    QMenu           * m_mAboutMe;
    QAction         * m_aTools;
    QMenu           * m_mTools;
    QLabel          * m_lbStatusBar;

    QLineEdit       * m_leInputSettingPath;
    QLineEdit       * m_leOutputSettingPath;
    QPushButton     * m_pbInputSettingPath;
    QPushButton     * m_pbOutputSettingPath;

    QPushButton     * m_pbPublish;
    QPushButton     * m_pbClosed;

    QRadioButton    * m_rbtnIOS;
    QRadioButton    * m_rbtnAndroid;

    QGroupBox       * m_gbInputSettingGroup;
    QGroupBox       * m_gbOutputSettingGroup;
    QGroupBox       * m_gbOpGroup;
    QGroupBox       * m_gbOutputGroup;

    QPlainTextEdit  * m_pteOutput;

    QWidget         * m_wMainWidget;

    SettingsVO      m_settingsvo;
    PublishThread   m_publish;
    TpApplication   * m_app;
};

#endif // MAINWINDOW_H
