#include "vins_fusion.h"
#include "ui_vins_fusion.h"
#include <QDesktopWidget>
#include <QMovie>
#include <QDebug>
#include <QStringList>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include "widget.h"
#include <QListWidgetItem>
#include <QProcess>

vins_fusion::vins_fusion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::vins_fusion)
{
    ui->setupUi(this);



    //页面布局
    this->setFixedSize(1500, 1000);
    this->setWindowTitle("北航江西研究院05team");
    //QDesktopWidget * desktop_main = QApplication::desktop();
    this->move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    //this->setFixedSize();

    //显示gif图片
    QMovie * movie = new QMovie(":/image/vins-fusion.gif");
    ui->label_image->setMovie(movie);
    ui->label_image->setScaledContents(true);
    movie->start();



    //设置列表控件
    QListWidgetItem * item = new QListWidgetItem("运行数据集");
    ui->listWidget->addItem(item);
    item->setTextAlignment(Qt::AlignHCenter);
    QStringList list;
    list << "1.打开参数文件" << "2.选择数据包" << "3.运行vins数据集" << "4.启动回环（可选)" << " " << " " <<  " ";
    ui->listWidget->addItems(list);

    QListWidgetItem * item_2 = new QListWidgetItem("实际运行(双目）");
    ui->listWidget->addItem(item_2);
    item_2->setTextAlignment(Qt::AlignHCenter);
    QStringList list_2;
    list_2 << "1.打开参数文件" << "2.启动小车" << "3.启动IMU" << "4.启动ZED" << "5.启动vins_fusion" << "6.启动参数文件" << "7.启动回环（可选）";
    ui->listWidget->addItems(list_2);



    //点击按钮返回上级页面
    connect(ui->pushButton_6, &QPushButton::clicked, [=](){
        this->hide();
        Widget * main_scene = new Widget;
        main_scene->setAttribute(Qt::WA_DeleteOnClose);
        main_scene->show();
    });



    //点击按钮打开参数文件
    connect(ui->pushButton, &QPushButton::clicked,[=](){
        filePath = QFileDialog::getOpenFileName(this, "打开文件");
        if(filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit->setText(filePath);

            QFile file(filePath);
            file.open(QIODevice::ReadWrite | QFile::Text);
            QByteArray array;
            array = file.readAll();
            ui->textEdit->setText(array);
        }

    });



    //点击按钮选择数据包
    connect(ui->pushButton_4, &QPushButton::clicked, [=](){
        filePath_2 = QFileDialog::getOpenFileName(this, "选择数据包");
        if(filePath_2.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_2->setText(filePath_2);
        }
    });



    //点击按钮保存文件
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        QFile saveFile(filePath);
        if(!saveFile.open(QFile::WriteOnly | QFile::Text))
        {
            QMessageBox::warning(this,"警告", "没有需要保存的文件");
            return;
        }
        else
        {
            QTextStream out(&saveFile);
            out << ui->textEdit->toPlainText();
            saveFile.close();
            QMessageBox::information(this, "保存",  "保存成功!");
        }

    });



    //点击按钮运行vins-fusion数据集
    //system("gnome-terminal -x bash -c 'source /home/user/Lio-sam_ws/devel/setup.bash;roslaunch lio_sam run.launch'&");
    //system("gnome-terminal -x bash -c 'source /home/user/Lio-sam_ws/devel/setup.bash;rosbag play /home/user/Lio-sam_ws/lio-sam_dataset/default/casual_walk.bag'&");
    connect(ui->pushButton_5, &QPushButton::clicked, [=](){
        if(filePath_2.isEmpty() || filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "数据包与参数文件路径不能为空!");
            return;
        }
        else
        {
            //启动rviz
            system("gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;roslaunch vins vins_rviz.launch'&");

            //启动参数文件
            QString str = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;rosrun vins vins_node ";
            QString str2 = "'&";
            str += filePath;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);

            //启动数据集
            QString str3 = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;rosbag play ";
            QString str4 = "'&";
            str3 += filePath_2;
            str3 += str4;
            QByteArray bt_2;
            bt_2.append(str3);
            const char * proc = bt_2.data();
            system(proc);

        }
    });



    //点击按钮运行数据集时启动回环
    connect(ui->pushButton_12, &QPushButton::clicked, [=](){
        if(filePath_2.isEmpty() || filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "数据包与参数文件路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;rosrun loop_fusion loop_fusion_node ";
            QString str2 = "'&";
            str += filePath;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }

    });


    //点击按钮启动小车
    connect(ui->pushButton_7, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/kobuki_ws/devel/setup.bash;source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_bringup minimal.launch'&");
        system("gnome-terminal -- bash -c 'source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_teleop keyboard_teleop.launch'&");
    });



    //点击按钮启动IMU
    connect(ui->pushButton_8, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source /home/ubuntu/qt_project/slam_visual_2/bash/xsens.sh;'&");
    });



    //点击按钮启动ZED
    connect(ui->pushButton_13, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/tools/zed/devel/setup.bash;"
               "roslaunch zed_wrapper zed.launch'&");
    });



    //点击按钮启动Vins
    connect(ui->pushButton_9, &QPushButton::clicked, [=](){
          QString name;
          name = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;roslaunch vins vins_rviz.launch'&";
          QByteArray bt;
          bt.append(name);
          const char * proc = bt.data();
          system(proc);
    });



    //点击按钮启动参数文件
    connect(ui->pushButton_10, &QPushButton::clicked, [=](){
          QString name;
          name = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;rosrun vins vins_node /home/ubuntu/vins-fusion_ws/src/VINS-Fusion-master/config/zed_measured/zed_stereo_config.yaml'&";
          QByteArray bt;
          bt.append(name);
          const char * proc = bt.data();
          system(proc);
    });



    //点击按钮启动回环（实测）
    connect(ui->pushButton_11, &QPushButton::clicked,[=](){
        if(filePath_2.isEmpty() || filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "数据包与参数文件路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c 'source ~/vins-fusion_ws/devel/setup.bash;rosrun loop_fusion loop_fusion_node ";
            QString str2 = "'&";
            str += filePath;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }
    });

}


vins_fusion::~vins_fusion()
{
    delete ui;
}
