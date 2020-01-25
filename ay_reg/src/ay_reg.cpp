#include "ay_reg.h"

ay_reg::ay_reg (QWidget *parent) : QWidget(parent) {
    QGridLayout *main_layout = new QGridLayout();
    this->setLayout(main_layout);

    for (int i = 0; i < this->REG_NUM; i++) {
        this->reg_name[i].setText("Reg " + QString::number(i));
        main_layout->addWidget(&this->reg_name[i], i + 1, 1);
        main_layout->addWidget(&this->reg_val[i], i + 1, 2);

        this->reg_val[i].setReadOnly(true);

        if (i != 7) {
            this->reg_val[i].setText("0x0");
        } else {
            this->reg_val[i].setText("0xFF");
        }
    }

    main_layout->setColumnMinimumWidth(2, 2);

    QString ch_param_name_cfg[] = {
        "Tone\nvalue",
        "Amplitude\nvalue",
        "Amplitude\nmode",
        "Noise\nmode",
        "Tone\nmode"
    };

    for (int i = 0; i < CH_PARAM_NUM; i++) {
        this->ch_param_name[i].setText(ch_param_name_cfg[i]);
        main_layout->addWidget(&this->ch_param_name[i], 1, i + 4);
    }

    const QString channel_name_cfg[] = {
        "Channel A",
        "Channel B",
        "Channel C"
    };

    for (int i = 0; i < CH_NUM; i++) {
        this->ch_name[i].setText(channel_name_cfg[i]);
        main_layout->addWidget(&this->ch_name[i], i + 2, 3);

        main_layout->addWidget(&this->ch_tone_val[i], i + 2, 4);
        main_layout->addWidget(&this->ch_amplitude_val[i], i + 2, 5);
        main_layout->addWidget(&this->ch_amplitude_mode[i], i + 2, 6);
        main_layout->addWidget(&this->ch_noise_mode[i], i + 2, 7);
        main_layout->addWidget(&this->ch_tone_mode[i], i + 2, 8);

        this->ch_tone_val[i].setReadOnly(true);
        this->ch_amplitude_val[i].setReadOnly(true);
        this->ch_amplitude_mode[i].setCheckable(false);
        this->ch_noise_mode[i].setCheckable(false);
        this->ch_tone_mode[i].setCheckable(false);
    }

    this->ch_noise_name.setText("Noise");
    main_layout->addWidget(&this->ch_noise_name, 5, 3);
    main_layout->addWidget(&this->noise_val, 5, 4);
    this->noise_val.setReadOnly(true);

    this->envelope_period_name.setText("Envelope period");
    main_layout->addWidget(&this->envelope_period_name, 6, 3);
    main_layout->addWidget(&this->envelope_period_val, 6, 4);
    this->envelope_period_val.setReadOnly(true);

    this->ch_exit[0].setText("OUT");
    main_layout->addWidget(&this->ch_exit[0], 7, 4);
    this->ch_exit[1].setText("IN");
    main_layout->addWidget(&this->ch_exit[1], 7, 5);

    this->ch_exit[2].setText("A");
    main_layout->addWidget(&this->ch_exit[2], 8, 3);
    this->ch_exit[3].setText("B");
    main_layout->addWidget(&this->ch_exit[3], 9, 3);

    for (int i = 0; i <= 1; i++) {
        main_layout->addWidget(&this->port_out_mode[i], i + 8, 4);
        main_layout->addWidget(&this->port_in_mode[i], i + 8, 5);

        this->port_out_mode[i].setCheckable(false);
        this->port_in_mode[i].setCheckable(false);
    }

    this->continue_mode_name.setText("Continue\nmode");
    main_layout->addWidget(&this->continue_mode_name, 11, 3);
    main_layout->addWidget(&this->continue_mode, 11, 4);
    this->continue_mode.setCheckable(false);

    this->attack_mode_name.setText("Attack\nmode");
    main_layout->addWidget(&this->attack_mode_name, 12, 3);
    main_layout->addWidget(&this->attack_mode, 12, 4);
    this->attack_mode.setCheckable(false);

    this->alternate_mode_name.setText("Alternate\nmode");
    main_layout->addWidget(&this->alternate_mode_name, 13, 3);
    main_layout->addWidget(&this->alternate_mode, 13, 4);
    this->alternate_mode.setCheckable(false);

    this->hold_mode_name.setText("Hold\nmode");
    main_layout->addWidget(&this->hold_mode_name, 14, 3);
    main_layout->addWidget(&this->hold_mode, 14, 4);
    this->hold_mode.setCheckable(false);

    this->update_ch_tone(channel_name::a);
    this->update_ch_tone(channel_name::b);
    this->update_ch_tone(channel_name::c);

    this->update_ch_amplitude(channel_name::a);
    this->update_ch_amplitude(channel_name::b);
    this->update_ch_amplitude(channel_name::c);

    this->update_ch_amplitude_mode(channel_name::a);
    this->update_ch_amplitude_mode(channel_name::b);
    this->update_ch_amplitude_mode(channel_name::c);

    this->update_noise();
    this->update_envelope_period();
    this->update_enable();
    this->envelope_shaper_cycle();
}

