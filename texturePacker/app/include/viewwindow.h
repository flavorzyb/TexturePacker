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
    bool loadFile(const QString & filePath);

private slots:
    void onFileAction();

private:
    void initUI();
    void initMenu();
    void initAction();
    void initStatusBar();
    void initInfoList();
    void initViewArea();
    void initBottom();
private:
    QWidget         * m_wWindow;
    QListWidget     * m_lwInfoList;
    QScrollArea     * m_sViewScroll;
    QSpinBox        * m_sbMagnificationBox;
    QSlider         * m_sMagnificationSlider;
    QAction         * m_aFile;
    QMenu           * m_mFile;
    QLabel          * m_lbStatusBar;
    QLabel          * m_lbViewContent;
};

#endif // VIEWWINDOW_H
