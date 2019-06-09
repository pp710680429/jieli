#ifndef RESLUTWIDGET_H
#define RESLUTWIDGET_H

#include <QWidget>

namespace Ui {
class ReslutWidget;
}

class ReslutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ReslutWidget(QWidget *parent = nullptr);
    ~ReslutWidget();

private:
    Ui::ReslutWidget *ui;
};

#endif // RESLUTWIDGET_H
