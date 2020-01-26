#include "aye.h"

#include <QHBoxLayout>
#include <QNetworkDatagram>
#include <QByteArray>

aye::aye (QWidget *parent, aye_cfg *cfg) : QWidget(parent) {
    QVBoxLayout *l = new QVBoxLayout(this);
    l->addWidget(&this->ay);
    l->addWidget(&this->save);

    this->save.setText("Save");

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
    connect(&this->save, SIGNAL (released()),this, SLOT (save_handler()));
}

