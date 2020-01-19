#include "aye.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

aye::aye (QWidget *parent) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout(this);
    l->addWidget(&this->ay);

    this->server = new QTcpServer(this);

    this->socket = new QTcpSocket(this);


    if (!this->server->listen(QHostAddress::LocalHost, 58000)) {
        exit(errno);
    }

    connect(this->server, SIGNAL(newConnection()), this, SLOT(new_connection()));
}

