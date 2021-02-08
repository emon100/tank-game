#include "mapmaker.h"
#include "mymap.h"
#include "ui_mapmaker.h"
#include <QMessageBox>
#include <QPushButton>
#include <QFile>
#include <QFileDialog>
#include <QDataStream>

Mapmaker::Mapmaker(QWidget *parent) :
        QMainWindow(parent),
        map(),
        cursor_status(NONE),
        ui(new Ui::Mapmaker)
{
    ui->setupUi(this);
    draw_table();

    ui->statusbar->showMessage("View mode");
    ui->maptable->setShowGrid(true); //隐藏分割线


    connect(ui->New,&QAction::triggered,this,&Mapmaker::add_new);
    connect(ui->Open,&QAction::triggered,this,&Mapmaker::open);
    connect(ui->Save,&QAction::triggered,this,&Mapmaker::save);
    connect(ui->Quit,&QAction::triggered,this,&Mapmaker::close);

    connect(ui->Redo,&QAction::triggered,this,&Mapmaker::redo);
    connect(ui->Undo,&QAction::triggered,this,&Mapmaker::undo);

    connect(ui->Help,&QAction::triggered,this,&Mapmaker::help);

    //click to change into view mode
    connect(ui->ViewButton,&QPushButton::clicked,this,&Mapmaker::change_mode<NONE>);

    //click to change into different edit mode
    //I think its better to put edit mode into a function.
    connect(ui->AirButton,   &QPushButton::clicked,this,&Mapmaker::change_mode<AIR>);
    connect(ui->IronButton,  &QPushButton::clicked,this,&Mapmaker::change_mode<IRON>);
    connect(ui->BrickButton, &QPushButton::clicked,this,&Mapmaker::change_mode<BRICK>);
    connect(ui->Base1Button, &QPushButton::clicked,this,&Mapmaker::change_mode<BASE1>);
    connect(ui->Base2Button, &QPushButton::clicked,this,&Mapmaker::change_mode<BASE2>);
    connect(ui->Spawn1Button,&QPushButton::clicked,this,&Mapmaker::change_mode<SPAWN1>);
    connect(ui->Spawn2Button,&QPushButton::clicked,this,&Mapmaker::change_mode<SPAWN2>);

    //click or drag to edit mapplane
    connect(ui->maptable,&QTableWidget::cellClicked,this,&Mapmaker::set_cell_by_cursor_status);
    connect(ui->maptable,&QTableWidget::cellEntered,this,&Mapmaker::set_cell_by_cursor_status);
    //double click to edit spawn;
    connect(ui->maptable,&QTableWidget::cellDoubleClicked,this,&Mapmaker::loop_spawn_direction);


}

void Mapmaker::loop_spawn_direction(int row,int column){
    //first check if the cell is spawn ,then change direction one by one in loop
    //finally show statusbar message;
    QPoint temp(row,column);
    DIRECTION now;
    if(map.spawn1==temp){
        map.spawn1_direction=static_cast<DIRECTION>((static_cast<int>(map.spawn1_direction)+1)%4);
        now=map.spawn1_direction;
    }else if(map.spawn2==temp){
        map.spawn2_direction=static_cast<DIRECTION>(static_cast<int>((map.spawn2_direction)+1)%4);
        now=map.spawn2_direction;
    }else {
        return;
    }
    switch (now) {
    case EAST : ui->statusbar->showMessage("The spawn is now facing the east.");break;
    case SOUTH: ui->statusbar->showMessage("The spawn is now facing the south.");break;
    case WEST : ui->statusbar->showMessage("The spawn is now facing the west.");break;
    case NORTH: ui->statusbar->showMessage("The spawn is now facing the north.");break;
    }
}

bool Mapmaker::enable_cursor(MAP_OBJECT sta){
    if(sta==cursor_status)//当前光标与物品一致无需编辑
        return false;
    else {
        switch (sta){
        case BASE1 :ui->statusbar->showMessage("Warning: A Base1 is required on the map!"); return false;
        case BASE2 :ui->statusbar->showMessage("Warning: A Base2 is required on the map!"); return false;
        case SPAWN1:ui->statusbar->showMessage("Warning: A Spawn1 is required on the map!");return false;
        case SPAWN2:ui->statusbar->showMessage("Warning: A Spawn2 is required on the map!");return false;
        default:break;
        }
        return true;
    }
}

