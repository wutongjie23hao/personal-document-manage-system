#include "leteratureeditdialog.h"
#include "ui_leteratureeditdialog.h"

#include <QSqlRecord>

LeteratureEditDialog::LeteratureEditDialog(int id, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LeteratureEditDialog)
{
    ui->setupUi(this);

    tableModel = new QSqlRelationalTableModel(this);
    tableModel->setTable("leterature");
    tableModel->setRelation(Leterature_Levelid,
                            QSqlRelation("level","id","level_name"));
    tableModel->setSort(Leterature_Name, Qt::AscendingOrder);
    tableModel->select();

    relationModel = tableModel->relationModel(Leterature_Levelid);
    ui->comboBox->setModel(relationModel);
    ui->comboBox->setModelColumn(relationModel->fieldIndex("level_name"));

    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::ManualSubmit);
    mapper->setModel(tableModel);
    mapper->setItemDelegate(new QSqlRelationalDelegate);
    mapper->addMapping(ui->lineEdit, Leterature_Name);
    mapper->addMapping(ui->lineEdit_2, Leterature_Journal);
    mapper->addMapping(ui->comboBox, Leterature_Levelid);
    mapper->addMapping(ui->lineEdit_3, Leterature_Author);
    mapper->addMapping(ui->dateEdit, Leterature_PostDate);
    mapper->addMapping(ui->textEdit, Leterature_Summary);
    mapper->addMapping(ui->textEdit_2, Leterature_Other);

    if (id != -1){
        for (int row = 0; row <tableModel->rowCount();++row){
            QSqlRecord record = tableModel->record(row);
            if(record.value(Leterature_Id).toInt()==id){
                mapper->setCurrentIndex(row);
                break;
            }
        }
    }  else {
        int row = 1;
        tableModel->insertRow(row);
        mapper->setCurrentIndex(row);

        ui->lineEdit->clear();
        ui->lineEdit_2->clear();
        ui->lineEdit_3->clear();
        ui->dateEdit->setDate(QDate::currentDate());
        ui->textEdit->clear();
        ui->textEdit_2->clear();

        ui->lineEdit->setFocus();

    }

}

LeteratureEditDialog::~LeteratureEditDialog()
{
    delete ui;
}

void LeteratureEditDialog::on_pushButton_5_clicked()
{
    if (ui->lineEdit->text().isEmpty() || ui->lineEdit_2->text().isEmpty() || ui->lineEdit_3->text().isEmpty() || ui->textEdit->toPlainText().isEmpty()){
        QMessageBox::warning(this, tr("输入警告"),
                                     tr("文献名和期刊为空！"));
    }
    else{
        mapper->submit();
        accept();
    }

    //SLOT(accept());
}
/*
void LeteratureEditDialog::on_pushButton_clicked()
{
    EditLeteratureLevel dialog(this);
    //r = dialog.exec();
    //tableModel->select();
    if (dialog.exec()==QDialog::Accepted){

        relationModel = tableModel->relationModel(Leterature_Levelid);
        ui->comboBox->setModel(relationModel);
        ui->comboBox->setModelColumn(relationModel->fieldIndex("name"));
    }
}
*/

void LeteratureEditDialog::on_pushButton_clicked()
{
    EditLeteratureLevel dialog(this);
    dialog.exec();
    relationModel->select();
    ui->comboBox->setCurrentIndex(1);
}
