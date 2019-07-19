#ifndef LOGINDIG_H
#define LOGINDIG_H

#include <QDialog>

namespace Ui {
class LoginDig;
}

class LoginDig : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDig(QWidget *parent = nullptr);
    ~LoginDig();

private:
    Ui::LoginDig *ui;
};

#endif // LOGINDIG_H
