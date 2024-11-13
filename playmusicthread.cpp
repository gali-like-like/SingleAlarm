#include "playmusicthread.h"
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioOutput>
PlayMusicThread::PlayMusicThread() {
    player = new QMediaPlayer();
    QAudioDevice audioDevice = QMediaDevices::defaultAudioOutput();
    qDebug()<<audioDevice.description();
    QAudioOutput* audioOutput = new QAudioOutput(audioDevice);
    audioOutput->setVolume(1);
    player->setAudioOutput(audioOutput);
}

PlayMusicThread::PlayMusicThread(QString musicPath, const QDateTime &dateTime)
{
    PlayMusicThread();
    this->musicPath = musicPath;
    this->playDateTime = dateTime;
}

void PlayMusicThread::run() {
    qint64 seconds = QDateTime::currentDateTime().secsTo(this->playDateTime);
    qDebug()<<"总共"<<seconds<<"s";
    while (seconds >= 0) {
        this->sleep(1);
        seconds = seconds -1;
        qDebug()<<"还剩"<<seconds<<"s";
    }
    player->play();
}

void PlayMusicThread::setFile(QString musicPath)
{
    this->musicPath = musicPath;
    player->setSource(QUrl::fromLocalFile(musicPath));
}

QString PlayMusicThread::getFile()
{
    return this->musicPath;
}

void PlayMusicThread::setPlayTime(const QDateTime& dateTime)
{
    this->playDateTime = dateTime;
}
