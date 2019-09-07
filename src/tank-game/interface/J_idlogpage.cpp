//wriiten by JHN
#include "J_idlogpage.h"
#include "ui_idlogpage.h"
#include "J_mainwindow.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>
IdlogPage::IdlogPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IdlogPage)
{
    ui->setupUi(this);
}

IdlogPage::~IdlogPage()
{
    delete ui;
}

void IdlogPage::on_pushButton_2_clicked()
{
    emit return_page1();
}

void IdlogPage::on_pushButton_clicked()
{
    QString logID=ui->NameEdit->text();//登录账号
    QString logPassword=ui->PasswordEdit->text();//登录密码
    ui->NameEdit->setText("");
    ui->PasswordEdit->setText("");
    if(user1==logID){//输入与之前相同
        QMessageBox fail(QMessageBox::Warning,"登录失败","请勿重复登录",QMessageBox::Ok);
        fail.exec();
        return;
    }
    QFile login("login.txt");
    if(!login.open(QIODevice::ReadOnly)){
        //
        qDebug()<<"boom";
    }else {
        QDataStream in(&login);
        QString temp_id;
        QString temp_password;
         while(!in.atEnd()) {
            in>>temp_id>>temp_password;//从文件里获得用户名和密码
            if(logID==temp_id&&logPassword==temp_password){
                user1=temp_id;
                QMessageBox success(QMessageBox::Information,"欢迎您","登录成功！",QMessageBox::Ok);
                success.exec();
                emit log_succeed();
                emit success_ID(logID);
                login.close();
                return;
            }
        }
        login.close();
        QMessageBox fail(QMessageBox::Warning,"登录失败","账号或密码错误",QMessageBox::Ok);
        fail.exec();
    }
}
