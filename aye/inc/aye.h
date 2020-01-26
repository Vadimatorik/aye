#pragma once

#include <QWidget>
#include <QTcpServer>
#include <QByteArray>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QList>
#include <QTcpSocket>
#include <QPushButton>
#include <QFileDialog>

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
    void save_handler ();

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

private:
    static const uint8_t CODE_AY_REG = 0;
    static const uint8_t CODE_AY_DATA = 1;

    struct __attribute__((packed)) socket_ay_msg {
        uint32_t time;
        uint8_t type;
        uint8_t data;
    };

private:
    const uint8_t PSG_FILE_MARKER_FORMAT = 0x1A;
    const uint8_t PSG_FILE_MARKER_INTERRUPT = 0xFF;
    const uint8_t PSG_FILE_MARKER_SKIP = 0xFE;
    const uint8_t PSG_FILE_MARKER_END_TRACK = 0xFD;

    struct __attribute__((__packed__)) psg_handler {
        uint8_t sign[3];
        uint8_t marker;
        uint8_t version;
        uint8_t interrupt;
        uint8_t padding[10];
    };

    QVector<socket_ay_msg> track;

private:
    QByteArray data;

private:
    ay_reg ay;
    QPushButton save;

};