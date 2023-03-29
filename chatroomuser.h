#ifndef CHATROOMUSER_H
#define CHATROOMUSER_H

#include <QObject>
#include <QHostAddress>
#include <QUuid>

class ChatRoomUser : public QObject
{
    Q_OBJECT

public:
    explicit ChatRoomUser(QObject *parent,
                          const QHostAddress &address);
    const QHostAddress address;
    const QUuid id;
    bool operator ==(const ChatRoomUser *b) const;

public slots:
    void drainIODevice() const;

signals:
    void incomingMessage(const QString &message) const;
};

#endif // CHATROOMUSER_H
