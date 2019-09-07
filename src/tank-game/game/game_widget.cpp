#include "game/game_widget.h"
#include "ui_game_widget.h"
#include "game/game_items.h"
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDataStream>

const int TIME=1000/50;
game_widget::game_widget(QWidget *parent,const QString &p1_n,const QString &p2_n) :
    QWidget(parent),
    ui(new Ui::game_widget),
    ispause(true),
    p1_name(p1_n),
    p2_name(p2_n)
{
    ui->setupUi(this);
    p1_name="player1";
    p2_name="player2";
    setFocusPolicy(Qt::StrongFocus);
    on_IntroButton_clicked();
    init();

    connect(&timer,&QTimer::timeout,this,&game_widget::object_update);
    connect(ui->ExitButton,&QPushButton::clicked,this,&game_widget::close);

    connect(this,&game_widget::win,this,&game_widget::final);
}
void game_widget::init(){
    p1=nullptr;
    p2=nullptr;
    p1_score=0;
    p2_score=0;
    p1_lives=3;
    p2_lives=3;
    ispause=true;
    ui->PauseButton->setText("开始");
    game_ui_update();
    initSceneView();
    view->show();
    qDebug()<<"1";
    //timer.start(TIME);
    connect(&p1->bullet,&BULLET::destroy_item,this,&game_widget::p1_destroy);
    connect(&p2->bullet,&BULLET::destroy_item,this,&game_widget::p2_destroy);
    connect(&p1->bullet,&BULLET::kill_tank,this,&game_widget::kill_tank);
    connect(&p2->bullet,&BULLET::kill_tank,this,&game_widget::kill_tank);

    qDebug()<<"OK!";
}


void game_widget::initSceneView(){
    scene = new QGraphicsScene(this);
    view  = new QGraphicsView(this);
    scene->setSceneRect(0,0,512,512);
    scene->installEventFilter(this);
    set_map_items();
    spawn_tanks();
    view->setScene(scene);
    //设置背景纯黑
    view->setBackgroundBrush(Qt::black);

}

void set_direction(TANK *tank,DIRECTION direction){
    switch (direction) {
    case NORTH:tank->set_direction(NORTH);break;
    case WEST :tank->set_direction(WEST);break;
    case SOUTH:tank->set_direction(SOUTH);break;
    case EAST :tank->set_direction(EAST);break;
    }
}

void game_widget::spawn_tanks(){
    spawn_tank1();
    spawn_tank2();
}

void game_widget::kill_tank(QGraphicsItem *tank){
    if(tank==p1){
        p2_score+=100;
        spawn_tank1();
    }else if(tank==p2){
        p1_score+=100;
        spawn_tank2();
    }

}

void game_widget::p1_destroy(QGraphicsItem *item){
    if(item->data(1)==1){
        emit win(2);
    }else if(item->data(1)==2){
        p1_score+=1000;
        emit win(1);
    }else {
        p1_score+=50;
        scene->removeItem(item);
    }
}
void game_widget::p2_destroy(QGraphicsItem *item){
    if(item->data(1)==1){
        p2_score+=1000;
        emit win(2);
    }else if(item->data(1)==2){
        emit win(1);
    }else {
        p2_score+=50;
        scene->removeItem(item);
    }
}

void game_widget::spawn_tank1(){
    p1_lives--;
    if(p1_lives>0){
        if(p1==nullptr)
            p1= new TANK(TANK_1);
        p1->bullet.hide();
        p1->setPos(32*map.spawn1.y()+16,32*map.spawn1.x()+16);
        p1->old_pos=p1->pos();
        set_direction(p1,map.spawn1_direction);
        p1->bullet.setPos(p1->pos());
        p1->bullet.setDirection(p1->get_direction());
        scene->addItem(p1);
        scene->addItem(&p1->bullet);
    }else {
        emit win(2);
}
}
void game_widget::spawn_tank2(){
    p2_lives--;
    if(p2_lives>0){
        if(p2==nullptr)
            p2= new TANK(TANK_2);
        p2->bullet.hide();
        p2->setPos(32*map.spawn2.y()+16,32*map.spawn2.x()+16);
        p2->old_pos=p2->pos();
        set_direction(p2,map.spawn2_direction);
        p2->bullet.setPos(p2->pos());
        p2->bullet.setDirection(p2->get_direction());
        scene->addItem(p2);
        scene->addItem(&p2->bullet);
    }else {
    emit win(1);
}

}
void game_widget::set_map_items(){
        MAP_ITEM *a=nullptr;
    for(size_t i=0;i<mapsize;++i){
        for(size_t j=0;j<mapsize;++j){
            switch(map.mapplane[i][j]) {
            case NONE :
            case SPAWN1:
            case SPAWN2:
            case AIR   :a=new MAP_ITEM(AIR);scene->addItem(a);break;
            case IRON  :a=new MAP_ITEM(IRON);scene->addItem(a);break;
            case BRICK :a=new MAP_ITEM(BRICK);scene->addItem(a);break;
            case BASE1 :a=new MAP_ITEM(BASE1);scene->addItem(a);break;
            case BASE2 :a=new MAP_ITEM(BASE2);scene->addItem(a);break;
            }
            a->setPos(32*j,32*i);//地图文件和游戏的scene是沿主对角线对称的
        }
    }
}

