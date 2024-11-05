#ifndef MYWEBSOCKETSERVER_H
#define MYWEBSOCKETSERVER_H

#include <QWebSocketServer>
#include <QWebSocket>
#include <QObject>

class MyWebSocketServer : public QObject {
    Q_OBJECT
public:
    explicit MyWebSocketServer(QObject *parent = nullptr);
    ~MyWebSocketServer();

public slots:
    void onNewConnection();
    void processTextMessage(const QString &message);
    void socketDisconnected();

private:
    QWebSocketServer *m_webSocketServer;
    QList<QWebSocket *> m_clients;
};

#endif // MYWEBSOCKETSERVER_H