void ay_reg::update_ch_tone (channel_name ch) {
    uint8_t r_l = 0;
    uint8_t r_h = 0;
    uint16_t r = 0;

    switch (ch) {
        case channel_name::a:
            r_l = this->reg_val[0].text().toUInt(nullptr, 16);
            r_h = this->reg_val[1].text().toUInt(nullptr, 16);
            r = r_l | (r_h << 8u);
            this->ch_tone_val[0].setText("0x" + QString::number(r, 16));
            break;

        case channel_name::b:
            r_l = this->reg_val[2].text().toUInt(nullptr, 16);
            r_h = this->reg_val[3].text().toUInt(nullptr, 16);
            r = r_l | (r_h << 8u);
            this->ch_tone_val[1].setText("0x" + QString::number(r, 16));
            break;

        case channel_name::c:
            r_l = this->reg_val[4].text().toUInt(nullptr, 16);
            r_h = this->reg_val[5].text().toUInt(nullptr, 16);
            r = r_l | (r_h << 8u);
            this->ch_tone_val[2].setText("0x" + QString::number(r, 16));
            break;
    }
}

void ay_reg::update_ch_amplitude (channel_name ch) {
    uint16_t r = 0;

    switch (ch) {
        case channel_name::a:
            r = this->reg_val[10].text().toUInt(nullptr, 16);
            r &= 0b1111u;
            this->ch_amplitude_val[0].setText("0x" + QString::number(r, 16));
            break;

        case channel_name::b:
            r = this->reg_val[11].text().toUInt(nullptr, 16);
            r &= 0b1111u;
            this->ch_amplitude_val[1].setText("0x" + QString::number(r, 16));
            break;

        case channel_name::c:
            r = this->reg_val[12].text().toUInt(nullptr, 16);
            r &= 0b1111u;
            this->ch_amplitude_val[2].setText("0x" + QString::number(r, 16));
            break;
    }
}

void ay_reg::update_ch_amplitude_mode (channel_name ch) {
    uint16_t r = 0;

    switch (ch) {
        case channel_name::a:
            r = this->reg_val[10].text().toUInt(nullptr, 16);
            r &= 1u << 4u;
            this->ch_amplitude_mode[0].setChecked(static_cast<bool>(r));
            break;

        case channel_name::b:
            r = this->reg_val[11].text().toUInt(nullptr, 16);
            r &= 1u << 4u;
            this->ch_amplitude_mode[1].setChecked(static_cast<bool>(r));
            break;

        case channel_name::c:
            r = this->reg_val[12].text().toUInt(nullptr, 16);
            r &= 1u << 4u;
            this->ch_amplitude_mode[2].setChecked(static_cast<bool>(r));
            break;
    }
}