void Mapmaker::set_cell_by_cursor_status(int row,int column){//Controller
    //To make sure the map has 2 base and 2 spawn,and make sure no redundant changes happen.
    if(cursor_status!=NONE&&enable_cursor(map.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)])){
        Undostack.push(map);
        set_cell(row,column,cursor_status);
    }else{
        //do nothing
    }
}

void Mapmaker::set_cell(int row, int column, MAP_OBJECT sta){//Model:change the Table and also the map behind
    QLabel *cell=nullptr;

    switch (sta) {
    case NONE  : return;
    case AIR   : cell = nullptr;break;
    case BRICK : cell = new QLabel("Brick",this) ;cell->setPixmap(QPixmap::fromImage(BrickImg));break;
    case IRON  : cell = new QLabel("Iron",this)  ;cell->setPixmap(QPixmap::fromImage(IronImg)) ;break;
        //Bases and spawns has to keep the only one;
    case BASE1 : cell = new QLabel("Base1",this) ;cell->setPixmap(QPixmap::fromImage(Base1Img)) ;ui->maptable->removeCellWidget(map.base1.x(),map.base1.y())  ;set_cell(map.base1.x(),map.base1.y(),AIR);map.base1.setX(row);map.base1.setY(column);break;
    case BASE2 : cell = new QLabel("Base2",this) ;cell->setPixmap(QPixmap::fromImage(Base2Img)) ;ui->maptable->removeCellWidget(map.base2.x(),map.base2.y())  ;set_cell(map.base2.x(),map.base2.y(),AIR);map.base2.setX(row);map.base2.setY(column);break;
    case SPAWN1: cell = new QLabel("Spawn1",this);cell->setPixmap(QPixmap::fromImage(Spawn1Img));ui->maptable->removeCellWidget(map.spawn1.x(),map.spawn1.y());set_cell(map.spawn1.x(),map.spawn1.y(),AIR);map.spawn1.setX(row);map.spawn1.setY(column);break;
    case SPAWN2: cell = new QLabel("Spawn2",this);cell->setPixmap(QPixmap::fromImage(Spawn2Img));ui->maptable->removeCellWidget(map.spawn2.x(),map.spawn2.y());set_cell(map.spawn2.x(),map.spawn2.y(),AIR);map.spawn2.setX(row);map.spawn2.setY(column);break;
    }
    map.mapplane[static_cast<size_t>(row)][static_cast<size_t>(column)]=sta;
    ui->maptable->setCellWidget(row,column,cell);
    ui->maptable->setShowGrid(true);
}

void Mapmaker::prepare_table(){
    ui->maptable->clear();
    ui->maptable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->maptable->setSelectionMode(QAbstractItemView::NoSelection);
    ui->maptable->setColumnCount(mapsize);
    ui->maptable->setRowCount(mapsize);
    ui->maptable->verticalHeader()->setVisible(false); //隐藏列表头
    ui->maptable->horizontalHeader()->setVisible(false); //隐藏行表头
    for(int i=0;i<mapsize;++i){
        ui->maptable->setColumnWidth(i,32);
        ui->maptable->setRowHeight(i,32);
    }
}

void Mapmaker::draw_table(){//View(Usually just use the table itself)
    prepare_table();
    //draw
    for (size_t i=0;i<mapsize;++i) {
        for(size_t j=0;j<mapsize;++j){
            set_cell(static_cast<int>(i),static_cast<int>(j),(map.mapplane[i][j]));
        }
    }
    //Make sure has spawn and base
    set_cell(map.base1.x(),map.base1.y(),BASE1);
    set_cell(map.base2.x(),map.base2.y(),BASE2);
    set_cell(map.spawn1.x(),map.spawn1.y(),SPAWN1);
    set_cell(map.spawn2.x(),map.spawn2.y(),SPAWN2);
}

