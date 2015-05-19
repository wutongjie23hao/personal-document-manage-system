#ifndef LETURE_H
#define LETURE_H

#include <QDialog>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QSqlError>
#include <QSqlRelationalTableModel>

#include <QStandardItemModel>

enum{
    Leterature_Id = 0,
    Leterature_Name = 1,
    Leterature_Journal = 2,
    Leterature_Levelid = 3,
    Leterature_Author = 4,
    Leterature_PostDate = 5,
    Leterature_Summary = 6,
    Leterature_Other = 7
};

enum{
    Relation_Id = 0,
    Relation_Paperid = 1,
    Relation_Leteratureid = 2
};

namespace Ui {
class LetureDlg;
}

class LetureDlg : public QDialog
{
    Q_OBJECT

public:
    explicit LetureDlg(QWidget *parent = 0);
    ~LetureDlg();
    void updateLeteratureView();

private slots:
    void on_pushButton_2_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_clicked();

private:
    Ui::LetureDlg *ui;
    QSqlRelationalTableModel *model;
};

#endif // LETURE_H
