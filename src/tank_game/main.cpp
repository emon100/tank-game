#include "map_maker/mapmaker.h"
#include "interface/J_mainwindow.h"
#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon("/resources/maker.ico"));

    MainWindow w;

    w.show();

    return app.exec();
}
