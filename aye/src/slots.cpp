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
    while (this->data.size() > sizeof(socket_ay_msg_t)) {
        socket_ay_msg_t *msg = reinterpret_cast<socket_ay_msg_t *>(this->data.data());
        if (msg->type == CODE_AY_REG) {
            this->ay.set_reg(msg->data);
        } else {
            this->ay.set_data(msg->data);
        }

        this->data.remove(0, sizeof(socket_ay_msg_t));
    }
}
