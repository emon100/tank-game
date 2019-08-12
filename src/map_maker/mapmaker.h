#ifndef MAPMAKER_H
#define MAPMAKER_H

#include "mymap.h"
#include <QMainWindow>
#include <QIcon>
#include <QTableWidgetItem>
#include <QAction>
#include <QPainter>
#include <QPixmap>
#include <QLabel>

namespace Ui {
class Mapmaker;
}

class Mapmaker : public QMainWindow
{
    Q_OBJECT

public:
    explicit Mapmaker(QWidget *parent = nullptr);
    ~Mapmaker();

private:
    MAP::mymap map;
    MAP_OBJECT cursor_status;

    template<MAP_OBJECT cursor_status>
    void change_mode();

    void add_new();//new one file
    void open();//打开文件
    void open_with_path(QString path);//打开文件
    void save();//保存文件
    void close();//关闭文件

    void set_table_by_file();//测试中
    void init_table();//测试，新建表格

    void set_cell(int row,int column,MAP_OBJECT sta);
    void set_cell_by_cursor_status(int row,int column);
    void set_spawn_direction(int row,int column);

    bool map_validate(MAP_OBJECT sta);

    Ui::Mapmaker *ui;
};

template <>
void Mapmaker::change_mode<NONE>();

#endif // MAPMAKER_H
