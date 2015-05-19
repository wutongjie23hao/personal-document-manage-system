#include "editleteraturelevel.h"
#include "ui_editleteraturelevel.h"

EditLeteratureLevel::EditLeteratureLevel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditLeteratureLevel)
{
    ui->setupUi(this);

    levelModel = new QSqlTableModel(this);
    levelModel->setTable("level");
    levelModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    levelModel->setSort(Level_name, Qt::AscendingOrder);
    levelModel->setHeaderData(Level_id, Qt::Horizontal, tr("id"));
    levelModel->setHeaderData(Level_name, Qt::Horizontal, tr("文献级别"));
    levelModel->select();

    ui->tableView->setModel(levelModel);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(Level_id, true);
    ui->tableView->resizeColumnsToContents();
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setStretchLastSection(true);

}

EditLeteratureLevel::~EditLeteratureLevel()
{
    delete ui;
}

void EditLeteratureLevel::on_pushButton_clicked()
{
    int rowNum = levelModel->rowCount();
    levelModel->insertRow(rowNum);
    QModelIndex index = levelModel->index(rowNum, Level_name);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void EditLeteratureLevel::on_pushButton_2_clicked()
{
    int curRow = ui->tableView->currentIndex().row();
    levelModel->removeRow(curRow);
    int ok = QMessageBox::warning(this,tr("删除当前行!"),tr("你确定"
                                                       "删除当前行吗？"),
                     QMessageBox::Yes,QMessageBox::No);
    if (ok == QMessageBox::No) {
        levelModel->revertAll();
    }
    else {
        levelModel->submitAll();
    }
    levelModel->select();
}

void EditLeteratureLevel::on_pushButton_4_clicked()
{
    levelModel->submitAll();
    levelModel->select();
}
