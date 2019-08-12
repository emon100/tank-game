#include "mapmaker.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    Mapmaker w;

    w.show();

    return app.exec();
}
