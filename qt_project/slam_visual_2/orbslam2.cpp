#include "orbslam2.h"
#include "ui_orbslam2.h"


orbslam2::orbslam2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::orbslam2)
{
    ui->setupUi(this);


    //页面布局
    this->setFixedSize(1500, 1000);
    this->setWindowTitle("北航江西研究院05team");
    //QDesktopWidget * desktop_main = QApplication::desktop();
    this->move((QApplication::desktop()->width() - this->width())/2, (QApplication::desktop()->height() - this->height())/2);
    //this->setFixedSize();


//    //显示gif图片
//    QMovie * movie = new QMovie(":/image/orbslam2.gif");
//    ui->label_image->setMovie(movie);
//    movie->start();



    //设置列表控件
    QListWidgetItem * item = new QListWidgetItem("运行数据集");
    ui->listWidget->addItem(item);
    item->setTextAlignment(Qt::AlignHCenter);
    QStringList list;
    list << "1.Monocular To TUM" << "   ./Examples/Monocular/mono_tum Vocabulary/ORBvoc.txt Examples/Monocular/TUMX.yaml PATH_TO_SEQUENCE_FOLDER"
         << "2.Monocular To EuRoc" << " ./Examples/Monocular/mono_euroc Vocabulary/ORBvoc.txt Examples/Monocular/EuRoC.yaml PATH_TO_SEQUENCE_FOLDER/mav0/cam0/data Examples/Monocular/EuRoC_TimeStamps/SEQUENCE.txt"
         << "3.Stereo To EuRoc " << "   ./Examples/Stereo/stereo_euroc Vocabulary/ORBvoc.txt Examples/Stereo/EuRoC.yaml PATH_TO_SEQUENCE/mav0/cam0/data PATH_TO_SEQUENCE/mav0/cam1/data Examples/Stereo/EuRoC_TimeStamps/SEQUENCE.txt"
         << "4.RGBD To Tum " << "   ./Examples/RGB-D/rgbd_tum Vocabulary/ORBvoc.txt Examples/RGB-D/TUMX.yaml PATH_TO_SEQUENCE_FOLDER ASSOCIATIONS_FILE";
    ui->listWidget->addItems(list);

    QListWidgetItem * item_2 = new QListWidgetItem("实际运行");
    ui->listWidget->addItem(item_2);
    item_2->setTextAlignment(Qt::AlignHCenter);
    QStringList list_2;
    list_2 << "1.启动小车" << "2.启动键盘" << "3.启动ZED" << "4.启动ORB_SLAM2";
    ui->listWidget->addItems(list_2);



    //点击按钮返回上级页面
    connect(ui->pushButton_6, &QPushButton::clicked, [=](){
        this->hide();
        Widget * main_scene = new Widget;
        main_scene->setAttribute(Qt::WA_DeleteOnClose);
        main_scene->show();
    });



    //点击按钮选择executable file
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
        }

    });



    //点击按钮选择path_to_vocabulary
    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        filePath_2 = QFileDialog::getOpenFileName(this, "打开文件");
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



    //点击按钮选择path_to_settings
    connect(ui->pushButton_3, &QPushButton::clicked, [=](){
        filePath_3 = QFileDialog::getOpenFileName(this, "打开文件");
        if(filePath_3.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_3->setText(filePath_3);
        }
    });


    //点击按钮选择path_to_image_folder1
    connect(ui->pushButton_11, &QPushButton::clicked, [=](){
        filePath_4 = QFileDialog::getExistingDirectory(this, "打开文件夹");
        if(filePath_4.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_4->setText(filePath_4);
        }
    });



    //点击按钮选择path_to_image_folder2
    connect(ui->pushButton_14, &QPushButton::clicked, [=](){
        filePath_5 = QFileDialog::getExistingDirectory(this, "打开文件夹");
        if(filePath_5.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_7->setText(filePath_5);
        }
    });



    //点击按钮选择path_to_times_file
    connect(ui->pushButton_7, &QPushButton::clicked, [=](){
        filePath_6 = QFileDialog::getOpenFileName(this, "打开文件");
        if(filePath_6.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_8->setText(filePath_6);
        }
    });



    //点击按钮选择path_to_sequence
    connect(ui->pushButton_15, &QPushButton::clicked, [=](){
        filePath_7 = QFileDialog::getOpenFileName(this, "打开文件");
        if(filePath_7.isEmpty())
        {
            QMessageBox::warning(this,"警告", "文件路径不能为空");
            return;
        }
        else
        {
            ui->lineEdit_9->setText(filePath_7);
        }
    });




//    //点击按钮保存文件
//    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
//        QFile saveFile(filePath);
//        if(!saveFile.open(QFile::WriteOnly | QFile::Text))
//        {
//            QMessageBox::warning(this,"警告", "没有需要保存的文件");
//            return;
//        }
//        else
//        {
//            QTextStream out(&saveFile);
//            out << ui->textEdit->toPlainText();
//            saveFile.close();
//            QMessageBox::information(this, "保存",  "保存成功!");
//        }

