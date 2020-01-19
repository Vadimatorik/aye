#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>

#include "ay_reg.h"

struct aye_cfg {
    uint16_t port;
};

class aye : public QWidget {
Q_OBJECT

public:
    explicit aye (QWidget *parent, aye_cfg *cfg);

private slots:
    void new_connection ();
    void server_read ();
    void client_disconnected ();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

private:
    static const uint8_t CODE_AY_REG = 0;
    static const uint8_t CODE_AY_DATA = 1;

    struct __attribute__((packed)) socket_ay_msg_t {
        uint32_t time;
        uint8_t type;
        uint8_t data;
    };

private:
    QByteArray data;

private:
    ay_reg ay;

};