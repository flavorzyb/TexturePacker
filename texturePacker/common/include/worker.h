#ifndef WORKER_H
#define WORKER_H
#include <QString>
#include <QThread>

class Publisher;

class Worker : public QThread
{
    Q_OBJECT

public:
    explicit Worker();

    QString imageFilePath() const;
    void setImageFilePath(const QString &imageFilePath);

    QString inputPath() const;
    void setInputPath(const QString &inputPath);

    QString outputPath() const;
    void setOutputPath(const QString &outputPath);

    void setPublisher(Publisher *publisher);

private:
    Worker(const Worker & wk);
    const Worker & operator =(const Worker & wk);
    void run();

private:
    QString m_imageFilePath;
    QString m_inputPath;
    QString m_outputPath;
    Publisher *m_publisher;
};

#endif // WORKER_H
