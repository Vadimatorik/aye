#include "aye.h"

void aye::new_connection () {
    this->socket = server->nextPendingConnection();
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(server_read()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(client_disconnected()));
}

void aye::client_disconnected () {
    this->server->close();
}

void aye::server_read () {
    this->data.append(this->socket->read(this->socket->bytesAvailable()));
    while (this->data.size() > 2) {

        
        this->data.remove(0, 2);
    }
}
