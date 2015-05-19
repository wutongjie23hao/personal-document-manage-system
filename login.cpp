#include <QMessageBox>
#include "login.h"
#include "ui_login.h"

LoginDlg::LoginDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDlg)
{
    ui->setupUi(this);
    bool debugTag = false;
    if (debugTag){
        ui->lineEdit->setText(tr("qt"));
        ui->lineEdit_2->setText(tr("123456"));
    }
}

LoginDlg::~LoginDlg()
{
    delete ui;
}

void LoginDlg::on_acceptPushButton_clicked()
{
    if(ui->lineEdit->text().trimmed()==tr("qt")&&ui->lineEdit_2->text()==tr("123456"))
        accept();
    else{
        QMessageBox::warning(this, tr("警告"), tr("用户名或密码错误!"), QMessageBox::Yes);
        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit->setFocus();
    }
}
