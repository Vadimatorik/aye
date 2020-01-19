#include <QApplication>

#include "aye.h"

int main (int argc, char *argv[]) {
    QApplication app(argc, argv);
    aye *e = new aye();
    e->show();
    return app.exec();
}
