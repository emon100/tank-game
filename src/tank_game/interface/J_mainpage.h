//wriiten by JHN
#ifndef MAINPAGE_H
#define MAINPAGE_H

#include <QWidget>

namespace Ui {
class MainPage;
}

class MainPage : public QWidget
{
    Q_OBJECT

public:
    explicit MainPage(QWidget *parent = nullptr);
    ~MainPage();
signals:
    void turn_page();
    void exit_page();
private slots:
    void on_Start_clicked();

    void on_Exit_clicked();

    void on_goto_mapmaker_clicked();

private:
    Ui::MainPage *ui;
    MainPage *main;
};

#endif // MAINPAGE_H
