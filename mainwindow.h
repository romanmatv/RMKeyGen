#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDebug>

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
    void on_pushButton_Mashine_clicked();

    void on_pushButton_Secret_clicked();

    void on_pushButton_Serial_clicked();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSettings settings;
    QString privateKe = "8867c7ebf004ed12616a0affbcc63a70677dcea7790fc8dfd1ab9a385c0bf6f80d755d7abdbf704901145e6bbc5e65bf7d8e897671bf7b4ef66ac97dbd3c6824";
};

#endif // MAINWINDOW_H
