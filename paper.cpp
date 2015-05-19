#include "paper.h"
#include "ui_paper.h"
#include <QWidget>
#include <leture.h>

#include <QSqlRecord>
#include <QSqlRelationalDelegate>
#include <QSqlQuery>

#include <QDebug>

PaperDlg::PaperDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PaperDlg)
{
    ui->setupUi(this);

    paperModel = new QSqlTableModel(this);
    paperModel->setTable("paper");
    //paperModel->setEditStrategy(QSqlTableModel::on);
    paperModel->setSort(Paper_Topic, Qt::AscendingOrder);
    paperModel->setHeaderData(Paper_Id, Qt::Horizontal, tr("论文id"));
    paperModel->setHeaderData(Paper_Topic, Qt::Horizontal, tr("研究主题"));
    paperModel->setHeaderData(Paper_Content, Qt::Horizontal, tr("主题相关内容"));
    paperModel->select();

    ui->tableView_2->setModel(paperModel);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setColumnHidden(Paper_Id, true);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
    
    relationModel = new QSqlRelationalTableModel(this);
    relationModel->setTable("relation");
    relationModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    relationModel->setRelation(Relation_Leteratureid,
                               QSqlRelation("leterature", "id", "name"));
    relationModel->setSort(Relation_Id, Qt::AscendingOrder);
    relationModel->setHeaderData(Relation_Id, Qt::Horizontal, tr("id"));
    relationModel->setHeaderData(Relation_Paperid, Qt::Horizontal, tr("论文主题"));
    relationModel->setHeaderData(Relation_Leteratureid, Qt::Horizontal, tr("文献名"));
    //relationModel->select();

    ui->tableView->setModel(relationModel);
    ui->tableView->setItemDelegate(new QSqlRelationalDelegate(this));
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->tableView->setColumnHidden(Relation_Id, true);
    ui->tableView->setColumnHidden(Relation_Paperid, true);

    updateLeteratureView();

    connect(ui->tableView_2->selectionModel(), SIGNAL(currentRowChanged(const QModelIndex &,
                                                 const QModelIndex &)),
            this, SLOT(updateLeteratureView()));

}

void PaperDlg::updateLeteratureView()
{
    QModelIndex indexNow = ui->tableView_2->currentIndex();
    if (indexNow.isValid()) {
        QSqlRecord record = paperModel->record(indexNow.row());
        int id = record.value("id").toInt();
        nowPaperId = id;
        relationModel->setFilter(QString("paperid = %1").arg(id));
        ui->label_3->setText(tr("与“%1”相关的文献：").arg(record.value("topic").toString()));
    } else {
        relationModel->setFilter("paperid = -1");
        ui->label_3->setText(tr("文献"));
    }

    //qDebug()<<indexNow.row();
    relationModel->select();

    ui->tableView->horizontalHeader()->setVisible(
                relationModel->rowCount() >= 0);
}

PaperDlg::~PaperDlg()
{
    delete ui;
}

void PaperDlg::on_pushButton_4_clicked()
{
    int row = paperModel->rowCount();
    paperModel->insertRow(row);
    QModelIndex index = paperModel->index(row, Paper_Topic);
    ui->tableView_2->setCurrentIndex(index);
    ui->tableView_2->edit(index);
}

void PaperDlg::on_pushButton_10_clicked()
{
    QModelIndex index = ui->tableView_2->currentIndex();
    if (!index.isValid())
        return;

    QSqlDatabase::database().transaction();
    QSqlRecord record = paperModel->record(index.row());
    int id = record.value(Paper_Id).toInt();
    int numLeterature = 0;

    QSqlQuery query(QString("SELECT COUNT(*) FROM relation"
                            "WHERE paperid = %1").arg(id));
    if (query.next()){
        numLeterature = query.value(0).toInt();
    }
    if (numLeterature > 0){
        int r = QMessageBox::warning(this, tr("删除论文"),
                                     tr("确认删除%1以及它的相关文献？").arg(record.value(Paper_Topic).toString()),
                                     QMessageBox::Yes|QMessageBox::No);
        if (r == QMessageBox::No) {
            QSqlDatabase::database().rollback();
            return;
        }
        query.exec(QString("DELETE FROM relation"
                           "WHERE paperid = %1").arg(id));
    }
    paperModel->removeRow(index.row());
    paperModel->submitAll();
    QSqlDatabase::database().commit();

    updateLeteratureView();
    paperModel->select();
    ui->tableView_2->setFocus();

}

void PaperDlg::on_pushButton_11_clicked()
{
    QString topic = ui->lineEdit_2->text();
    paperModel->setFilter(tr("topic = '%1'").arg(topic));

    paperModel->select();
}

void PaperDlg::on_pushButton_12_clicked()
{
    paperModel->setTable("paper");
    paperModel->select();
    paperModel->setSort(Paper_Topic, Qt::AscendingOrder);
    paperModel->setHeaderData(Paper_Id, Qt::Horizontal, tr("论文id"));
    paperModel->setHeaderData(Paper_Topic, Qt::Horizontal, tr("研究主题"));
    paperModel->setHeaderData(Paper_Content, Qt::Horizontal, tr("主题相关内容"));
    paperModel->select();

    ui->tableView_2->setModel(paperModel);
    ui->tableView_2->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView_2->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView_2->setColumnHidden(Paper_Id, true);
    ui->tableView_2->resizeColumnsToContents();
    ui->tableView_2->horizontalHeader()->setStretchLastSection(true);
}

void PaperDlg::on_pushButton_2_clicked()
{
    int row = relationModel->rowCount();
    relationModel->insertRow(row);
    relationModel->setData(relationModel->index(row, Relation_Paperid), nowPaperId);
    QModelIndex index = relationModel->index(row, Relation_Leteratureid);
    ui->tableView->setCurrentIndex(index);
    ui->tableView->edit(index);
}

void PaperDlg::on_pushButton_3_clicked()
{
    QModelIndex curIndex = ui->tableView->currentIndex();
    if (!curIndex.isValid())
        return;
    relationModel->removeRow(curIndex.row());

    int ok = QMessageBox::warning(this,tr("删除当前行!"), tr("你确定"
                                                               "删除当前行吗？"),
                             QMessageBox::Yes,QMessageBox::No);
    if (ok == QMessageBox::No)
    {
        relationModel->revertAll();
    } else {
        relationModel->submitAll();
    }
}

void PaperDlg::on_pushButton_5_clicked()
{
    relationModel->submitAll();
}
