#include "dialog_view_tasks.h"
#include "ui_dialog_view_tasks.h"

Dialog_view_tasks::Dialog_view_tasks(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_view_tasks)
{
    ui->setupUi(this);

    settings_ui();
    load_tasks();
    connect(timer_tasks_upd,SIGNAL(timeout()),this,SLOT(load_tasks()));

}

Dialog_view_tasks::~Dialog_view_tasks()
{
    delete ui;
}
void Dialog_view_tasks::settings_ui()
{
    QTableWidget * tasks_table = ui->tableWidget_task_table; //Основная таблица

    QTableWidgetItem * name_1_collumn_tasks_table = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_tasks_table = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_tasks_table = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_tasks_table = new QTableWidgetItem();

    tasks_table->setColumnCount(4);

    name_1_collumn_tasks_table->setText("Номер");
    name_2_collumn_tasks_table->setText("Кто добавил");
    name_3_collumn_tasks_table->setText("Что добавил");
    name_4_collumn_tasks_table->setText("Статус");

    tasks_table->setHorizontalHeaderItem(1,name_1_collumn_tasks_table);
    tasks_table->setHorizontalHeaderItem(2,name_2_collumn_tasks_table);
    tasks_table->setHorizontalHeaderItem(3,name_3_collumn_tasks_table);
    tasks_table->setHorizontalHeaderItem(4,name_4_collumn_tasks_table);

}
void Dialog_view_tasks::clear_task_table()
{
    int c =0;
    ui->tableWidget_task_table->clear();
    for (c = ui->tableWidget_task_table->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_task_table->removeRow(c);
    }

}

void Dialog_view_tasks::load_tasks()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    clear_task_table();
    QString current;
    current = QDate::currentDate().toString("MM.dd.yyyy");
    if(db.open())
    {
        query.exec("SELECT \
                   logs.id, \
                   staff.fname, \
                   staff.name, \
                   staff.mname,\
                   logs.text, \
                   logs.date_add \
                 FROM \
                   test.logs, \
                   test.staff\
                 WHERE \
                   logs.staff_add_id = staff.id AND\
                   logs.date_add='"+current+"'");
                while (query.next())
        {
            QString id_value = query.value(0).toString();
            QString name_value;
            name_value.append(query.value(1).toString()).append(" ").append(query.value(2).toString()).append(" ").append(query.value(3).toString());
            QString text_value = query.value(4).toString();
            QDate date_value_date = query.value(5).toDate();
            QString date_value=date_value_date.toString("dd.MM.yyyy");

            QTableWidgetItem * id = new QTableWidgetItem();
            QTableWidgetItem * name = new QTableWidgetItem();
            QTableWidgetItem * text = new QTableWidgetItem();
            QTableWidgetItem * date = new QTableWidgetItem();

            id->setText(id_value);
            name->setText(name_value);
            text->setText(text_value);
            date->setText(date_value);

            int last_row = ui->tableWidget_task_table->rowCount();
            ui->tableWidget_task_table->insertRow(last_row);
            ui->tableWidget_task_table->setItem(last_row,0,id);
            ui->tableWidget_task_table->setItem(last_row,1,name);
            ui->tableWidget_task_table->setItem(last_row,2,text);
            ui->tableWidget_task_table->setItem(last_row,3,date);
            timer_tasks_upd->start(60000);
        }
        }
    }

