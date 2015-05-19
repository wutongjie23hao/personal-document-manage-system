#include "employeeform.h"
#include <QSqlRelationalDelegate>
#include <QSqlRecord>
#include <QGridLayout>

EmployeeForm::EmployeeForm(int id, QWidget *parent)
    :QDialog(parent)
{
   nameEdit = new QLineEdit;
   nameLabel = new QLabel(tr("Na&me"));
   nameLabel->setBuddy(nameEdit);

   departmentComboBox = new QComboBox;
   departmentLabel = new QLabel(tr("Depar&tment"));
   departmentLabel->setBuddy(departmentComboBox);

   extensionLineEdit = new QLineEdit;
   extensionLineEdit->setValidator(new QIntValidator(0,99999,this));
   extensionLabel = new QLabel(tr("E&xtension"));
   extensionLabel->setBuddy(extensionLineEdit);

   emailEdit = new QLineEdit;
   emailLabel = new QLabel(tr("&Email:"));
   emailLabel->setBuddy(emailEdit);

   startDateEdit = new QDateEdit;
   startDateEdit->setCalendarPopup(true);
   QDate today = QDate::currentDate();
   startDateEdit->setDateRange(today.addDays(-90),today.addDays(90));
   startDateLabel = new QLabel(tr("&Start Date:"));
   startDateLabel->setBuddy(startDateEdit);

   firstButton = new QPushButton(tr("<<&First"));
   previousButton = new QPushButton(tr("<&Previous"));
   nextButton = new QPushButton(tr("&Next"));
   lastButton = new QPushButton(tr("&Last"));

   addButton = new QPushButton(tr("&Add"));
   deleteButton = new QPushButton(tr("&Delete"));
   closeButton = new QPushButton(tr("&Close"));

   buttonBox = new QDialogButtonBox;
   buttonBox->addButton(addButton,QDialogButtonBox::ActionRole);
   buttonBox->addButton(deleteButton,QDialogButtonBox::ActionRole);
   buttonBox->addButton(closeButton,QDialogButtonBox::ActionRole);

   tableModel = new QSqlRelationalTableModel(this);
   tableModel->setTable("employee");
   tableModel->setRelation(Employee_DepartmentId,
                           QSqlRelation("department","id","name"));
   tableModel->setSort(Employee_Name, Qt::AscendingOrder);
   tableModel->select();

   QSqlTableModel *relationModel =
           tableModel->relationModel(Employee_DepartmentId);
   departmentComboBox->setModel(relationModel);
   departmentComboBox->setModelColumn(
               relationModel->fieldIndex("name"));

   mapper = new QDataWidgetMapper(this);
   mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
   mapper->setModel(tableModel);
   mapper->setItemDelegate(new QSqlRelationalDelegate(this));
   mapper->addMapping(nameEdit,Employee_Name);
   mapper->addMapping(departmentComboBox,Employee_DepartmentId);
   mapper->addMapping(extensionLineEdit,Employee_Extension);
   mapper->addMapping(emailEdit, Employee_Email);
   mapper->addMapping(startDateEdit,Employee_StartDate);

   if (id != -1){
       for (int row = 0; row < tableModel->rowCount(); ++row){
           QSqlRecord record = tableModel->record(row);
           if (record.value(Employee_Id).toInt() == id){
               mapper->setCurrentIndex(row);
               break;
           }
       }
   } else {
       mapper->toFirst();
   }

   connect(firstButton,SIGNAL(clicked()),mapper, SLOT(toFirst()));
   connect(previousButton, SIGNAL(clicked()), mapper, SLOT(toPrevious()));
   connect(nextButton, SIGNAL(clicked()), mapper, SLOT(toNext()));
   connect(lastButton, SIGNAL(clicked()), mapper, SLOT(toLast()));
   connect(addButton, SIGNAL(clicked()), this, SLOT(addEmployee()));
   connect(deleteButton, SIGNAL(clicked()), this, SLOT(deleteEmployee()));
   connect(closeButton, SIGNAL(clicked()), this, SLOT(accept()));

   QGridLayout *mainLayout = new QGridLayout;
   mainLayout->addWidget(firstButton,0,0);
   mainLayout->addWidget(previousButton,0,1);
   mainLayout->addWidget(nextButton,0,2);
   mainLayout->addWidget(lastButton,0,3);
   mainLayout->addWidget(nameLabel,1,0);
   mainLayout->addWidget(nameEdit, 1, 1, 1, 3);
   mainLayout->addWidget(departmentLabel,2,0);
   mainLayout->addWidget(departmentComboBox,2,1, 1, 3);
   mainLayout->addWidget(extensionLabel,3,0);
   mainLayout->addWidget(extensionLineEdit,3,1, 1, 3);
   mainLayout->addWidget(emailLabel,4,0);
   mainLayout->addWidget(emailEdit,4,1, 1, 3);
   mainLayout->addWidget(startDateLabel,5,0);
   mainLayout->addWidget(startDateEdit,5,1, 1, 3);
   mainLayout->addWidget(buttonBox,6,0,1,4);
   setLayout(mainLayout);

}

void EmployeeForm::addEmployee()
{
    int row = mapper->currentIndex();
    mapper->submit();
    tableModel->insertRow(row);
    mapper->setCurrentIndex(row);

    nameEdit->clear();
    extensionLineEdit->clear();
    startDateEdit->setDate(QDate::currentDate());

    nameEdit->setFocus();
}

void EmployeeForm::deleteEmployee()
{
    int row = mapper->currentIndex();
    tableModel->removeRow(row);
    mapper->submit();
    mapper->setCurrentIndex(qMin(row, tableModel->rowCount()-1));
}


