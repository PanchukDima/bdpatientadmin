#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Dialog_login login_win;
    if(login_win.exec())
    {
        settings_ui();
        get_count_tasks();
        connect(ui->tableWidget_role,SIGNAL(cellClicked(int,int)),SLOT(get_user_right()));
        connect(ui->pushButton_add_user,SIGNAL(clicked()),SLOT(add_user()));
        connect(ui->pushButton_edit_user,SIGNAL(clicked()),SLOT(edit_user()));
        connect(ui->pushButton_del_user,SIGNAL(clicked()),SLOT(del_user()));
        connect(ui->pushButton_add_right,SIGNAL(clicked()),SLOT(save_user_right()));
        connect(ui->pushButton_tasks,SIGNAL(clicked()),SLOT(view_tasks()));
        connect(timer_tasks,SIGNAL(timeout()),this,SLOT(get_count_tasks()));
        connect(ui->treeWidget,SIGNAL(itemChanged(QTreeWidgetItem*,int)),SLOT(checkedItemTree(QTreeWidgetItem*,int)));


    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::checkedItemTree(QTreeWidgetItem * item, int column)
{
    if(column != 0)
    return;
    Qt::CheckState checkState = item->checkState(0);
    for(int i = 0; i < item->childCount(); ++i)
    {
        item->child(i)->setCheckState(0, checkState);

    }

}

void MainWindow::settings_ui()
{
    QTableWidget* roleTable = ui->tableWidget_role;
    QTableWidgetItem * name_1_collumn_role = new QTableWidgetItem();
    QTableWidgetItem * name_2_collumn_role = new QTableWidgetItem();
    QTableWidgetItem * name_3_collumn_role = new QTableWidgetItem();
    QTableWidgetItem * name_4_collumn_role = new QTableWidgetItem();
    roleTable->setColumnCount(4);
    roleTable->setColumnWidth(0,100);
    roleTable->setColumnWidth(1,100);
    name_1_collumn_role->setText("Номер");
    name_2_collumn_role->setText("Имя пользователя");
    name_3_collumn_role->setText("Логин");
    name_4_collumn_role->setText("Статус");
    roleTable->setHorizontalHeaderItem(0,name_1_collumn_role);
    roleTable->setHorizontalHeaderItem(1,name_2_collumn_role);
    roleTable->setHorizontalHeaderItem(2,name_3_collumn_role);
    roleTable->setHorizontalHeaderItem(3,name_4_collumn_role);
    get_users();
}
void MainWindow::get_users()
{
    QSqlDatabase db = QSqlDatabase::database();
    clear_users_table();
    int last_row = ui->tableWidget_role->rowCount();
    if (db.open())
    {

        ui->statusBar->showMessage("подключенно");
        QSqlQuery query1;
        QString sqlquery;
        sqlquery = "SELECT users.id, staff.fname, staff.name, staff.mname, users.user_login, staff.status FROM test.staff, test.users WHERE staff.id = users.staff_id";
        query1.exec(sqlquery);

        while (query1.next())
        {


            QString id_value = query1.value(0).toString();
            QString name_value;
            name_value.append(query1.value(1).toString()).append(" ").append(query1.value(2).toString()).append(" ").append(query1.value(3).toString());
            QString login_value = query1.value(4).toString();
            QString status_value = query1.value(5).toString();

            switch (status_value.toInt()) {
            case 0:
                status_value="Работает";
                break;
            case 1:
                status_value="В отпуске";
                break;
            }

            QTableWidgetItem * id = new QTableWidgetItem();
            QTableWidgetItem * name = new QTableWidgetItem();
            QTableWidgetItem * login = new QTableWidgetItem();
            QTableWidgetItem * status = new QTableWidgetItem();

            id->setText(id_value);
            name->setText(name_value);
            login->setText(login_value);
            status->setText(status_value);

            ui->tableWidget_role->insertRow(last_row);
            ui->tableWidget_role->setItem(last_row,0,id);
            ui->tableWidget_role->setItem(last_row,1,name);
            ui->tableWidget_role->setItem(last_row,2,login);
            ui->tableWidget_role->setItem(last_row,3,status);

        }
    }
}
void MainWindow::get_user_right()
{
    ui->treeWidget->clear();
    ui->pushButton_add_right->setEnabled(true);
    ui->treeWidget->setColumnWidth(0,200);
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QTreeWidgetItem *group_patients_rights =new QTreeWidgetItem();
    QTreeWidgetItem *add_patients = new QTreeWidgetItem();
    QTreeWidgetItem *edit_patients = new QTreeWidgetItem();
    QTreeWidgetItem *del_patients = new QTreeWidgetItem();
    QTreeWidgetItem *group_dynamic_view_rights =new QTreeWidgetItem();
    QTreeWidgetItem *add_dynamic_view = new QTreeWidgetItem();
    QTreeWidgetItem *edit_dynamic_view = new QTreeWidgetItem();
    QTreeWidgetItem *del_dynamic_view = new QTreeWidgetItem();
    QTreeWidgetItem *group_control_pos_rights =new QTreeWidgetItem();
    QTreeWidgetItem *add_control_pos = new QTreeWidgetItem();
    QTreeWidgetItem *edit_control_pos = new QTreeWidgetItem();
    QTreeWidgetItem *del_control_pos = new QTreeWidgetItem();
    QTreeWidgetItem *add_today_control_pos = new QTreeWidgetItem();

    group_patients_rights->setText(0,tr("Работа с пациентами"));
    group_patients_rights->setText(1,tr("Добавлять, Изменять, Удалять"));
    add_patients->setText(0,tr("Добавлять Пациента"));
    edit_patients->setText(0,tr("Изменять Пациента"));
    del_patients->setText(0,tr("Удалять Пациента"));

    group_dynamic_view_rights->setText(0,tr("Работа с Таблицей Динамика наблюдения"));
    group_dynamic_view_rights->setText(1,tr("Добавлять, Изменять, Удалять"));
    add_dynamic_view->setText(0,tr("Добавлять Динамику наблюдения"));
    edit_dynamic_view->setText(0,tr("Изменять Динамику наблюдения"));
    del_dynamic_view->setText(0,tr("Удалять Динамику наблюдения"));


    group_control_pos_rights->setText(0,tr("Работа с Таблицей Контроль посещений"));
    group_control_pos_rights->setText(1,tr("Добавлять, Изменять, Удалять, Пришел сегодня"));
    add_control_pos->setText(0,tr("Добавлять Контроль посещений"));
    edit_control_pos->setText(0,tr("Изменять Контроль посещений"));
    del_control_pos->setText(0,tr("Удалять Контроль посещений"));
    add_today_control_pos->setText(0,tr("Метка Пришел сегодня"));

    group_patients_rights->setFlags(group_patients_rights->flags() | Qt::ItemIsUserCheckable);
    group_patients_rights->setCheckState(0,Qt::Checked);
    add_patients->setFlags(add_patients->flags() | Qt::ItemIsUserCheckable);
    edit_patients->setFlags(edit_patients->flags() | Qt::ItemIsUserCheckable);
    del_patients->setFlags(del_patients->flags() | Qt::ItemIsUserCheckable);

    group_dynamic_view_rights->setFlags(group_dynamic_view_rights->flags() | Qt::ItemIsUserCheckable);
    group_dynamic_view_rights->setCheckState(0,Qt::Checked);
    add_dynamic_view->setFlags(add_patients->flags() | Qt::ItemIsUserCheckable);
    edit_dynamic_view->setFlags(edit_patients->flags() | Qt::ItemIsUserCheckable);
    del_dynamic_view->setFlags(del_patients->flags() | Qt::ItemIsUserCheckable);

    group_control_pos_rights->setFlags(group_control_pos_rights->flags() | Qt::ItemIsUserCheckable);
    group_control_pos_rights->setCheckState(0,Qt::Checked);
    add_control_pos->setFlags(add_control_pos->flags() | Qt::ItemIsUserCheckable);
    edit_control_pos->setFlags(edit_control_pos->flags() | Qt::ItemIsUserCheckable);
    del_control_pos->setFlags(del_control_pos->flags() | Qt::ItemIsUserCheckable);
    add_today_control_pos->setFlags(del_control_pos->flags() | Qt::ItemIsUserCheckable);

    if(group_patients_rights->checkState(0))
    {

        add_patients->setCheckState(0,Qt::Checked);
        edit_patients->setCheckState(0,Qt::Checked);
        del_patients->setCheckState(0,Qt::Checked);
    }
    else
    {

        add_patients->setCheckState(0,Qt::Unchecked);
        edit_patients->setCheckState(0,Qt::Unchecked);
        del_patients->setCheckState(0,Qt::Unchecked);
    }

    if(group_dynamic_view_rights->checkState(0))
    {

        add_dynamic_view->setCheckState(0,Qt::Checked);
        edit_dynamic_view->setCheckState(0,Qt::Checked);
        del_dynamic_view->setCheckState(0,Qt::Checked);
    }
    else
    {

        add_dynamic_view->setCheckState(0,Qt::Unchecked);
        edit_dynamic_view->setCheckState(0,Qt::Unchecked);
        del_dynamic_view->setCheckState(0,Qt::Unchecked);
    }

    if(group_control_pos_rights->checkState(0))
    {

        add_control_pos->setCheckState(0,Qt::Checked);
        edit_control_pos->setCheckState(0,Qt::Checked);
        del_control_pos->setCheckState(0,Qt::Checked);
        add_today_control_pos->setCheckState(0,Qt::Checked);
    }
    else
    {

        add_control_pos->setCheckState(0,Qt::Unchecked);
        edit_control_pos->setCheckState(0,Qt::Unchecked);
        del_control_pos->setCheckState(0,Qt::Unchecked);
        add_today_control_pos->setCheckState(0,Qt::Unchecked);
    }


    ui->treeWidget->addTopLevelItem(group_patients_rights);
    group_patients_rights->addChild(add_patients);
    group_patients_rights->addChild(edit_patients);
    group_patients_rights->addChild(del_patients);

    ui->treeWidget->addTopLevelItem(group_dynamic_view_rights);
    group_dynamic_view_rights->addChild(add_dynamic_view);
    group_dynamic_view_rights->addChild(edit_dynamic_view);
    group_dynamic_view_rights->addChild(del_dynamic_view);

    ui->treeWidget->addTopLevelItem(group_control_pos_rights);
    group_control_pos_rights->addChild(add_control_pos);
    group_control_pos_rights->addChild(edit_control_pos);
    group_control_pos_rights->addChild(del_control_pos);
    group_control_pos_rights->addChild(add_today_control_pos);
    int selected_tables = ui->tableWidget_role->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_role->currentRow();
        QString id_user = ui->tableWidget_role->item(cu_row,0)->text();
        qDebug()<<id_user;
        QString str_query = "SELECT\
                rights.insert_patients,\
                rights.delete_patients,\
                rights.update_patients,\
                rights.add_dynamic_view,\
                rights.edit_dynamic_view,\
                rights.del_dynamic_view,\
                rights.add_visits,\
                rights.edit_visits,\
                rights.del_visits,\
                rights.add_today_visits\
                FROM\
                test.rights\
                WHERE\
                rights.user_id=";

        if (db.open())
        {
            query.exec(str_query.append(id_user));

            while (query.next())
            {
                qDebug()<<query.value(0)<<query.value(1)<<query.value(2)<<query.value(3)<<query.value(4)<<query.value(5)<<query.value(6)<<query.value(7)<<query.value(8)<<query.value(9);
                if(query.value(0).toBool())
                {
                    add_patients->setCheckState(0,Qt::Checked);

                }
                else
                {
                    add_patients->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(1).toBool())
                {
                    del_patients->setCheckState(0,Qt::Checked);

                }
                else
                {
                    del_patients->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(2).toBool())
                {
                    edit_patients->setCheckState(0,Qt::Checked);
                }
                else
                {
                    edit_patients->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(3).toBool())
                {
                    add_dynamic_view->setCheckState(0,Qt::Checked);

                }
                else
                {
                    add_dynamic_view->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(4).toBool())
                {
                    edit_dynamic_view->setCheckState(0,Qt::Checked);

                }
                else
                {
                    edit_dynamic_view->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(5).toBool())
                {
                    del_dynamic_view->setCheckState(0,Qt::Checked);
                }
                else
                {
                    del_dynamic_view->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(6).toBool())
                {
                    add_control_pos->setCheckState(0,Qt::Checked);

                }
                else
                {
                    add_control_pos->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(7).toBool())
                {
                    edit_control_pos->setCheckState(0,Qt::Checked);

                }
                else
                {
                    edit_control_pos->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(8).toBool())
                {
                    del_control_pos->setCheckState(0,Qt::Checked);
                }
                else
                {
                    del_control_pos->setCheckState(0,Qt::Unchecked);
                }
                if(query.value(9).toBool())
                {
                    add_today_control_pos->setCheckState(0,Qt::Checked);
                }
                else
                {
                    add_today_control_pos->setCheckState(0,Qt::Unchecked);
                }
                group_control_pos_rights->setExpanded(true);
                group_dynamic_view_rights->setExpanded(true);
                group_patients_rights->setExpanded(true);
            }
        }
    }
}
void MainWindow::save_user_right()
{
    QTreeWidgetItemIterator it(ui->treeWidget);
    QString id_user;
    QString add_patients;
    QString edit_patients;
    QString del_patients;
    QString add_dynamic_view;
    QString edit_dynamic_view;
    QString del_dynamic_view;
    QString add_control_pos;
    QString edit_control_pos;
    QString del_control_pos;
    QString add_today_control_pos;
    ui->pushButton_add_right->setEnabled(false);
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        add_patients="true";
    }
    else
    {
        add_patients="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        edit_patients="true";
    }
    else
    {
        edit_patients="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        del_patients="true";
    }
    else
    {
        del_patients="false";
    }
    ++it;
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        add_dynamic_view="true";
    }
    else
    {
        add_dynamic_view="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        edit_dynamic_view="true";
    }
    else
    {
        edit_dynamic_view="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        del_dynamic_view="true";
    }
    else
    {
        del_dynamic_view="false";
    }
    ++it;
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        add_control_pos="true";
    }
    else
    {
        add_control_pos="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        edit_control_pos="true";
    }
    else
    {
        edit_control_pos="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        del_control_pos="true";
    }
    else
    {
        del_control_pos="false";
    }
    ++it;
    if((*it)->checkState(0)==Qt::Checked)
    {
        add_today_control_pos="true";
    }
    else
    {
        add_today_control_pos="false";
    }

    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    int selected_tables = ui->tableWidget_role->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_role->currentRow();
        id_user = ui->tableWidget_role->item(cu_row,0)->text();

        QString str_query = "UPDATE test.rights\
                SET insert_patients=" + add_patients + ", delete_patients=" + del_patients + ", update_patients=" + edit_patients + ", add_dynamic_view=" + add_dynamic_view + ", edit_dynamic_view=" + edit_dynamic_view + ",\
                    del_dynamic_view=" + del_dynamic_view + ", add_visits="+ add_control_pos+ ", edit_visits="+ edit_control_pos+ ", del_visits="+ del_control_pos+ ",\
                    add_today_visits="+ add_today_control_pos +"\
              WHERE  user_id="+id_user;
        qDebug()<<str_query;
        if (db.open())
        {
            query.exec(str_query);
        }
    }
    get_user_right();

}

