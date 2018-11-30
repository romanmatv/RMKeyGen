#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "serials.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText(privateKe);
    ui->lineEdit_3->setText(settings.value("key/machine", "").toString());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Mashine_clicked()
{
    QString mach = Serials::generateMachine();
    settings.setValue("key/machine", mach);
    settings.sync();
    ui->lineEdit_3->setText(mach);
}

void MainWindow::on_pushButton_Secret_clicked()
{
    QString secret = Serials::generateSecret(250);
    settings.setValue("key/secret", secret);
    settings.sync();
    ui->lineEdit->setText(secret);
}

void MainWindow::on_pushButton_Serial_clicked()
{
    if (ui->lineEdit->text().isEmpty()||ui->lineEdit_3->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
        return;
    }
    QString serial = Serials::generateSerial(ui->lineEdit->text(), ui->lineEdit_3->text(), ui->lineEdit_2->text());
    ui->lineEdit_4->setText(serial);
}

void MainWindow::on_pushButton_clicked()
{
    QString serial = ui->lineEdit_5->text();
    if (serial.isEmpty()||ui->lineEdit->text().isEmpty()||ui->lineEdit_3->text().isEmpty()||ui->lineEdit_2->text().isEmpty()){
        qDebug() << "enpty";
        return;
    }
    bool result = Serials::validSerial(serial, ui->lineEdit->text(), ui->lineEdit_3->text(), ui->lineEdit_2->text());
    if (result){
        ui->label_5->setText("VALIDED");
    }else{
        ui->label_5->setText("UNVALIDED");
    }
    qDebug() << result;
}
