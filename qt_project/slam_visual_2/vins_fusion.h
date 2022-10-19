#ifndef VINS_FUSION_H
#define VINS_FUSION_H

#include <QWidget>
#include <QString>

namespace Ui {
class vins_fusion;
}

class vins_fusion : public QWidget
{
    Q_OBJECT

public:
    explicit vins_fusion(QWidget *parent = 0);
    ~vins_fusion();

private:
    Ui::vins_fusion *ui;

    QString filePath;
    QString filePath_2;
};

#endif // VINS_FUSION_H
