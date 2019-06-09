#include "reslutwidget.h"
#include "ui_reslutwidget.h"

#include <QFile>
#include <QTextStream>
#include <QDebug>

ReslutWidget::ReslutWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ReslutWidget)
{
    ui->setupUi(this);

    QFile* file = new QFile("fw.txt");
    if(file->open(QIODevice ::ReadOnly | QIODevice :: Text)){
        ui->textEdit->setText(QString(file->readAll()));
        qDebug() << QString(file->readAll());
    }else {
        ui->textEdit->setText("计算结果未找到");
    }
    file->close();


}

ReslutWidget::~ReslutWidget()
{
    delete ui;
}
