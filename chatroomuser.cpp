#include "chatroomuser.h"


/*!
    \class ChatRoomUser
    \brief The ChatRoomUser implements the equility check operator,
        user address storage, and unique id.
*/
ChatRoomUser::ChatRoomUser(QObject *parent,
                           const QHostAddress &address) : QObject(parent),
                           address(address),
                           id(QUuid::createUuid())
{

}

bool ChatRoomUser::operator ==(const ChatRoomUser *b) const
{
    return this->id == b->id;
};

void ChatRoomUser::drainIODevice() const {
    QByteArray data = ((QIODevice* )QObject::sender())->readAll();
    emit ChatRoomUser::incomingMessage(QString::fromUtf8(data));
}
