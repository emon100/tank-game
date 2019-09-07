//wriiten by JHN
#include "J_idregister.h"
#include "ui_idregister.h"
#include "J_mainwindow.h"
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <QDebug>

IDregister::IDregister(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::IDregister)
{
    ui->setupUi(this);
}

IDregister::~IDregister()
{
    delete ui;
}

void IDregister::on_pushButton_2_clicked()
{
    emit return_page1();
}

void IDregister::on_pushButton_clicked()
{
    QString new_ID=ui->NameEdit->text();//注册账号
    QString new_Password=ui->PasswordEdit->text();//注册密码
    if(new_ID==""||new_Password==""){
        QMessageBox fail(QMessageBox::Warning,"注册失败","账号或密码为空",QMessageBox::Ok);
        fail.exec();
        ui->NameEdit->setText("");
        ui->PasswordEdit->setText("");
        return;
    }
    QFile reg("login.txt");
    if(!reg.open(QIODevice::ReadOnly)){//文件不存在
        //写新文件
        if(!reg.open(QIODevice::WriteOnly)){
            //
            qDebug()<<"Boom";
        }else{//
            QDataStream out(&reg);
            out<<new_ID<<new_Password;
            reg.close();
            QMessageBox success(QMessageBox::Information,"注册成功","注册成功",QMessageBox::Ok);
            success.exec();
            ui->NameEdit->clear();
            ui->PasswordEdit->clear();
            emit return_login();
            return;
        }
    }else{//文件存在,判断重复
        QDataStream in(&reg);
        QString temp_id;
        QString temp_password;

        while (!in.atEnd()) {
            in>>temp_id>>temp_password;
            if(new_ID==temp_id){
                QMessageBox fail(QMessageBox::Warning,"注册失败","请勿重复注册",QMessageBox::Ok);
                fail.exec();
                ui->NameEdit->clear();
                ui->PasswordEdit->clear();
                reg.close();
                return;
            }
        }
        reg.close();
        if(!reg.open(QIODevice::Append)){
            //
            qDebug()<<"Boom";
        }else{//
            QDataStream out(&reg);
            out<<new_ID<<new_Password;
            reg.close();
            QMessageBox success(QMessageBox::Information,"注册成功","注册成功",QMessageBox::Ok);
            success.exec();
            ui->NameEdit->clear();
            ui->PasswordEdit->clear();
            emit return_login();
            return;
        }

    }

}
