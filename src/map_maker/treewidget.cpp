#include <QFont>
#include <QImage>
#include <QHBoxLayout>
#include <QSpinBox>
#include "treewidget.h"
#include "ui_treewidget.h"
#include "mapmaker.h"

treewidget::treewidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::treewidget)
{
    ui->setupUi(this);
    //QImage imageiron(":/images/iron.bmp");
    QSpinBox *spinbox = new QSpinBox(this);
    QSlider *slider = new QSlider(Qt::Horizontal,this);
    spinbox->setRange(0,135);
    slider->setRange(0,135);

    connect(slider,&QSlider::valueChanged,spinbox,&QSpinBox::setValue);
    void (QSpinBox:: *spinBoxSignal)(int) = &QSpinBox::valueChanged;
    QObject::connect(spinbox, spinBoxSignal, slider, &QSlider::setValue);
    spinbox->setValue(35);

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(spinbox);
    layout->addWidget(slider);
    setLayout(layout);

}

treewidget::~treewidget()
{
    delete ui;
}

void treewidget::on_mainwindow_clicked()
{
    treewidget::fontsize++;
    ui->label1->setFont(QFont("Times",fontsize));
    this->update();
    MainWindow  *mainwindow = new MainWindow(this);
    mainwindow->show();
}

