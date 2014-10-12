#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QtWidgets>

class ViewWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit ViewWindow(QWidget *parent = 0);

private slots:
    void onFileAction();

private:
    void initUI();
    void initMenu();
    void initAction();
    void initStatusBar();

private:
    QWidget         * m_wWindow;
    QAction         * m_aFile;
    QMenu           * m_mFile;
};

#endif // VIEWWINDOW_H
