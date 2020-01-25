#include "ay_reg.h"

ay_reg::ay_reg (QWidget *parent) : QWidget(parent) {
    QGridLayout *main_layout = new QGridLayout();
    this->setLayout(main_layout);

    for (int i = 0; i < REG_NUM; i++) {
        this->reg_name[i].setText("Reg " + QString::number(i));
        main_layout->addWidget(&this->reg_name[i], i + 1, 1);
        main_layout->addWidget(&this->reg_val[i], i + 1, 2);
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


    QString channel_name_cfg[] = {
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
    }

    this->ch_noise.setText("Noise");
    main_layout->addWidget(&this->ch_noise, 5, 3);
    main_layout->addWidget(&this->ch_noise_val, 5, 4);

    this->ch_exit[0].setText("OUT");
    main_layout->addWidget(&this->ch_exit[0], 6, 4);
    this->ch_exit[1].setText("IN");
    main_layout->addWidget(&this->ch_exit[1], 6, 5);

    this->ch_exit[2].setText("A");
    main_layout->addWidget(&this->ch_exit[2], 7, 3);
    this->ch_exit[3].setText("B");
    main_layout->addWidget(&this->ch_exit[3], 8, 3);

    for (int i = 0; i <= 1; i++) {
        main_layout->addWidget(&this->port_out_mode[i], i + 7, 4);
        main_layout->addWidget(&this->port_in_mode[i], i + 7, 5);
    }

    this->continue_mode_name.setText("Continue\nmode");
    main_layout->addWidget(&this->continue_mode_name, 10, 3);
    main_layout->addWidget(&this->continue_mode, 10, 4);

    this->attack_mode_name.setText("Attack\nmode");
    main_layout->addWidget(&this->attack_mode_name, 11, 3);
    main_layout->addWidget(&this->attack_mode, 11, 4);

    this->alternate_mode_name.setText("Alternate\nmode");
    main_layout->addWidget(&this->alternate_mode_name, 12, 3);
    main_layout->addWidget(&this->alternate_mode, 12, 4);

    this->hold_mode_name.setText("Hold\nmode");
    main_layout->addWidget(&this->hold_mode_name, 13, 3);
    main_layout->addWidget(&this->hold_mode, 13, 4);
}

void ay_reg::set_reg (uint8_t reg) {
    QPalette palette;
    palette.setColor(QPalette::Base,Qt::white);
    palette.setColor(QPalette::Text,Qt::black);

    this->reg_val[this->cur_reg].setPalette(palette);

    this->cur_reg = reg;

    if (reg < this->REG_NUM) {
        palette.setColor(QPalette::Base,Qt::green);
        this->reg_val[this->cur_reg].setPalette(palette);
    }
}

void ay_reg::set_data (uint8_t data) {
    if (this->cur_reg < this->REG_NUM) {
        this->reg_val[this->cur_reg].setText("0x" + QString::number(data, 16));
    }
}