//更换模式的函数模板
template<MAP_OBJECT STA>
void Mapmaker::change_mode(){
    ui->maptable->setShowGrid(true);ui->statusbar->showMessage("Edit mode");cursor_status=STA;
}

template<>
void Mapmaker::change_mode<NONE>(){
    ui->maptable->setShowGrid(false);ui->statusbar->showMessage("View mode");draw_table();cursor_status=NONE;
}

void Mapmaker::add_new(){
    Mapmaker *window_to_be_use = this;
    if(QMessageBox::Yes==QMessageBox::warning(this,tr("Warning!"),
                                              tr("Create new file in this window might lead to data lost.\nOpen in a new window?"),
                                              QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)){
        window_to_be_use = new Mapmaker();
        window_to_be_use->setAttribute(Qt::WA_DeleteOnClose);
        window_to_be_use->show();
    }
    else {
        //do nothing
    }
    window_to_be_use->map=MAP::mymap();
    window_to_be_use->draw_table();
    return;
}

void Mapmaker::open(){
    QString path;
    //dialog
    Mapmaker *window_to_be_use = this;
    path = QFileDialog::getOpenFileName(this, tr("Open file"),".",tr("Map Files(*.map)"));

    if(path.isEmpty()){//Not OK
        QMessageBox::warning(this, tr("Path"),tr("You did not select any file."));
    }
    else{
    //OK
    //Ask if open in new Window
        if(QMessageBox::Yes==QMessageBox::warning(this,tr("Warning!"),
                                                  tr("Open in this window might lead to data lost.\nOpen in a new window?"),
                                                  QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes)){
            window_to_be_use = new Mapmaker();
            window_to_be_use->setAttribute(Qt::WA_DeleteOnClose);
            window_to_be_use->show();
        }else{
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
        in.readRawData(reinterpret_cast<char *>(&map),sizeof(map));
        file.close();
        if(map.spawn1_direction>3||map.spawn1_direction<0){
        QMessageBox::warning(this, tr("ERROR"),
                             tr("Cannot open file:\n%1").arg(path));
        map.init();
        return;
        }
        draw_table();
    }
    return;
}

//TODO
void Mapmaker::save(){
    QString  path = QFileDialog::getSaveFileName(this,
                                                 tr("Open File"),
                                                 ".",
                                                 tr("Map Files(*.map)"));
    if(path.isEmpty()){
        QMessageBox::warning(this, tr("Path"),
                             tr("You did not select any file."));
    }else{
        QFile file(path);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::warning(this, tr("Write File"),
                                 tr("Cannot open file:\n%1").arg(path));
            return;
        }else{
            QDataStream out(&file);
            out.writeRawData(reinterpret_cast<char *>(&map),sizeof (map));//TODO:因为大小端的原因，这个写法是很可能出现问题的。
            file.close();
        }
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

void Mapmaker::undo(){
    if(Undostack.isEmpty()){
        //do nothing
    }else{
        Redostack.push(map);
        map=Undostack.pop();
        draw_table();
    }
}

void Mapmaker::redo(){
    if(Redostack.isEmpty()){
        //do nothing
    }else{
        Undostack.push(map);
        map=Redostack.pop();
        draw_table();
    }
}

void Mapmaker::help(){
        QMessageBox(QMessageBox::Information,"帮助",
                    "    本关卡编辑器可以绘制坦克大战游戏的地图。各个按钮代表不同的模式:\n"
                    "    View:观察模式"
                    "    Air:清除砖块\n"
                    "    Brick:添加可破坏砖块\n"
                    "    Iron:添加不可破坏砖块\n"
                    "    Base1:修改玩家1基地\n"
                    "    Base2:修改玩家2基地\n"
                    "    Spawn1:修改玩家1重生地点\n"
                    "    Spawn2:修改玩家2重生地点\n"
                    "    双击出生点可以修改坦克出生面对的方向",
                    QMessageBox::Ok,this).exec();
}
void Mapmaker::about(){
        QMessageBox(QMessageBox::Information,"关于",
                    "    本关卡编辑器由emon100开发\n"
                    "    E-mail:emon100@qq.com\n",
                    QMessageBox::Ok,this).exec();
}

Mapmaker::~Mapmaker()
{
    delete ui;
}
