#include "leture.h"
#include "ui_leture.h"
//#include "datedelegate.h"
#include "leteratureeditdialog.h"

#include <QSqlRecord>
#include <QDebug>


LetureDlg::LetureDlg(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LetureDlg)
{
    ui->setupUi(this);
    ui->pushButton->hide();


    model = new QSqlRelationalTableModel(this);
    model->setTable("leterature");
    model->setRelation(Leterature_Levelid,
                       QSqlRelation("level","id","level_name"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(Leterature_Name, Qt::AscendingOrder);
    model->setHeaderData(Leterature_Id, Qt::Horizontal, tr("id"));
    model->setHeaderData(Leterature_Name, Qt::Horizontal, tr("文献名"));
    model->setHeaderData(Leterature_Journal, Qt::Horizontal, tr("期刊"));
    model->setHeaderData(Leterature_Levelid, Qt::Horizontal, tr("期刊级别"));
    model->setHeaderData(Leterature_Author, Qt::Horizontal, tr("作者"));
    model->setHeaderData(Leterature_PostDate, Qt::Horizontal, tr("发表日期"));
    model->setHeaderData(Leterature_Summary, Qt::Horizontal, tr("个人总结"));
    model->setHeaderData(Leterature_Other, Qt::Horizontal, tr("其他"));
    model->select();

    ui->tableView->setModel(model);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setColumnHidden(Leterature_Id, true);
    ui->tableView->resizeColumnsToContents();
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QHeaderView *header = ui->tableView->horizontalHeader();
    header->setStretchLastSection(true);

    //DateDelegate dateDelegate;
    //ui->tableView->setItemDelegateForColumn(4, &dateDelegate);

    //ui->tableView->setItemDelegateForColumn(5,QAbstractItemDelegate::);

}

LetureDlg::~LetureDlg()
{
    delete ui;
}

void LetureDlg::on_pushButton_2_clicked()
{
    /*
    model->database().transaction();
    if (model->submitAll()){
        model->database().commit();
    }else {
        model->database().rollback();
        QMessageBox::warning(this, tr("tableModel"),
                             tr("数据库错误：%1")
                             .arg(model->lastError().text()));
    }
    */
    int leteratureId = -1;
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()){
        QSqlRecord record = model->record(index.row());
        leteratureId = record.value(Leterature_Id).toInt();
    } else {
        QMessageBox::warning(this, tr("警告"), tr("请选中修改行！"));
        return;
    }
    LeteratureEditDialog dialog(leteratureId, this);
    dialog.exec();
    //updateLeteratureView();
    model->select();

}

void LetureDlg::updateLeteratureView()
{
    QModelIndex index = ui->tableView->currentIndex();
    if (index.isValid()) {
        QSqlRecord record = model->record(index.row());
        int id = record.value("id").toInt();
        model->setFilter(QString("leteratureid = %1").arg(id));

    } else {
        model->setFilter("leteratureid = -1");

    }
    model->select();
    ui->tableView->horizontalHeader()->setVisible(model->rowCount()>0);
}

//void LetureDlg::on_pushButton_clicked()
//{
//    model->revertAll();
//}

void LetureDlg::on_pushButton_8_clicked()
{
    QString name = ui->lineEdit->text();
    model->setFilter(tr("name = '%1' ").arg(name));

    model->select();

}

void LetureDlg::on_pushButton_9_clicked()
{
    model->setTable("leterature");
    model->setRelation(Leterature_Levelid,
                       QSqlRelation("level","id","level_name"));
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setSort(Leterature_Name, Qt::AscendingOrder);
    model->setHeaderData(Leterature_Id, Qt::Horizontal, tr("id"));
    model->setHeaderData(Leterature_Name, Qt::Horizontal, tr("文献名"));
    model->setHeaderData(Leterature_Journal, Qt::Horizontal, tr("期刊"));
    model->setHeaderData(Leterature_Levelid, Qt::Horizontal, tr("期刊级别"));
    model->setHeaderData(Leterature_Author, Qt::Horizontal, tr("作者"));
    model->setHeaderData(Leterature_PostDate, Qt::Horizontal, tr("发表日期"));
    model->setHeaderData(Leterature_Summary, Qt::Horizontal, tr("个人总结"));
    model->setHeaderData(Leterature_Other, Qt::Horizontal, tr("其他"));
    model->select();
}

void LetureDlg::on_pushButton_7_clicked()
{
    int curRow = ui->tableView->currentIndex().row();

    model->removeRow(curRow);

    int ok = QMessageBox::warning(this, tr("删除当前行！"),
                                  tr("你确定删除选中的文献信息？"),
                                  QMessageBox::Yes, QMessageBox::No);
    if (ok == QMessageBox::No){
        model->revertAll();
    } else {
        model->submitAll();
    }
}

void LetureDlg::on_pushButton_3_clicked()
{
    int leteratureId = -1;
    LeteratureEditDialog dialog(leteratureId, this);
    dialog.exec();
    model->select();

}

void LetureDlg::on_pushButton_clicked()
{
    EditLeteratureLevel dialog(this);
    dialog.exec();
    model->select();
}
