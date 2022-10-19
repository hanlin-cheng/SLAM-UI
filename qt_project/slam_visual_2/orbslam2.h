#ifndef ORBSLAM2_H
#define ORBSLAM2_H

#include <QWidget>
#include <QString>
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

namespace Ui {
class orbslam2;
}

class orbslam2 : public QWidget
{
    Q_OBJECT

public:
    explicit orbslam2(QWidget *parent = 0);
    ~orbslam2();

private:
    Ui::orbslam2 *ui;

    QString filePath;
    QString filePath_2;
    QString filePath_3;
    QString filePath_4;
    QString filePath_5;
    QString filePath_6;
    QString filePath_7;
    QString file = " ";

};

#endif // ORBSLAM2_H
