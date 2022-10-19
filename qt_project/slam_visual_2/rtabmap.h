#ifndef RTABMAP_H
#define RTABMAP_H

#include <QWidget>
#include <QString>

namespace Ui {
class rtabmap;
}

class rtabmap : public QWidget
{
    Q_OBJECT

public:
    explicit rtabmap(QWidget *parent = 0);
    ~rtabmap();

private:
    Ui::rtabmap *ui;

    QString filePath;
    QString filePath_2;
    QString filename;
};

#endif // RTABMAP_H
