#include "aye.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

aye::aye (QWidget *parent, aye_cfg *cfg) : QWidget(parent) {
    QHBoxLayout *l = new QHBoxLayout(this);
    l->addWidget(&this->ay);

    if ((this->server = new QTcpServer(this)) == nullptr) {
        exit(ENOMEM);
    }

    if ((this->socket = new QTcpSocket(this)) == nullptr) {
        exit(ENOMEM);
    };

    if (!this->server->listen(QHostAddress::LocalHost, cfg->port)) {
        exit(errno);
    }

    connect(this->server, SIGNAL(newConnection()), this, SLOT(new_connection()));
}