void game_widget::keyPressEvent(QKeyEvent *key){
    //p1
    switch(key->key()){
    case Qt::Key_W   :p1->tank_movable=true;p1->set_direction(NORTH);break;
    case Qt::Key_A   :p1->tank_movable=true;p1->set_direction(WEST);break;
    case Qt::Key_S   :p1->tank_movable=true;p1->set_direction(SOUTH);break;
    case Qt::Key_D   :p1->tank_movable=true;p1->set_direction(EAST);break;
    case Qt::Key_F  :fire_bullet1();break;
    }
    //p2
    switch(key->key()){
    case Qt::Key_Up  :p2->tank_movable=true;p2->set_direction(NORTH);break;
    case Qt::Key_Left:p2->tank_movable=true;p2->set_direction(WEST);break;
    case Qt::Key_Down:p2->tank_movable=true;p2->set_direction(SOUTH);break;
    case Qt::Key_Right:p2->tank_movable=true;p2->set_direction(EAST);break;
    case Qt::Key_L   :fire_bullet2();break;
    }
    //qDebug()<<p1->pos()<<"pressed";
    return;
}
void game_widget::keyReleaseEvent(QKeyEvent *key){
    switch(key->key()){
    case Qt::Key_W   :p1->tank_movable=false;p1->set_direction(NORTH);break;
    case Qt::Key_A   :p1->tank_movable=false;p1->set_direction(WEST);break;
    case Qt::Key_S   :p1->tank_movable=false;p1->set_direction(SOUTH);break;
    case Qt::Key_D   :p1->tank_movable=false;p1->set_direction(EAST);break;
    }
    switch(key->key()){
    case Qt::Key_Up  :p2->tank_movable=false;p2->set_direction(NORTH);break;
    case Qt::Key_Left:p2->tank_movable=false;p2->set_direction(WEST);break;
    case Qt::Key_Down:p2->tank_movable=false;p2->set_direction(SOUTH);break;
    case Qt::Key_Right:p2->tank_movable=false;p2->set_direction(EAST);break;
    }
    //qDebug()<<p1->pos()<<"released";
    return;
}

void game_widget::fire_bullet1(){
    if(p1->bullet_movable==false){//不行才可发射
        p1->bullet_movable=true;
        BULLET &b=p1->bullet;
        b.show();
        b.setDirection(p1->get_direction());
        switch(b.getDirection()){//出现在坦克前面
        case NORTH   :b.setPos(p1->pos().x(),p1->pos().y()-32);break;
        case WEST    :b.setPos(p1->pos().x()-32,p1->pos().y());break;
        case SOUTH   :b.setPos(p1->pos().x(),p1->pos().y()+32);break;
        case EAST    :b.setPos(p1->pos().x()+32,p1->pos().y());break;
        }
    }
}

void game_widget::fire_bullet2(){
    if(p2->bullet_movable==false){//不行才可发射
        p2->bullet_movable=true;
        BULLET &b=p2->bullet;
        b.show();
        b.setDirection(p2->get_direction());
        switch(b.getDirection()){
        case NORTH   :b.setPos(p2->pos().x(),p2->pos().y()-32);break;
        case WEST    :b.setPos(p2->pos().x()-32,p2->pos().y());break;
        case SOUTH   :b.setPos(p2->pos().x(),p2->pos().y()+32);break;
        case EAST    :b.setPos(p2->pos().x()+32,p2->pos().y());break;
        }
    }
}

void game_widget::object_update(){
    bullets_update();
    scene->update();
    tanks_update();
    game_ui_update();
}

