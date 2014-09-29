#ifndef ABOUTME_H
#define ABOUTME_H

#include <QWidget>
#include <QDialog>

class AboutMe : public QDialog
{
    Q_OBJECT
public:
    explicit AboutMe(QWidget *parent);

private:
    void initUI();
};

#endif // ABOUTME_H
