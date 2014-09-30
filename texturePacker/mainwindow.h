#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void initUI();
    void initMenu();
    void initAction();
    void initInputSettingsGroup();
    void initOutputSettingGroup();
    void initOpGroup();
    void initOutputGroup();

private:
    QAction     * m_aAboutMe;
    QMenu       * m_mAboutMe;

    QLineEdit   * m_leInputSettingPath;
    QLineEdit   * m_leOutputSettingPath;
    QPushButton * m_pbInputSettingPath;
    QPushButton * m_pbOutputSettingPath;

    QPushButton * m_pbPublish;
    QPushButton * m_pbClosed;

    QRadioButton * m_rbtnIOS;
    QRadioButton * m_rbtnAndroid;

    QGroupBox   * m_gbInputSettingGroup;
    QGroupBox   * m_gbOutputSettingGroup;
    QGroupBox   * m_gbOpGroup;
    QGroupBox   * m_gbOutputGroup;

    QPlainTextEdit * m_pteOutput;

    QWidget     * m_wMainWidget;
private slots:
    void onAboutMeAction();
    void onSettingInputPathEvent();
    void onSettingOutputPathEvent();
};

#endif // MAINWINDOW_H
