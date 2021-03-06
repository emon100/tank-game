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
    p1_lives=4;
    p2_lives=4;
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
    view  = new QGraphicsView(scene,this);
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
        p2_score+=500;
        spawn_tank1();
    }else if(tank==p2){
        p1_score+=500;
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
    if(p1_lives>=0){
        if(p1==nullptr){
            p1= new TANK(TANK_1);
        }
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
    if(p2_lives>=0){
        if(p2==nullptr){
            p2= new TANK(TANK_2);
        }
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

/*TODO:Handle input using QMap to implement mutiple key input*/
void game_widget::keyPressEvent(QKeyEvent *key){
    current_pressed_key.insert(key->key());
    p1->tank_movable=false;
    p2->tank_movable=false;
    //p1
    if(current_pressed_key.contains(Qt::Key_W)){p1->tank_movable=true;p1->set_direction(NORTH);   }
    if(current_pressed_key.contains(Qt::Key_A)){p1->tank_movable=true;p1->set_direction(WEST);                 }
    if(current_pressed_key.contains(Qt::Key_S)){p1->tank_movable=true;p1->set_direction(SOUTH);                }
    if(current_pressed_key.contains(Qt::Key_D)){p1->tank_movable=true;p1->set_direction(EAST);                 }
    if(current_pressed_key.contains(Qt::Key_C)){fire_bullet1();                                                }


    //p2
    if(current_pressed_key.contains(Qt::Key_I)){p2->tank_movable=true;p2->set_direction(NORTH);}
    if(current_pressed_key.contains(Qt::Key_J)){p2->tank_movable=true;p2->set_direction(WEST);}
    if(current_pressed_key.contains(Qt::Key_K)){p2->tank_movable=true;p2->set_direction(SOUTH);}
    if(current_pressed_key.contains(Qt::Key_L)){p2->tank_movable=true;p2->set_direction(EAST);}
    if(current_pressed_key.contains(Qt::Key_Slash)){  fire_bullet2();}

    if(current_pressed_key.contains(Qt::Key_Return)){  on_PauseButton_clicked();}
    //qDebug()<<p1->pos()<<"pressed";

    return;
}
void game_widget::keyReleaseEvent(QKeyEvent *key){
    if(current_pressed_key.remove(key->key())){
        p1->tank_movable=false;
        p2->tank_movable=false;
        //p1
        if(current_pressed_key.contains(Qt::Key_W)){p1->tank_movable=true;p1->set_direction(NORTH);   }
        if(current_pressed_key.contains(Qt::Key_A)){p1->tank_movable=true;p1->set_direction(WEST);                 }
        if(current_pressed_key.contains(Qt::Key_S)){p1->tank_movable=true;p1->set_direction(SOUTH);                }
        if(current_pressed_key.contains(Qt::Key_D)){p1->tank_movable=true;p1->set_direction(EAST);                 }
        if(current_pressed_key.contains(Qt::Key_C)){fire_bullet1();                                                }


        //p2
        if(current_pressed_key.contains(Qt::Key_I)){p2->tank_movable=true;p2->set_direction(NORTH);}
        if(current_pressed_key.contains(Qt::Key_J)){p2->tank_movable=true;p2->set_direction(WEST);}
        if(current_pressed_key.contains(Qt::Key_K)){p2->tank_movable=true;p2->set_direction(SOUTH);}
        if(current_pressed_key.contains(Qt::Key_L)){p2->tank_movable=true;p2->set_direction(EAST);}
        if(current_pressed_key.contains(Qt::Key_Slash)){fire_bullet2();}

        if(current_pressed_key.contains(Qt::Key_Return)){on_PauseButton_clicked();}
    }
}

void game_widget::fire_bullet1(){
    if(ispause==false&&p1->bullet_movable==false){//不行才可发射
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
    if(ispause==false&&p2->bullet_movable==false){//不行才可发射
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
    tanks_update();
    scene->update();
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
        case NORTH:p2_now.ry()-=p2_speed;break;
        case WEST :p2_now.rx()-=p2_speed;break;
        case SOUTH:p2_now.ry()+=p2_speed;break;
        case EAST :p2_now.rx()+=p2_speed;break;
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
    //判断坦克离开地图
    if(p1->pos().x()<0||p1->pos().x()>512||p1->pos().y()<0||p1->pos().y()>512){
        spawn_tank1();
    }
    if(p2->pos().x()<0||p2->pos().x()>512||p2->pos().y()<0||p2->pos().y()>512){
        spawn_tank2();
    }
    scene->update();
}



/////界面逻辑
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
        if(map.spawn1_direction>3||map.spawn1_direction<0){//校验
        QMessageBox::warning(this, tr("ERROR"),
                             tr("Cannot open file:\n%1").arg(path));
        map.init();
        return;
        }
        qDebug()<<"File OK";
        initSceneView();//打开好了才初始化游戏界面,TODO:bug:取消暂停后再加载地图之后坦克可以随意移动。
    }
    return;
}

//历史最佳对局功能
void game_widget::scores_output(){
    QFile file("scores.dat");
    bool change=false;
    QString temp_id;
    int temp_score;
    if(!file.open(QIODevice::ReadOnly)){
        if (file.open(QIODevice::WriteOnly)) {
            QDataStream out(&file);
            out<<p1_name<<p1_score;
            out<<p2_name<<p2_score;
        }
    }else {
        QDataStream in(&file);
        in>>temp_id>>temp_score;
        if(temp_score<=p1_score){
            change=true;
        }
        in>>temp_id>>temp_score;
        if(temp_score<=p2_score&&change){
            change=true;
        }else {
            change=false;
        }
        file.close();
    }
    if(change) {
    if(file.open(QIODevice::WriteOnly)){
        QDataStream out(&file);
        out<<p1_name<<p1_score;
        out<<p2_name<<p2_score;
        file.close();
    }
    }
}
void game_widget::close(){
    if(QMessageBox::Yes==QMessageBox::question(this,
                                               tr("Quit?"),
                                               tr("Are you sure to quit?"),
                                               QMessageBox::Yes|QMessageBox::No,QMessageBox::No))
    {
        QWidget::close();
    }
    else return;
}
void game_widget::game_ui_update(){
    ui->P1_name->setText(QString("%1").arg(p1_name));
    ui->P2_name->setText(QString("%1").arg(p2_name));
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
    QFile scores("scores.dat");
    if(scores.open(QIODevice::ReadOnly)){
        over->setText(over->text()+"\n"+"历史精彩对局");
        QDataStream in(&scores);
        QString temp_id;
        int   temp_score;
        for (int i=0;i<2&&!in.atEnd();++i) {
            in>>temp_id>>temp_score;
            over->setText(over->text()+"\n"+temp_id+QString("   %1").arg(temp_score));
            in>>temp_id>>temp_score;
            over->setText(over->text()+"\n"+temp_id+QString("   %1").arg(temp_score));
        }
        scores.close();
    }
    scores_output();
    int result=over->exec();
    if(result==QMessageBox::Yes){
        scene->clear();
        view->close();
        init();
    }else {
        QWidget::close();
    }
}

void game_widget::on_LevelButton_clicked()
{
    open();
    scene->clear();
    view->close();
    init();
}

void game_widget::on_IntroButton_clicked()//说明
{
    QMessageBox *over=new QMessageBox(QMessageBox::Information,"坦克大战游戏介绍",
                                      "text",
                                      QMessageBox::Ok,nullptr);
    over->setText("    本游戏为一款双人对战游戏，玩家1使用W A S D操作坦克移动，用C键发射子弹，玩家2使用I J K L操作坦克，用问号键发射子弹。双方的获胜目标是摧毁对方的建筑或者让对方用尽复活次数。\n"
                  "    可以通过关卡编辑器设计不同的地图之后在游戏内载入。"
                  "	   按回车可以开始或暂停游戏");
    over->exec();
}

void game_widget::on_PauseButton_clicked()//暂停
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

game_widget::~game_widget()
{
    delete ui;
}
