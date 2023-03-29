#include <QObject>
#include <QTcpSocket>
#include "chatroomuser.h"

class SocketWrapper : public QObject
{
    Q_OBJECT
public:
    explicit SocketWrapper(QObject* parent, const ChatRoomUser *user);
    void write(const QByteArray &data, const QList<const ChatRoomUser *> to);
private:
    QTcpSocket *const socket;
    const ChatRoomUser *const m_user;
};