void MainWindow::clear_users_table()
{
    int c =0;
    ui->tableWidget_role->clear();
    for (c = ui->tableWidget_role->rowCount()-1; c >= 0; c--)
    {
        ui->tableWidget_role->removeRow(c);
    }
}

void MainWindow::add_user()
{
    Dialog_control_user dialog;
    dialog.setParam(0,"0");
    if(dialog.exec())
    {
        get_users();
    }
}
void MainWindow::edit_user()
{
    int selected_tables = ui->tableWidget_role->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_role->currentRow();
        QString id_user = ui->tableWidget_role->item(cu_row,0)->text();
        Dialog_control_user dialog;
        dialog.setParam(1,id_user);
        if(dialog.exec())
        {
            get_users();
        }
    }

}
void MainWindow::del_user()
{
    int selected_tables = ui->tableWidget_role->selectionModel()->selectedRows().count();
    if (selected_tables == 1)
    {
        int cu_row = ui->tableWidget_role->currentRow();
        QString id_user = ui->tableWidget_role->item(cu_row,0)->text();
        QString user_name = ui->tableWidget_role->item(cu_row,1)->text();
        Dialog_delete_user dialog;
        dialog.setParam(id_user,user_name);
        dialog.exec();
    }
}

void MainWindow::get_count_tasks()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString task_count;
    if(db.open())
    {
        query.exec("SELECT COUNT(id) FROM test.logs WHERE date_add='"+QDate::currentDate().toString("MM.dd.yyyy")+"';");
        while(query.next())
        {
            task_count = query.value(0).toString();
        }
        ui->pushButton_tasks->setText("Сегодня добавлено или обновленно "+task_count);
    }
    timer_tasks->start(60000);

}
void MainWindow::view_tasks()
{
    Dialog_view_tasks dialog;
    dialog.exec();
}
