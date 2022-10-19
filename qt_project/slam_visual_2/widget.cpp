#include "widget.h"
#include "ui_widget.h"
#include <QPushButton>
#include <QProcess>
#include <QDesktopWidget>
#include <QApplication>
#include "liosam.h"
#include "vins_fusion.h"
#include "orbslam2.h"
#include "rtabmap.h"


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    //主页面布局
    this->setFixedSize(1500, 1000);
    this->setWindowTitle("北航江西研究院05team");
    //QDesktopWidget * desktop_main = QApplication::desktop();
    this->move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    //this->setFixedSize();


    //点击按钮退出程序
    connect(ui->pushButton_5, &QPushButton::clicked, this, &QWidget::close);

    //点击按钮转到下级页面
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){

        this->close();
        vins_fusion * vins_scene = new vins_fusion;
        vins_scene->setAttribute(Qt::WA_DeleteOnClose);
        vins_scene->show();
    });

    connect(ui->pushButton_2, &QPushButton::clicked, [=](){

        this->close();
        liosam * lio_scene = new liosam;
        lio_scene->setAttribute(Qt::WA_DeleteOnClose);
        lio_scene->show();
    });

    connect(ui->pushButton_4, &QPushButton::clicked, [=](){
        this->close();
        orbslam2 * orb_scene = new orbslam2;
        orb_scene->setAttribute(Qt::WA_DeleteOnClose);
        orb_scene->show();
    });

    connect(ui->pushButton, &QPushButton::clicked,[=](){
        this->close();
        rtabmap * rta_scene = new rtabmap;
        rta_scene->setAttribute(Qt::WA_DeleteOnClose);
        rta_scene->show();
    });


}

Widget::~Widget()
{
    delete ui;
}