//    });



    //点击按钮运行Monocular To EuRoc
    connect(ui->pushButton_13, &QPushButton::clicked,[=](){
        if(filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "executable file路径不能为空!");
            return;
        }
        else if(filePath_2.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_vocabulary路径不能为空!");
            return;
        }
        else if(filePath_3.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_settings路径不能为空!");
            return;
        }
        else if(filePath_4.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_image_folder1路径不能为空!");
            return;
        }
        else if(filePath_6.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_times_file路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c '";
            QString str2 = "'&";
            str += filePath;
            str += file;
            str += filePath_2;
            str += file;
            str += filePath_3;
            str += file;
            str += filePath_4;
            str += file;
            str += filePath_6;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }
    });



    //点击按钮运行Monocular To TUM
    connect(ui->pushButton_12, &QPushButton::clicked,[=](){
        if(filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "executable file路径不能为空!");
            return;
        }
        else if(filePath_2.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_vocabulary路径不能为空!");
            return;
        }
        else if(filePath_3.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_settings路径不能为空!");
            return;
        }
        else if(filePath_4.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_image_folder1路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c 'export LD_LIBRARY_PATH=/home/ubuntu/slam/ORB_SLAM2/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/g2o/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/DBoW2/lib:$LD_LIBRARY_PATH;";
            QString str2 = "'&";
            str += filePath;
            str += file;
            str += filePath_2;
            str += file;
            str += filePath_3;
            str += file;
            str += filePath_4;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }
    });



    //点击按钮运行Stereo To EuRoc
    connect(ui->pushButton_16, &QPushButton::clicked,[=](){
        if(filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "executable file路径不能为空!");
            return;
        }
        else if(filePath_2.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_vocabulary路径不能为空!");
            return;
        }
        else if(filePath_3.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_settings路径不能为空!");
            return;
        }
        else if(filePath_4.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_image_folder1路径不能为空!");
            return;
        }
        else if(filePath_5.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_image_folder1路径不能为空!");
            return;
        }
        else if(filePath_6.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_times_file路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c 'export LD_LIBRARY_PATH=/home/ubuntu/slam/ORB_SLAM2/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/g2o/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/DBoW2/lib:$LD_LIBRARY_PATH;";
            QString str2 = "'&";
            str += filePath;
            str += file;
            str += filePath_2;
            str += file;
            str += filePath_3;
            str += file;
            str += filePath_4;
            str += file;
            str += filePath_5;
            str += file;
            str += filePath_6;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }
    });



    //点击按钮运行RGBD To TUM
    connect(ui->pushButton_17, &QPushButton::clicked,[=](){
        if(filePath.isEmpty())
        {
            QMessageBox::warning(this,"警告", "executable file路径不能为空!");
            return;
        }
        else if(filePath_2.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_vocabulary路径不能为空!");
            return;
        }
        else if(filePath_3.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_settings路径不能为空!");
            return;
        }
        else if(filePath_4.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_image_folder1路径不能为空!");
            return;
        }
        else if(filePath_7.isEmpty())
        {
            QMessageBox::warning(this,"警告", "path_to_times_file路径不能为空!");
            return;
        }
        else
        {
            QString str = "gnome-terminal -- bash -c 'export LD_LIBRARY_PATH=/home/ubuntu/slam/ORB_SLAM2/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/g2o/lib:/home/ubuntu/slam/ORB_SLAM2/Thirdparty/DBoW2/lib:$LD_LIBRARY_PATH;";
            QString str2 = "'&";
            str += filePath;
            str += file;
            str += filePath_2;
            str += file;
            str += filePath_3;
            str += file;
            str += filePath_4;
            str += file;
            str += filePath_7;
            str += str2;
            QByteArray bt_1;
            bt_1.append(str);
            const char * proc_1 = bt_1.data();
            system(proc_1);
        }
    });



    //点击按钮启动小车
    connect(ui->pushButton_10, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/kobuki_ws/devel/setup.bash;source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_bringup minimal.launch'&");
    });



    //点击按钮启动键盘
    connect(ui->pushButton_8, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/turtlebot_exploration_ws/devel/setup.bash;roslaunch turtlebot_teleop keyboard_teleop.launch'&");
    });



    //点击按钮启动ZED
    connect(ui->pushButton_18, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source ~/tools/zed/devel/setup.bash;"
               "roslaunch zed_wrapper zed.launch'&");
    });



    //点击按钮启动ORB—SLAM2
    connect(ui->pushButton_19, &QPushButton::clicked, [=](){
        system("gnome-terminal -- bash -c 'source /opt/ros/melodic/setup.bash;source /home/ubuntu/qt_project/slam_visual_2/bash/orb.sh;read " "'&");
    });


}


orbslam2::~orbslam2()
{
    delete ui;
}
