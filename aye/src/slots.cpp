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
    while (this->data.size() > sizeof(socket_ay_msg)) {
        socket_ay_msg *msg = reinterpret_cast<socket_ay_msg *>(this->data.data());
        track.append(*msg);

        if (msg->type == CODE_AY_REG) {
            this->ay.set_reg(msg->data);
        } else {
            this->ay.set_data(msg->data);
        }

        this->data.remove(0, sizeof(socket_ay_msg));
    }
}


void aye::save_handler () {
    QString f_name = QFileDialog::getSaveFileName(this, tr("Save dump file"), "", "");
    if (f_name.isEmpty()) {
        return;
    }

    QFile f_psg(f_name + ".psg");
    if (!f_psg.open(QIODevice::WriteOnly)) {
        return;
    }

    QFile f_log(f_name + ".log");
    if (!f_log.open(QIODevice::WriteOnly | QIODevice::Text)) {
        return;
    }

    QTextStream out(&f_log);

    psg_handler h = {0};
    h.sign[0] = 'P';
    h.sign[1] = 'S';
    h.sign[2] = 'G';
    h.marker = this->PSG_FILE_MARKER_FORMAT;
    h.version = 0;

    QByteArray psg_data;
    psg_data.append(reinterpret_cast<const char *>(&h), sizeof(h));

    uint32_t cur_time = this->track[0].time;
    uint8_t cur_reg = 0xFF;

    for (socket_ay_msg item : this->track) {
        if (item.type == CODE_AY_REG) {
            cur_reg = item.data;
        } else if (cur_reg < 18) {
            if (item.time - cur_time > 10) {
                uint32_t d_time = item.time - cur_time;
                uint32_t pause_count = (d_time + 10)/20;
                if (pause_count < 4) {
                    out << "D time: " << QString::number(d_time) << endl;
                    for (int i = 0; i < pause_count; i++) {
                        psg_data.append(PSG_FILE_MARKER_INTERRUPT);
                    }
                } else {
                    uint32_t block_pause_count = pause_count/4;
                    psg_data.append(PSG_FILE_MARKER_SKIP);
                    psg_data.append(block_pause_count);

                    for (int i = 0; i < pause_count%4; i++) {
                        psg_data.append(PSG_FILE_MARKER_INTERRUPT);
                    }
                }

                cur_time = item.time;
            }

            psg_data.append(cur_reg);
            psg_data.append(item.data);

            out << "Time: " << QString::number(item.time) << "\t";
            out << "R: " << QString::number(cur_reg, 16) << "\t";
            out << "D: " << QString::number(item.data, 16);
            out << endl;
        }
    }

    f_psg.write(psg_data);
    f_psg.close();
    out.flush();
    f_log.close();
}