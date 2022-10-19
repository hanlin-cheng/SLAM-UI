#ifndef LIOSAM_H
#define LIOSAM_H

#include <QWidget>
#include <QString>

namespace Ui {
class liosam;
}

class liosam : public QWidget
{
    Q_OBJECT

public:
    explicit liosam(QWidget *parent = 0);
    ~liosam();

private slots:



private:
    Ui::liosam *ui;

    QString filePath;
    QString filePath_2;
};

#endif // LIOSAM_H
