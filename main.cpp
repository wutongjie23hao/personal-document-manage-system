#include <QApplication>
#include "mainwindow.h"
#include "login.h"
//#include "employeeform.h"
//#include "mainform.h"

#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlError>


int main(int argc, char *argv[])
{
    QSqlDatabase dbconn = QSqlDatabase::addDatabase("QSQLITE");
    dbconn.setDatabaseName("mytest8.db");
    if(!dbconn.open())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),
                              dbconn.lastError().text());
        return 0;
    }

    QApplication app(argc, argv);

    MainWindow *dialog = new MainWindow;
    LoginDlg loginDlg;
    if (loginDlg.exec()==QDialog::Accepted)
    {
        dialog->show();
        return app.exec();
    }
    else return 0;

}
