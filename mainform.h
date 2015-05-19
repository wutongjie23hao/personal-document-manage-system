#ifndef MAINFORM_H
#define MAINFORM_H

#include <QWidget>
#include <QSqlRelationalTableModel>
#include <QDialogButtonBox>
#include <QPushButton>
#include <QTableView>
#include <QLabel>

enum {
    Department_Id = 0,
    Department_Name = 1,
    Department_LocationId = 2
};

class MainForm : public QWidget
{
    Q_OBJECT
public:
    MainForm();
private slots:
    void updateEmployeeView();
    void addDepartment();
    void deleteDepartment();
    void editEmployees();

private:
    void createDepartmentPanel();
    void createEmployeePanel();

    QSqlRelationalTableModel *departmentModel;
    QSqlRelationalTableModel *employeeModel;
    QWidget *departmentPanel;
    QWidget *employeePanel;

    QLabel *departmentLabel;
    QLabel *employeeLabel;

    QTableView *departmentView;
    QTableView *employeeView;

    QPushButton *addButton;
    QPushButton *deleteButton;
    QPushButton *editButton;
    QPushButton *quitButton;
    QDialogButtonBox *buttonBox;

};

#endif // MAINFORM_H
