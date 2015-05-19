#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "leture.h"
#include "paper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    LetureDlg *letureDlg = new LetureDlg;
    letureDlg->show();
}

void MainWindow::on_pushButton_2_clicked()
{
    PaperDlg *paperDlg = new PaperDlg(this);
    paperDlg->show();
}
