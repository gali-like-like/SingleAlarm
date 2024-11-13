#ifndef PLAYMUSICTHREAD_H
#define PLAYMUSICTHREAD_H
#include <QThread>
#include <QMediaPlayer>
#include <QDateTime>
class PlayMusicThread:public QThread
{
public:
    PlayMusicThread();
    PlayMusicThread(QString musicPath,const QDateTime& dateTime);
    void run();
    void setFile(QString musicPath);
    QString getFile();
    void setPlayTime(const QDateTime& dateTime);
private:
    QString musicPath;
    QMediaPlayer* player;
    QDateTime playDateTime;
};

#endif // PLAYMUSICTHREAD_H
