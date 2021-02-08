#include "interface/J_mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    MainWindow w;
    w.setWindowIcon(QIcon("/resources/maker.ico"));
    w.setWindowTitle("坦克大战");

    w.show();

    return app.exec();
}
