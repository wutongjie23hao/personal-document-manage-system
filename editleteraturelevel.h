#ifndef EDITLETERATURELEVEL_H
#define EDITLETERATURELEVEL_H

#include <QDialog>
#include <QSqlTableModel>
#include <QMessageBox>

enum {
    Level_id = 0,
    Level_name = 1
};

namespace Ui {
class EditLeteratureLevel;
}

class EditLeteratureLevel : public QDialog
{
    Q_OBJECT

public:
    explicit EditLeteratureLevel(QWidget *parent = 0);
    ~EditLeteratureLevel();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::EditLeteratureLevel *ui;
    QSqlTableModel *levelModel;
};

#endif // EDITLETERATURELEVEL_H
