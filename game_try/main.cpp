#include "game_widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    game_widget w;
    w.show();

    return a.exec();
}