//TOOTOTOTOTOTDOODODO
void game_widget::bullets_update(){
    QPointF p1_now;
    QPointF p2_now;
    p1_now= p1->bullet.pos();
    p2_now= p2->bullet.pos();
    int p1_speed=p1->bullet.getSpeed();
    int p2_speed=p1->bullet.getSpeed();
    if(p1->bullet_movable){
        switch(p1->bullet.getDirection()){
        case NORTH   :p1_now.ry()-=p1_speed;break;
        case WEST    :p1_now.rx()-=p1_speed;break;
        case SOUTH   :p1_now.ry()+=p1_speed;break;
        case EAST    :p1_now.rx()+=p1_speed;break;
        }
        p1->bullet.setPos(p1_now);
    }else {
    }
    if(p2->bullet_movable){
        switch(p2->bullet.getDirection()){
        case NORTH:p2_now.ry()-=p2_speed;;break;
        case WEST :p2_now.rx()-=p2_speed;;break;
        case SOUTH:p2_now.ry()+=p2_speed;;break;
        case EAST :p2_now.rx()+=p2_speed;;break;
        }
        p2->bullet.setPos(p2_now);
    }else {
    }
    if(p1->bullet_movable&&!p1->bullet.handleCollisions()){
            p1->bullet_movable=false;
            p1->bullet.setPos(p1_now);
            p1->bullet.setDirection(p1->get_direction());
            p1->bullet.hide();
    }
    if(p2->bullet_movable&&!p2->bullet.handleCollisions()){

            p2->bullet_movable=false;
            p2->bullet.setPos(p2_now);
            p2->bullet.setDirection(p2->get_direction());
            p2->bullet.hide();
    }
    if(p1->bullet.pos().x()<0||p1->bullet.pos().x()>512||p1->bullet.pos().y()<0||p1->bullet.pos().y()>512){
            p1->bullet_movable=false;
            p1->bullet.setPos(p1_now);
            p1->bullet.setDirection(p1->get_direction());
            p1->bullet.hide();
    }
    if(p2->bullet.pos().x()<0||p2->bullet.pos().x()>512||p2->bullet.pos().y()<0||p2->bullet.pos().y()>512){
            p2->bullet_movable=false;
            p2->bullet.setPos(p2_now);
            p2->bullet.setDirection(p2->get_direction());
            p2->bullet.hide();
    }
}

void game_widget::tanks_update(){//同时在不发射子弹的时候负责承载子弹
    QPointF p1_old,p1_now;
    QPointF p2_old,p2_now;
    p1_old=p1_now= p1->pos();
    p2_old=p2_now= p2->pos();
    int p1_speed=p1->speed();
    int p2_speed=p2->speed();

    if(p1->tank_movable){
    //    qDebug()<<"p1 can move";
        switch(p1->get_direction()){
        case NORTH   :p1_now.ry()-=p1_speed;p1->set_direction(NORTH);break;
        case WEST    :p1_now.rx()-=p1_speed;p1->set_direction(WEST);break;
        case SOUTH   :p1_now.ry()+=p1_speed;p1->set_direction(SOUTH);break;
        case EAST    :p1_now.rx()+=p1_speed;p1->set_direction(EAST);break;
        }
        p1->setPos(p1_now);
        if(!p1->bullet_movable){
            p1->bullet.setPos(p1_now);
            p1->bullet.setDirection(p1->get_direction());
        }
        if(!p1->handleCollisions()){
            p1->setPos(p1_old);
            if(!p1->bullet_movable){
                p1->bullet.setPos(p1_old);
                p1->bullet.setDirection(p1->get_direction());
            }
        }
    }else{}
    if(p2->tank_movable){
    //    qDebug()<<"p2 can move";
        switch(p2->get_direction()){
        case NORTH:p2_now.ry()-=p2_speed;p2->set_direction(NORTH);break;
        case WEST :p2_now.rx()-=p2_speed;p2->set_direction(WEST);break;
        case SOUTH:p2_now.ry()+=p2_speed;p2->set_direction(SOUTH);break;
        case EAST :p2_now.rx()+=p2_speed;p2->set_direction(EAST);break;
        }
        p2->setPos(p2_now);
        if(!p2->bullet_movable){
            p2->bullet.setPos(p2_now);
            p2->bullet.setDirection(p2->get_direction());
        }
        if(!p2->handleCollisions()){
            p2->setPos(p2_old);
            if(!p2->bullet_movable){
                p2->bullet.setPos(p2_old);
                p2->bullet.setDirection(p2->get_direction());
            }
        }
    }else {}
    if(p1->pos().x()<0||p1->pos().x()>512||p1->pos().y()<0||p1->pos().y()>512){
        spawn_tank1();
    }
    if(p2->pos().x()<0||p2->pos().x()>512||p2->pos().y()<0||p2->pos().y()>512){
        spawn_tank2();
    }
    scene->update();
}



