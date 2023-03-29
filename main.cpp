#include "mainwindow.h"
#include <QTcpSocket>
#include <QApplication>
#include "chatroom.h"
#include "chatroomtcpmiddleware.h"

/*
 *  Chatroom is a stupid historyless internet chat server.
 *  Written as a solutions for the one of the Evil Empire's enterprises.
 *
 *  Copyleft (c) xerasovanon@gmail.com
 *  Forbidden for war, terror, or occupation use.
 *  ! Free Alexey Navalny !
 *  Support Ukraine. Stop terror and occupation.
 *  Listen reggae! ;) Jazz Rul3zz!
 */

QCoreApplication* createApplication(int &argc, char *argv[])
{
    for (int i = 1; i < argc; ++i) {
        if (!strcmp(argv[i], "-no-gui"))
            return new QCoreApplication(argc, argv);
    }
    return new QApplication(argc, argv);
}

int main(int argc, char* argv[])
{
    uint port = 1701; // The day of Alexey Navalny emprisonment

    std::unique_ptr<QCoreApplication> app(createApplication(argc, argv));
    ChatRoom chatRoom(app.get());
    ChatRoomTcpMiddleware middleware(app.get());

    // When client connects to the chat server, the user is created and
    // the Chatroom's notified
    QObject::connect(&middleware, &ChatRoomTcpMiddleware::connectionAccepted,
                     &chatRoom, &ChatRoom::userJoin);

    // When Chatroom send's broadcast message, the middleware sends the message
    // to all it's users
    QObject::connect(&chatRoom, &ChatRoom::outgoingBroadcastMessage,
                     &middleware, &ChatRoomTcpMiddleware::broadcastMessage);

    middleware.listen(port);

    if (qobject_cast<QApplication *>(app.get())) {
       MainWindow w;
       w.show();
       return app->exec();
    } else {
       // start non-GUI version...
    }

    return app->exec();
}
