#include "rtabmap.h"
#include "ui_rtabmap.h"
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
#include <QPicture>
#include <QImage>
#include <QPixmap>
#include <QFileInfo>

rtabmap::rtabmap(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::rtabmap)
{
    ui->setupUi(this);



    //页面布局
    this->setFixedSize(1500, 1000);
    this->setWindowTitle("北航江西研究院05team");
    //QDesktopWidget * desktop_main = QApplication::desktop();
    this->move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    //this->setFixedSize();

    //显示图片
    QImage image;
    image.load(":/image/rtabmap.jpeg");
    QPixmap pixmap = QPixmap::fromImage(image);
    int width = ui->label_image->width();
    int height = ui->label_image->height();
    QPixmap fitpixmap = pixmap.scaled(width, height, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    ui->label_image->setPixmap(fitpixmap);


    //设置列表控件
    QListWidgetItem * item = new QListWidgetItem("运行数据集");
    ui->listWidget->addItem(item);
    item->setTextAlignment(Qt::AlignHCenter);
    QStringList list;
    list << "1.打开launch文件" << "2.选择数据包" << "3.运行Rtabmap数据集" << " " << " " <<  " ";
    ui->listWidget->addItems(list);

    QListWidgetItem * item_2 = new QListWidgetItem("导航与避障");
    ui->listWidget->addItem(item_2);
    item_2->setTextAlignment(Qt::AlignHCenter);
    QStringList list_2;
    list_2 << "1.打开launch文件" << "2.启动小车" << "3.启动键盘" << "4.启动ZED" << "5.启动Rtabmap";
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
        filePath = QFileDialog::getOpenFileName(this, "打开launch文件");
        QFileInfo fileinfo = QFileInfo(filePath);
        filename = fileinfo.fileName();
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



    //点击按钮运行rtabmap数据集
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
            //启动参数文件
            QString str = "gnome-terminal -- bash -c 'export LD_LIBRARY_PATH=/home/ubuntu/slam/ORB_SLAM2/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/g2o/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/DBoW2/lib:$LD_LIBRARY_PATH;source ~/catkin_rtabmap/devel/setup.bash;roslaunch rtabmap_ros ";
            QString str2 = "'&";
            str += filename;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);

            //启动数据集
            QString str3 = "gnome-terminal -- bash -c 'source ~/catkin_rtabmap/devel/setup.bash;rosbag play --clock ";
            QString str4 = "'&";
            str3 += filePath_2;
            str3 += str4;
            QByteArray bt_2;
            bt_2.append(str3);
            const char * proc = bt_2.data();
            system(proc);

        }
    });



    //点击按钮启动小车
    connect(ui->pushButton_7, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/kobuki_ws/devel/setup.bash;source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_bringup minimal.launch'&");
    });



    //点击按钮启动键盘
    connect(ui->pushButton_8, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_teleop keyboard_teleop.launch'&");
    });



    //点击按钮启动ZED
    connect(ui->pushButton_13, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/tools/zed/devel/setup.bash;source ~/turtlebot_ws/devel/setup.bash;roslaunch turbot_vslam rtabmap_zed.launch'&");
    });



    //点击按钮启动Rtabmap
    connect(ui->pushButton_9, &QPushButton::clicked, [=](){
          QString name;
          name = "gnome-terminal -- bash -c 'source ~/turtlebot_ws/devel/setup.bash;roslaunch turbot_rviz rtabmap_rviz.launch'&";
          QByteArray bt;
          bt.append(name);
          const char * proc = bt.data();
          system(proc);
    });



}

rtabmap::~rtabmap()
{
    delete ui;
}
