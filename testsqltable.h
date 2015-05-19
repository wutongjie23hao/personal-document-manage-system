#ifndef TESTSQLTABLE
#define TESTSQLTABLE

#include <QtSql>
#include <QMessageBox>
#include <QTableView>
#include <QHeaderView>
#include <QDialog>
#include <QHBoxLayout>
class TestSqlTable:public QDialog
{
public:
    TestSqlTable()
    {
        bool debugTag = false;
        if (!createConnection())
            qDebug()<<"connection wrong!";//return 1;
        QSqlQuery query;
        query.exec("CREATE TABLE scooter(id INTEGER PRIMARY KEY AUTOINCREMENT, name VARCHAR(40) NOT NULL, maxspeed INTEGER NOT NULL, maxrange INTEGER NOT NULL, weight INTEGER NOT NULL, description VARCHAR(80) NOT NULL)");
        //query.exec("insert into cooter(name,maxspeed,maxrange,weight, description) values('我的车',10,10,10,'我的祖国在希望的田野上')");
        if (debugTag==true)
            query.exec("insert into scooter(name,maxspeed,maxrange,weight, description) values('我的车',10,10,10,'我的祖国在希望的田野上')");
        query.exec("select * from scooter");
        while(query.next())
        {
            int idC = query.value(0).toInt();
            qDebug()<<idC;
        }
        enum{Scooter_Id = 0,Scooter_Name = 1,Scooter_MaxSpeed = 2,Scooter_MaxRange = 3,Scooter_Weight = 4,Scooter_Description =5};
        QSqlTableModel *model = new QSqlTableModel(this);
        model->setTable("scooter");
        model->setSort(Scooter_Name,Qt::AscendingOrder);
        model->setHeaderData(Scooter_Name, Qt::Horizontal, tr("名字"));
        model->setHeaderData(Scooter_MaxSpeed, Qt::Horizontal, tr("MPH"));
        model->setHeaderData(Scooter_MaxRange, Qt::Horizontal, tr("Miles"));
        model->setHeaderData(Scooter_Weight, Qt::Horizontal, tr("Lbs"));
        model->setHeaderData(Scooter_Description, Qt::Horizontal, tr("Description"));
        model->select();
        QTableView *view = new QTableView;
        view->setModel(model);
        view->setSelectionMode(QAbstractItemView::SingleSelection);
        view->setSelectionBehavior(QAbstractItemView::SelectRows);
        view->setColumnHidden(Scooter_Id, true);
        view->resizeColumnsToContents();
        view->setEditTriggers(QAbstractItemView::NoEditTriggers);

        QHeaderView* header = view->horizontalHeader();
        header->setStretchLastSection(true);

        QHBoxLayout *layout = new QHBoxLayout;
        layout->addWidget(view);
        this->setLayout(layout);
    }
    bool createConnection()
    {
        //bool tag = false;
        QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
        dbconn.setDatabaseName("mytest8.db");
        //qDebug() <<dbconn.open()<<endl;
        if(!dbconn.open())
        {
            QMessageBox::critical(0, QObject::tr("Database Error"),
                                  dbconn.lastError().text());
            return false;
        }
        return true;

    }
};
#endif // TESTSQLTABLE

