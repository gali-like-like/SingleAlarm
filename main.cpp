#include <QCoreApplication>
#include <QLocale>
#include <QTranslator>
#include <QCommandLineParser>
#include <QDebug>
#include <QFile>
#include <QMimeDatabase>
#include <QMimeType>
#include <QMediaPlayer>
#include <QDateTime>
#include "playmusicthread.h"
#include <QRegularExpression>
#include <QRegularExpressionMatch>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    a.setApplicationVersion("1.0.0");
    /**
    -S 指定多少s后提醒
    -M 指定多少min后提醒
    -H 指定多少hour后提醒
    -P 指定提醒后的播放的音乐
    -T 指定具体时间后播放音乐
    ps：AT和H/M/S互斥,必须有-P和其他的时间选项
    **/
    QCommandLineParser parser;
    // 其他选项，例如：
    QCommandLineOption optionS("S", "Set a reminder in seconds.", "seconds");
    QCommandLineOption optionM("M", "Set a reminder in minutes.", "minutes");
    QCommandLineOption optionH("H", "Set a reminder in hours.", "hours");
    QCommandLineOption optionP("P", "Specify the music to play after the reminder.", "music file");
    QCommandLineOption optionT("T","Set a datetime,formatter yyyy-MM-dd hh:mm:ss;T and H/M/S execlusive","date time");
    parser.addOption(optionS);
    parser.addOption(optionM);
    parser.addOption(optionH);
    parser.addOption(optionP);
    parser.addOption(optionT);
    parser.setApplicationDescription("This is a simple Qt application to demonstrate command line argument parsing.");
    parser.addHelpOption();
    parser.addVersionOption();
    //时间单位都转成秒
    QMap<QString,int> convert = QMap<QString,int>();
    convert.insert("S",1);
    convert.insert("M",60);
    convert.insert("H",3600);
    PlayMusicThread thread = PlayMusicThread();
    // 解析命令行参数

    parser.process(a);
    // 如果需要，您可以获取其他选项的值，例如：
    foreach (QString option, parser.optionNames()) {
        qDebug()<<option<<":"<<parser.value(option);
    }


    QMediaPlayer player = QMediaPlayer();
    QDateTime now = QDateTime::currentDateTime();
    QStringList options = parser.optionNames();
    if(!options.contains("P")) {
        qWarning()<<"必选包含P选项";
        return -1;
    }
    QString musicPath = parser.value("P");
    QRegularExpression regular = QRegularExpression("T|M|H|S");
    QStringList timeOptions = options.filter(regular).toList();
    qInfo()<<timeOptions;
    if(timeOptions.isEmpty()) {
        qCritical()<<"必选有一个时间选项,要么S/M/H,要么T！";
        return -1;
    }
    if(timeOptions.contains("T") and timeOptions.size() >= 2) {
        qDebug() << "T选项不能和H/M/S选项一起用";
        return -1;
    } else if(timeOptions.contains("T") and timeOptions.size() == 1)
    {
        QString playTime = parser.value("T");
        qDebug()<<"play time:"<<playTime;
        QDateTime playDateTime = QDateTime::fromString(playTime,"yyyy-MM-dd hh:mm:ss");
        if(playDateTime.isNull() || !playDateTime.isValid()) {
            qDebug() << "T选项值格式错误!,格式必须是yyyy-MM-dd hh:mm:ss";
            return -1;
        } else {
            thread.setPlayTime(playDateTime);
            thread.setFile(musicPath);
            thread.start();
        }
    } else if(!timeOptions.contains("T")) {
        for(QString option:timeOptions) {
            QString value = parser.value(option);
            bool ok = false;
            int intValue = value.toInt(&ok);
            if(ok) {
                intValue = intValue*convert.value(option);
                now = now.addSecs(intValue);
            } else {
                qDebug()<<option<<"参数数值错误！";
                return -1;
            }
            qDebug()<<option<<":"<<intValue;
        }
        QFile file = QFile(musicPath);
        qDebug()<<"P:"+musicPath;
        if(QFile::exists(musicPath)) {
            //判断文件的mime类型是否为音频
            qDebug()<<"文件存在";
            QMimeType mimeType = QMimeDatabase().mimeTypeForFileNameAndData(musicPath,&file);
            qDebug()<<"name:"+mimeType.name()+",suffix name:"+mimeType.preferredSuffix();
            if(mimeType.name().contains("audio")) {
                thread.setFile(musicPath);
                qDebug()<<"播放时间:"<<now.toString("yyyy-MM-dd HH:mm:ss");
                thread.setPlayTime(now);
                thread.start();
            }
        }
    }
    return a.exec();
}
