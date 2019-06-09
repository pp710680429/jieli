#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStandardItemModel>
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Init()
{
    hide();
    QFile f("libcss.dll");
    QTextStream tmpt(&f);
    if(f.open(QIODevice ::ReadWrite | QIODevice :: Text)){
        QString s = QString( f.readAll());
        int k = s.toInt();
        if (k == 0){
            QMessageBox::information(this,tr("提示"),tr("请激活或者卸载！"),QMessageBox::Ok);
            close();
            this->deleteLater();
        }else {
            k = k-1;
            tmpt.seek(0);
            tmpt << k;
            show();
        }
    }

    mProcess = new QProcess;
    fileout = new QFile("fr.txt");
    if(fileout->open(QIODevice :: WriteOnly | QIODevice :: Text)){
        qDebug()<< "文件打开失败";
       // QMessageBox::warning(this,tr("提示"),tr("文件打开失败，文件是否被其它程序占用？"),QMessageBox::Ok);
}

    ui->pushButton->setEnabled(false);
    ui->tableView_zhijiejiedianhezai->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_kedongzhiyueshu->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_feijiedianhezai->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_jiedianzuobiao->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_danyunjiedian->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

void MainWindow::setItemDataToFile(QTextStream &out,QStandardItemModel *models)
{
    QStringList sstr;
    for (int i = 0 ;i < models->rowCount() ; i++) {
        sstr.clear();
        for (int j =0; j < models->columnCount(); j++) {
            sstr<< models->item(i,j)->text();
        }
        for (QString s : sstr) {
            out << s << " ";
        }
        out << "\n";
    }
}

void MainWindow::on_pushButton_clicked()
{
    static QTextStream out(fileout);
    out.seek(0);
    out << ui->lineEdit_nn->text() << " "
        << ui->lineEdit_ne->text() << " "
        << ui->lineEdit_nf->text() << " "
        << ui->lineEdit_nd->text() << " "
        << ui->lineEdit_ndf->text() << " "
        << ui->lineEdit_npj->text() << " "
        << ui->lineEdit_npe->text() << "\n";

    setItemDataToFile(out,model);
    setItemDataToFile(out,model3);
    setItemDataToFile(out,modelx);
    setItemDataToFile(out,model5);
    setItemDataToFile(out,model6);

    out.flush();

    QString runPath = QCoreApplication::applicationDirPath();
    static QString cmd = "translate" ;//runPath.append("");
    mProcess->start(cmd);
    mProcess->waitForFinished();
    mResultWidget = new ReslutWidget;
    mResultWidget->show();
}

void MainWindow::on_pushButton_2_clicked()
{

    if(
            ui->lineEdit_nn->text().isEmpty() &
            ui->lineEdit_nf->text().isEmpty() &
            ui->lineEdit_nd->text().isEmpty() &
            ui->lineEdit_ndf->text().isEmpty() &
            ui->lineEdit_ne->text().isEmpty() &
            ui->lineEdit_npj->text().isEmpty() &
            ui->lineEdit_npe->text().isEmpty()
            )
        return;

    ui->pushButton->setEnabled(true);

    //结点坐标
    model = new QStandardItemModel(this);
    for (int i = 0; i < ui->lineEdit_nn->text().toInt(); i++ ) {
        model->setItem(i, 0, new QStandardItem(QString("%1").arg(QString::number(i+1))));
        model->setItem(i, 1, new QStandardItem("0"));
        model->setItem(i, 2, new QStandardItem("0"));
    }
    model->setHeaderData(0,Qt::Horizontal,QVariant("序号i"));
    model->setHeaderData(1,Qt::Horizontal,QVariant("坐标(x)"));
    model->setHeaderData(2,Qt::Horizontal,QVariant("坐标(y)"));
    ui->tableView_jiedianzuobiao->setModel(model);

    //单元始末端结点号和EA、EI值
    model3 = new QStandardItemModel(this);
    for (int i = 0; i < ui->lineEdit_ne->text().toInt(); i++ ) {
        model3->setItem(i, 0, new QStandardItem(QString("%1").arg(QString::number(i+1))));
        model3->setItem(i, 1, new QStandardItem("0"));
        model3->setItem(i, 2, new QStandardItem("0"));
        model3->setItem(i, 3, new QStandardItem("0"));
        model3->setItem(i, 4, new QStandardItem("0"));
    }
    model3->setHeaderData(0,Qt::Horizontal,QVariant("单元号i"));
    model3->setHeaderData(1,Qt::Horizontal,QVariant("始端号jl[i]"));
    model3->setHeaderData(2,Qt::Horizontal,QVariant("末端号jl[i]"));
    model3->setHeaderData(3,Qt::Horizontal,QVariant("抗拉刚度EA[i]"));
    model3->setHeaderData(4,Qt::Horizontal,QVariant("抗压刚度EI[i]"));
    ui->tableView_danyunjiedian->setModel(model3);

    //直接结点荷载

    modelx = new QStandardItemModel(this);

    for (int i = 0; i < ui->lineEdit_npj->text().toInt(); i++ ) {
        modelx->setItem(i, 0, new QStandardItem(QString("%1").arg(QString::number(i+1))));
        modelx->setItem(i, 1, new QStandardItem("0"));
        modelx->setItem(i, 2, new QStandardItem("0"));
        modelx->setItem(i, 3, new QStandardItem("0"));
        modelx->setItem(i, 4, new QStandardItem("0"));
    }
    modelx->setHeaderData(0,Qt::Horizontal,QVariant("编号i"));
    modelx->setHeaderData(1,Qt::Horizontal,QVariant("结点号mj[i]"));
    modelx->setHeaderData(2,Qt::Horizontal,QVariant("Fn"));
    modelx->setHeaderData(3,Qt::Horizontal,QVariant("Fs"));
    modelx->setHeaderData(4,Qt::Horizontal,QVariant("M"));
    ui->tableView_zhijiejiedianhezai->setModel(modelx);

    //直接结点荷载
    model5 = new QStandardItemModel(this);
    for (int i = 0; i < ui->lineEdit_npe->text().toInt(); i++ ) {
        model5->setItem(i, 0, new QStandardItem(QString("%1").arg(QString::number(i+1))));
        model5->setItem(i, 1, new QStandardItem("0"));
        model5->setItem(i, 2, new QStandardItem("0"));
        model5->setItem(i, 3, new QStandardItem("0"));
        model5->setItem(i, 4, new QStandardItem("0"));
        model5->setItem(i, 5, new QStandardItem("0"));
        model5->setItem(i, 6, new QStandardItem("0"));
    }
    model5->setHeaderData(0,Qt::Horizontal,QVariant("编号i"));
    model5->setHeaderData(1,Qt::Horizontal,QVariant("单元号mf[i]"));
    model5->setHeaderData(2,Qt::Horizontal,QVariant("荷载类型ind[i]"));
    model5->setHeaderData(3,Qt::Horizontal,QVariant("a aq[i]"));
    model5->setHeaderData(4,Qt::Horizontal,QVariant("b bq[i]"));
    model5->setHeaderData(5,Qt::Horizontal,QVariant("q1"));
    model5->setHeaderData(6,Qt::Horizontal,QVariant("q2"));
    ui->tableView_feijiedianhezai->setModel(model5);

    //可去支座中的约束条件
    //qDebug() << ui->lineEdit_ndf->text();
    model6 = new QStandardItemModel(this);
    for (int i = 0; i < ui->lineEdit_ndf->text().toInt(); i++ ) {
        model6->setItem(i, 0, new QStandardItem(QString("%1").arg(QString::number(i+1))));
        model6->setItem(i, 1, new QStandardItem("0"));
        model6->setItem(i, 2, new QStandardItem("0"));
    }
    model6->setHeaderData(0,Qt::Horizontal,QVariant("编号i"));
    model6->setHeaderData(1,Qt::Horizontal,QVariant("位移分量号ibd[i]"));
    model6->setHeaderData(2,Qt::Horizontal,QVariant("位移值[i]"));
    ui->tableView_kedongzhiyueshu->setModel(model6);
}
