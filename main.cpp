#include <QCoreApplication>
#include <QSettings>
#include <QFile>
#include <QDir>
#include <QString>
#include "httplistener.h"
#include "httprequesthandler.h"
// #include "src/requestmapper.h"
#include "src/mywebsocketserver.h"

using namespace stefanfrings;

QString searchConfigFile() {
    QString binDir=QCoreApplication::applicationDirPath();
    QString appName=QCoreApplication::applicationName();
    QString fileName("webapp1.ini");

    QStringList searchList;
    searchList.append(binDir);
    searchList.append(binDir+"/etc");
    searchList.append(binDir+"/../etc");
    searchList.append(binDir+"/../"+appName+"/etc");     // for development with shadow build (Linux)
    searchList.append(binDir+"/../../"+appName+"/etc");  // for development with shadow build (Windows)
    searchList.append(QDir::rootPath()+"etc/opt");
    searchList.append(QDir::rootPath()+"etc");

    foreach (QString dir, searchList)
    {
        QFile file(dir+"/"+fileName);
        if (file.exists())
        {
            fileName=QDir(file.fileName()).canonicalPath();
            qDebug("Using config file %s",qPrintable(fileName));
            return fileName;
        }
    }

    // not found
    foreach (QString dir, searchList)
    {
        qWarning("%s/%s not found",qPrintable(dir),qPrintable(fileName));
    }
    qFatal("Cannot find config file %s",qPrintable(fileName));
    return nullptr;
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    // QString configFileName=searchConfigFile();
    // QSettings* listenerSettings = new QSettings(configFileName, QSettings::IniFormat, &a);
    // qDebug("config file loaded");

    QSettings* listenerSettings=
        new QSettings("C:/Users/makif/QtWebApp/MyFirstWebApp/etc/webapp1.ini",QSettings::IniFormat,&app);
    qDebug("config file loaded");

    listenerSettings->beginGroup("listener");
    // new stefanfrings::HttpListener(listenerSettings, new stefanfrings::HttpRequestHandler(&app), &app);

     // new HttpListener(listenerSettings,new HelloWorldController(&app),&app);

    // RequestMapper requestMapper;
    // new HttpListener(listenerSettings, new RequestMapper(&app), &app);

    MyWebSocketServer webSocketServer;
    // Set up code that uses the Qt event loop here.
    // Call a.quit() or a.exit() to quit the application.
    // A not very useful example would be including
    // #include <QTimer>
    // near the top of the file and calling
    // QTimer::singleShot(5000, &a, &QCoreApplication::quit);
    // which quits the application after 5 seconds.

    // If you do not need a running Qt event loop, remove the call
    // to a.exec() or use the Non-Qt Plain C++ Application template.

    return app.exec();
}
