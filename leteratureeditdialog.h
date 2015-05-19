#ifndef LETERATUREEDITDIALOG_H
#define LETERATUREEDITDIALOG_H

#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSqlRelationalDelegate>
#include <QDataWidgetMapper>

#include "leture.h"
#include "editleteraturelevel.h"

namespace Ui {
class LeteratureEditDialog;
}

class LeteratureEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LeteratureEditDialog(int id, QWidget *parent = 0);
    ~LeteratureEditDialog();

private slots:
    void on_pushButton_5_clicked();

    //void on_pushButton_clicked();

    void on_pushButton_clicked();

private:
    Ui::LeteratureEditDialog *ui;
    QSqlRelationalTableModel *tableModel;
    QDataWidgetMapper *mapper;
    QSqlTableModel *relationModel;
};

#endif // LETERATUREEDITDIALOG_H