//界面逻辑
void game_widget::open(){
    QString path;
    //dialog
    game_widget *window_to_be_use = this;
    path = QFileDialog::getOpenFileName(this, tr("Open map file"),"D:\\source\\repos\\tank-game",tr("Map Files(*.map)"));

    if(path.isEmpty()){//Not OK
        QMessageBox::warning(this, tr("Path"),tr("You did not select any file."));
    }
    else{
        window_to_be_use->open_with_path(path);
        return;
    }
}
void game_widget::open_with_path(const QString &path){
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly )) {
        QMessageBox::warning(this, tr("Read File"),
                             tr("Cannot open file:\n%1").arg(path));
        return;
    }else{
        QDataStream in(&file);
        in.readRawData(reinterpret_cast<char *>(&map),sizeof(map));
        file.close();
        qDebug()<<"File OK";
        initSceneView();//打开好了才初始化游戏界面
    }
    return;
}
void game_widget::safe_close(){
        QFile file("scores.dat");
        if(file.open(QIODevice::WriteOnly)){
        QDataStream out;

        } else {}


        QWidget::close();
}
void game_widget::close(){
    if(QMessageBox::Yes==QMessageBox::question(this,
                                               tr("Quit?"),
                                               tr("Are you sure to quit?"),
                                               QMessageBox::Yes|QMessageBox::No,QMessageBox::No))
    {
        safe_close();
    }
    else return;
}
void game_widget::game_ui_update(){
    ui->P1_name->setText(QString("玩家1:%1").arg(p1_name));
    ui->P2_name->setText(QString("玩家2:%1").arg(p2_name));
    ui->P1_score->setText(QString("分数:%1").arg(p1_score));
    ui->P2_score->setText(QString("分数:%1").arg(p2_score));
    ui->P1_lives->setText(QString("剩余生命:%1").arg(p1_lives));
    ui->P2_lives->setText(QString("剩余生命:%1").arg(p2_lives));
}
void game_widget::final(int n){
    timer.stop();
    QMessageBox *over=new QMessageBox(QMessageBox::Information,"游戏结束",
                                      "text",
                                      QMessageBox::Yes|QMessageBox::No,nullptr);
    over->button(QMessageBox::Yes)->setText("再来一局!");
    over->button(QMessageBox::No)->setText("退出");

    if(n==1){
       over->setText(QString("玩家%1赢了!，分数为%2分，玩家%3也有%4分").arg(p1_name).arg(p1_score).arg(p2_name).arg(p2_score));
    }else if(n==2){
       over->setText(QString("玩家%1赢了!，分数为%2分，玩家%3也有%4分").arg(p2_name).arg(p2_score).arg(p1_name).arg(p1_score));
    }
    int result=over->exec();
    if(result==QMessageBox::Yes){
        scene->clear();
        view->close();
        init();
    }else {
        safe_close();
        QWidget::close();
    }

}
game_widget::~game_widget()
{
    delete ui;
}

void game_widget::on_LevelButton_clicked()
{
    open();
    scene->clear();
    view->close();
    init();
}

void game_widget::on_IntroButton_clicked()
{
    QMessageBox *over=new QMessageBox(QMessageBox::Information,"坦克大战游戏介绍",
                                      "text",
                                      QMessageBox::Ok,nullptr);
    over->setText("    本游戏为一款双人对战游戏，玩家1使用WASD操作坦克移动，用F键发射子弹，玩家2使用方向键操作坦克，用J发射子弹。双方的获胜目标是摧毁对方的建筑或者让对方用尽复活次数。\n"
                  "    可以通过关卡编辑器设计不同的地图之后在游戏内载入。"
                  "	   按开始键开始游戏，游戏中间按暂停键可以暂停游戏");
    over->exec();
}

void game_widget::on_PauseButton_clicked()
{
    if(ispause){
        timer.start(TIME);
        ui->PauseButton->setText("暂停");
        ispause=!ispause;
   } else {
        timer.stop();
        ui->PauseButton->setText("开始");
        ispause=!ispause;
    }
    update();
}
