#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>
#include <QGridLayout>

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
    void initInputGroup();
    void initOutputGroup();
    void initOpGroup();
private:
    QAction     * m_aAboutMe;
    QMenu       * m_mAboutMe;
    QLineEdit   * m_leInputDirPath;
    QLineEdit   * m_leOutputDirPath;
    QPushButton * m_pbInputDirPath;
    QPushButton * m_pbOutputDirPath;
    QGroupBox   * m_gbInputGroup;
    QGroupBox   * m_gbOutputGroup;
    QGroupBox   * m_gbOpGroup;

private slots:
    void onAboutMeAction();
};

#endif // MAINWINDOW_H
