#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class LoginDlg;
}

class LoginDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDlg(QWidget *parent = 0);
    ~LoginDlg();

private slots:
    void on_acceptPushButton_clicked();

private:
    Ui::LoginDlg *ui;
};

#endif // LOGIN_H
