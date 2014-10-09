#ifndef WORKER_H
#define WORKER_H
#include <QString>
#include <QThread>

class Worker : public QThread
{
    Q_OBJECT
public:
    explicit Worker();
    void run();
    QString imageFilePath() const;
    void setImageFilePath(const QString &imageFilePath);

    QString inputPath() const;
    void setInputPath(const QString &inputPath);

    QString outputPath() const;
    void setOutputPath(const QString &outputPath);

signals:
    void done(bool succ, const QString & imagePath);

public slots:

private:
    Worker(const Worker & wk);
    const Worker & operator =(const Worker & wk);

private:
    QString m_imageFilePath;
    QString m_inputPath;
    QString m_outputPath;
};

#endif // WORKER_H
