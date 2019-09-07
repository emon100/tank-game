//wriiten by JHN
#ifndef CURRENTPLAYER_H
#define CURRENTPLAYER_H

#include <QWidget>

namespace Ui {
class CurrentPlayer;
}

class CurrentPlayer : public QWidget
{
    Q_OBJECT

public:
    explicit CurrentPlayer(QWidget *parent = nullptr);
    ~CurrentPlayer();
signals:
    void Game_begin(QString,QString);
    void turn_page1();
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::CurrentPlayer *ui;
};

#endif // CURRENTPLAYER_H
