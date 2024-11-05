#include "mywebsocketserver.h"

MyWebSocketServer::MyWebSocketServer(QObject *parent) : QObject(parent) {
    m_webSocketServer = new QWebSocketServer(QStringLiteral("WebSocket Server"),
                                             QWebSocketServer::NonSecureMode,
                                             this);

    // Указываем конкретный IP-адрес и порт
    QHostAddress address("192.168.31.190");
    if (m_webSocketServer->listen(address, 8090)) {
        qDebug() << "WebSocket сервер запущен на" << address.toString() << "и порту 8090";
        connect(m_webSocketServer, &QWebSocketServer::newConnection, this, &MyWebSocketServer::onNewConnection);
    } else {
        qDebug() << "Не удалось запустить WebSocket сервер на" << address.toString() << "и порту 8090";
    }
}

MyWebSocketServer::~MyWebSocketServer() {
    m_webSocketServer->close();
    qDeleteAll(m_clients.begin(), m_clients.end());
}

void MyWebSocketServer::onNewConnection() {
    QWebSocket *socket = m_webSocketServer->nextPendingConnection();

    connect(socket, &QWebSocket::textMessageReceived, this, &MyWebSocketServer::processTextMessage);
    connect(socket, &QWebSocket::disconnected, this, &MyWebSocketServer::socketDisconnected);

    m_clients << socket;
    qDebug() << "Новое WebSocket соединение установлено";
}

void MyWebSocketServer::processTextMessage(const QString &message) {
    qDebug() << "Получено сообщение:" << message;

    // Пример: отправляем сообщение обратно всем клиентам
    for (QWebSocket *client : qAsConst(m_clients)) {
        if (client->isValid()) {
            client->sendTextMessage("Echo: " + message);
        }
    }
}

void MyWebSocketServer::socketDisconnected() {
    QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
    if (socket) {
        m_clients.removeAll(socket);
        socket->deleteLater();
        qDebug() << "WebSocket соединение закрыто";
    }
}
