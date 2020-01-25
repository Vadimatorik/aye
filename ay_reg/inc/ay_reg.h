#pragma once

#include <QApplication>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QCheckBox>
#include <QString>

class ay_reg : public QWidget {
public:
    ay_reg (QWidget *parent = nullptr);

public:
    void set_reg (uint8_t reg);
    void set_data (uint8_t data);

private:
    enum class channel_name : uint8_t {
        a, b, c
    };

private:
    void update_ch_tone (channel_name ch);
    void update_ch_amplitude (channel_name ch);
    void update_ch_amplitude_mode (channel_name ch);

    void update_enable ();
    void envelope_shaper_cycle ();
    void update_noise ();
    void update_envelope_period ();

private:
    const static uint8_t REG_NUM = 18;
    const static uint8_t CH_NUM = 3;
    const static uint8_t PORT_NUM = 2;
    const static uint8_t CH_PARAM_NUM = 5;
    const static uint8_t EXIT_NUM = 4;

private:
    uint8_t cur_reg = 0;

private:
    QLabel reg_name[REG_NUM];
    QLineEdit reg_val[REG_NUM];
    QLineEdit ch_tone_val[CH_NUM];
    QLineEdit ch_amplitude_val[CH_NUM];
    QLineEdit noise_val;

    QCheckBox ch_amplitude_mode[CH_NUM];
    QCheckBox ch_noise_mode[CH_NUM];
    QCheckBox ch_tone_mode[CH_NUM];

    QCheckBox port_out_mode[PORT_NUM];
    QCheckBox port_in_mode[PORT_NUM];

    QLabel envelope_period_name;
    QLineEdit envelope_period_val;

    QCheckBox continue_mode;
    QCheckBox attack_mode;
    QCheckBox alternate_mode;
    QCheckBox hold_mode;

    QLabel ch_param_name[CH_PARAM_NUM];
    QLabel ch_name[CH_NUM];
    QLabel ch_noise_name;
    QLabel ch_exit[EXIT_NUM];

    QLabel continue_mode_name;
    QLabel attack_mode_name;
    QLabel alternate_mode_name;
    QLabel hold_mode_name;

};
