#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QStandardItemModel>
#include <QProcess>
#include "reslutwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::MainWindow *ui;

    void Init();
    QFile *filein;
    QFile *fileout;
    QTextStream * in;
    QStandardItemModel* model,* model3,* modelx,* model5,* model6;
    QProcess *mProcess;
    ReslutWidget * mResultWidget;


    void setItemDataToFile(QTextStream &out,QStandardItemModel * models);

};

#endif // MAINWINDOW_H
