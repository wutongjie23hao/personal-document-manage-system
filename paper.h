#ifndef PAPER_H
#define PAPER_H

#include <QDialog>
#include <QSqlTableModel>
#include <QSqlRelationalTableModel>

enum{
    Paper_Id = 0,
    Paper_Topic = 1,
    Paper_Content = 2
};

namespace Ui {
class PaperDlg;
}

class PaperDlg : public QDialog
{
    Q_OBJECT

public:
    explicit PaperDlg(QWidget *parent = 0);
    ~PaperDlg();

private:
    Ui::PaperDlg *ui;
    QSqlTableModel *paperModel;
    QSqlRelationalTableModel *relationModel;
    int nowPaperId;

private slots:
    void updateLeteratureView();
    void on_pushButton_4_clicked();
    void on_pushButton_10_clicked();
    void on_pushButton_11_clicked();
    void on_pushButton_12_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_5_clicked();
};

#endif // PAPER_H
