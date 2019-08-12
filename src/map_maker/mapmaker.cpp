#include "mapmaker.h"
#include "mymap.h"
#include "ui_mapmaker.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>
#include <QDebug>

Mapmaker::Mapmaker(QWidget *parent) :
    QMainWindow(parent),
    plane(),
    cursor_status(NONE),
    ui(new Ui::Mapmaker)
{
    ui->setupUi(this);
    init_table();

    ui->statusbar->showMessage("View mode");
    ui->maptable->setShowGrid(true); //隐藏分割线


    QPainter painter(this);
    connect(ui->Open,&QAction::triggered,this,&Mapmaker::open);
    connect(ui->Save,&QAction::triggered,this,&Mapmaker::save);
    connect(ui->Quit,&QAction::triggered,this,&Mapmaker::close);


    //click to change into view mode
    connect(ui->ViewButton,&QPushButton::clicked,this,&Mapmaker::change_mode<NONE>);

    //click to change into different edit mode
    //I think its better to put edit mode into a function.
    connect(ui->AirButton,  &QPushButton::clicked,this,&Mapmaker::change_mode<AIR>);
    connect(ui->IronButton, &QPushButton::clicked,this,&Mapmaker::change_mode<IRON>);
    connect(ui->BrickButton,&QPushButton::clicked,this,&Mapmaker::change_mode<BRICK>);
    connect(ui->Base1Button,&QPushButton::clicked,this,&Mapmaker::change_mode<BASE1>);
    connect(ui->Base2Button,&QPushButton::clicked,this,&Mapmaker::change_mode<BASE2>);

    //click to edit mapplane
    connect(ui->maptable,&QTableWidget::cellClicked,this,&Mapmaker::set_cell_by_cursor_status);


}

void Mapmaker::set_cell_by_cursor_status(int row,int column){
    set_cell(row,column,this->cursor_status);
}
void Mapmaker::open(){
    QString path;
    //dialog
    Mapmaker *window_to_be_use = this;
    path = QFileDialog::getOpenFileName(this,
                                        tr("Open file"),
                                        ".",
                                        tr("Text Files(*.map)"));

    if(path.isEmpty()){
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }
    else{//OK
        //Ask if open in new Window
    if(QMessageBox::Yes==QMessageBox::warning(this,
                                              tr("Warning!"),
                                              tr("Open in this window might lead to data lost.\nOpen in a new window?"),
                                              QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)){
        window_to_be_use = new Mapmaker();
        window_to_be_use->show();
    }
    else {
        //do nothing
    }

    window_to_be_use->open_with_path(path);
    return;
    }

}
void Mapmaker::open_with_path(QString path){
        QFile file(path);
            if (!file.open(QIODevice::ReadOnly )) {
                QMessageBox::warning(this, tr("Read File"),
                                     tr("Cannot open file:\n%1").arg(path));
                return;
            }else{
                QDataStream in(&file);
                in.readRawData(reinterpret_cast<char *>(&plane),sizeof(plane));
                file.close();
                qDebug()<<plane.base1.x();
                init_table();
        }
        return;
}

//TODO
void Mapmaker::save(){
    QString  path = QFileDialog::getSaveFileName(this,
                                                 tr("Open File"),
                                                 ".",
                                                 tr("Text Files(*.map)"));
    if(path.isEmpty()) {
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    } else {
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly )) {
            QMessageBox::warning(this, tr("Write File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }
        QDataStream out(&file);
        out.writeRawData(reinterpret_cast<char *>(&plane),sizeof (plane));
        file.close();
    }
}

void Mapmaker::close(){
    if(QMessageBox::Yes==QMessageBox::question(this,
                                               tr("Quit?"),
                                               tr("Are you sure to quit?"),
                                               QMessageBox::Yes|QMessageBox::No,QMessageBox::No))
    {
        QWidget::close();
    }
    else return;
}

//TOTOTOTOTOTOTTODODODODODODDO:complete mapobject type
void Mapmaker::set_cell(int row, int column, MAP_OBJECT sta){//change the Table and also the map behind
    QLabel *cell;
    switch (sta) {
    case NONE        : return;
    case AIR  : cell = nullptr;plane.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)]=AIR;break;
    case BRICK: cell = new QLabel("Brick");plane.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)]=BRICK;break;
    case IRON : cell = new QLabel("Iron");cell->setPixmap(QPixmap::fromImage(IronImg));plane.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)]=IRON;break;
    case BASE1: cell = new QLabel("Base1");cell->setPixmap(QPixmap::fromImage(Base1Img));ui->maptable->removeCellWidget(plane.base1.x(),plane.base1.y());plane.base1.setX(row);plane.base1.setY(column);break;
    case BASE2: cell = new QLabel("Base2");cell->setPixmap(QPixmap::fromImage(Base2Img));ui->maptable->removeCellWidget(plane.base2.x(),plane.base2.y());plane.base2.setX(row);plane.base2.setY(column);break;
    }
    plane.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)]=static_cast<MAP_OBJECT>(sta);
    ui->maptable->setCellWidget(row,column,cell);
    ui->maptable->setShowGrid(true); //隐藏分割线
}



void Mapmaker::init_table(){
    ui->maptable->clear();
    ui->maptable->setColumnCount(mapsize);
    ui->maptable->setRowCount(mapsize);
    ui->maptable->verticalHeader()->setVisible(false); //隐藏列表头
    ui->maptable->horizontalHeader()->setVisible(false); //隐藏行表头
    for(int i=0;i<mapsize;++i){
        ui->maptable->setColumnWidth(i,32);
        ui->maptable->setRowHeight(i,32);
    }
    set_cell(plane.base1.x(),plane.base1.y(),BASE1);
    set_cell(plane.base2.x(),plane.base2.y(),BASE2);
    for (size_t i=0;i<mapsize;++i) {
        for(size_t j=0;j<mapsize;++j){
            set_cell(static_cast<int>(i),static_cast<int>(j),(plane.mapplane[i][j]));
        }
    }
}

//更换模式的函数模板
template<MAP_OBJECT STA>
void Mapmaker::change_mode(){
    ui->maptable->setShowGrid(true);ui->statusbar->showMessage("Edit mode");cursor_status=STA;
}

template<>
void Mapmaker::change_mode<NONE>(){
    ui->maptable->setShowGrid(false);ui->statusbar->showMessage("View mode");cursor_status=NONE;
}

Mapmaker::~Mapmaker()
{
    delete ui;
}
