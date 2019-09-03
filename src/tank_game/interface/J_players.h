//wriiten by JHN
#ifndef PLAYERS_H
#define PLAYERS_H

#include <QWidget>

namespace Ui {
class Players;
}

class Players : public QWidget
{
    Q_OBJECT

public:
    explicit Players(QWidget *parent = nullptr);
    ~Players();
signals:
    void Game_begin(QString,QString);
    void turn_page3();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Players *ui;
};

#endif // PLAYERS_H
