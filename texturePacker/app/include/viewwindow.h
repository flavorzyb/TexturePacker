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
    void onSpinBoxValueChanged(double value);
    void onSliderValueChanged(int value);

private:
    void initUI();
    void initMenu();
    void initAction();
    void initStatusBar();
    void initInfoList();
    void initViewArea();
    void initBottom();
    void onMagnificationImage();

private:
    QWidget         * m_wWindow;
    QListWidget     * m_lwInfoList;
    QDoubleSpinBox  * m_sbMagnificationBox;
    QSlider         * m_sMagnificationSlider;
    QAction         * m_aFile;
    QMenu           * m_mFile;
    QLabel          * m_lbStatusBar;
    QGraphicsView   * m_lbViewContent;
    QGraphicsScene  * m_lbViewScene;
    QImage            m_viewImage;
    QGroupBox       * m_gbMagnification;
    double          m_scaleValue;
};

#endif // VIEWWINDOW_H