void ay_reg::update_noise () {
    uint8_t val = this->reg_val[6].text().toUInt(nullptr, 16);
    val &= 0b11111u;
    this->noise_val.setText("0x" + QString::number(val, 16));
}

void ay_reg::update_envelope_period () {
    uint8_t r_l = this->reg_val[13].text().toUInt(nullptr, 16);
    uint8_t r_h = this->reg_val[14].text().toUInt(nullptr, 16);
    uint16_t r = r_l | (r_h << 8u);
    this->envelope_period_val.setText("0x" + QString::number(r, 16));
}

void ay_reg::update_enable () {
    uint8_t r = this->reg_val[7].text().toUInt(nullptr, 16);
    this->ch_tone_mode[0].setChecked(static_cast<bool>(!(r & (1u << 0u))));
    this->ch_tone_mode[1].setChecked(static_cast<bool>(!(r & (1u << 1u))));
    this->ch_tone_mode[2].setChecked(static_cast<bool>(!(r & (1u << 2u))));

    this->ch_noise_mode[0].setChecked(static_cast<bool>(!(r & (1u << 3u))));
    this->ch_noise_mode[1].setChecked(static_cast<bool>(!(r & (1u << 4u))));
    this->ch_noise_mode[2].setChecked(static_cast<bool>(!(r & (1u << 5u))));

    this->port_in_mode[0].setChecked(static_cast<bool>(r & (1u << 6u)));
    this->port_in_mode[1].setChecked(static_cast<bool>(r & (1u << 6u)));

    this->port_out_mode[0].setChecked(static_cast<bool>(!(r & (1u << 7u))));
    this->port_out_mode[1].setChecked(static_cast<bool>(!(r & (1u << 7u))));
}

void ay_reg::envelope_shaper_cycle () {
    uint8_t r = this->reg_val[15].text().toUInt(nullptr, 16);
    this->hold_mode.setChecked(static_cast<bool>(r & (1u << 0u)));
    this->alternate_mode.setChecked(static_cast<bool>(r & (1u << 1u)));
    this->attack_mode.setChecked(static_cast<bool>(r & (1u << 2u)));
    this->continue_mode.setChecked(static_cast<bool>(r & (1u << 3u)));
}

void ay_reg::set_reg (uint8_t reg) {
    QPalette palette;
    palette.setColor(QPalette::Base, Qt::white);
    palette.setColor(QPalette::Text, Qt::black);

    this->reg_val[this->cur_reg].setPalette(palette);

    this->cur_reg = reg;

    if (reg < this->REG_NUM) {
        palette.setColor(QPalette::Base, Qt::green);
        this->reg_val[this->cur_reg].setPalette(palette);
    }
}

void ay_reg::set_data (uint8_t data) {
    if (this->cur_reg < this->REG_NUM) {
        this->reg_val[this->cur_reg].setText("0x" + QString::number(data, 16));

        switch (this->cur_reg) {
            case 0:
            case 1:
                this->update_ch_tone(channel_name::a);
                break;

            case 2:
            case 3:
                this->update_ch_tone(channel_name::a);
                break;

            case 4:
            case 5:
                this->update_ch_tone(channel_name::a);
                break;

            case 6:
                this->update_noise();
                break;

            case 7:
                this->update_enable();
                break;

            case 10:
                this->update_ch_amplitude(channel_name::a);
                this->update_ch_amplitude_mode(channel_name::a);
                break;

            case 11:
                this->update_ch_amplitude(channel_name::b);
                this->update_ch_amplitude_mode(channel_name::b);
                break;

            case 12:
                this->update_ch_amplitude(channel_name::c);
                this->update_ch_amplitude_mode(channel_name::c);
                break;

            case 13:
            case 14:
                this->update_envelope_period();
                break;

            case 15:
                this->envelope_shaper_cycle();
                break;
        }
    }
}
