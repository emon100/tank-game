#include "mapmaker.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("/resources/maker.ico"));

    Mapmaker w;

    w.show();

    return app.exec();
}
