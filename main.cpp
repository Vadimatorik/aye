#include <QApplication>

#include "aye.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

const char cli_help_msg[] =
    "Aye usage:\n"
    "    -p TCP port\n"
    "    -h\n"
    "    -? help\n"
    "\n";

void print_cli_help () {
    printf("%s", cli_help_msg);
}

int analysis_cmd_line (int argc, char *argv[], aye_cfg *cfg) {
    int c = 0;

    while ((c = getopt(argc, argv, "p:h?")) != -1) {
        switch (c) {
            case 'p':
                cfg->port = atoi(optarg);
                break;

            case 'h':
                print_cli_help();
                return EINVAL;

            case '?':
                print_cli_help();
                return EINVAL;

            default:
                perror("Argument not been recognized!\n");
                return EINVAL;
        }
    }

    return 0;
}

int check_cmd_line_param (aye_cfg *cfg) {
    if (cfg->port == 0) {
        perror("The port number is not specified!\n");
        return EINVAL;
    }

    return 0;
}


int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    aye_cfg e_cfg = {0};

    int rv = 0;
    if ((rv = analysis_cmd_line(argc, argv, &e_cfg)) != 0) {
        return rv;
    }

    if ((rv = check_cmd_line_param(&e_cfg)) != 0) {
        return rv;
    }

    aye *e = new aye(nullptr, &e_cfg);
    e->show();
    return app.exec();
}
