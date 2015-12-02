#include "dialog_control_user.h"
#include "ui_dialog_control_user.h"

Dialog_control_user::Dialog_control_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_control_user)
{
    ui->setupUi(this);
    connect(ui->pushButton_ok,SIGNAL(clicked()),SLOT(sendUser()));
}

Dialog_control_user::~Dialog_control_user()
{
    delete ui;
}
void Dialog_control_user::setParam(int param, QString id)
{
    global_param = param;
    switch (param) {
    case 0:
        global_id = id;
        break;
    case 1:
        global_id = id;
        getUser(id);
        break;
    }
}
void Dialog_control_user::getUser(QString id)
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    if(db.open())
    {
        query.exec("SELECT staff.fname, staff.name, staff.mname, users.user_login, staff.status FROM test.users, test.staff WHERE staff.id = users.staff_id AND users.id ="+id);
        while(query.next())
        {
            ui->lineEdit_fname->setText(query.value(0).toString());
            ui->lineEdit_name->setText(query.value(1).toString());
            ui->lineEdit_mname->setText(query.value(2).toString());
            ui->lineEdit_login->setText(query.value(3).toString());
            switch (query.value(4).toInt()) {
            case 0:
                ui->radioButton_work->setChecked(true);
                ui->radioButton_holiday->setChecked(false);
                break;
            case 1:
                ui->radioButton_work->setChecked(false);
                ui->radioButton_holiday->setChecked(true);
                break;
            }
        }
    }

}
void Dialog_control_user::sendUser()
{
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query;
    QString fname = ui->lineEdit_fname->text();
    QString name = ui->lineEdit_name->text();
    QString mname = ui->lineEdit_mname->text();
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();
    QString retry_password = ui->lineEdit_retry_password->text();
    QString status;
    if(ui->radioButton_work->isChecked())
    {
        status = "0";
    }
    else
    {
        status="1";
    }

    if(db.open()){
        switch (global_param) {
        case 0:
            if(fname =="" || name=="" || mname=="" || login=="" || password=="" || retry_password=="")
            {
                ui->label_status->setText("Не все поля заполнены");
            }
            else
            {
                if(password==retry_password)
                {
                    QCryptographicHash hash(QCryptographicHash::Md5);
                    QByteArray array(password.toStdString().c_str());
                    hash.addData(array);
                    QString password_md5 = hash.result().toHex().data();
                    QString id_staff;
                    QString id_user;
                    query.exec("INSERT INTO test.staff(fname, name, mname, status) VALUES ('"+fname+"','"+name+"','"+mname+"',"+status+") RETURNING id");
                    while(query.next())
                    {
                        id_staff = query.value(0).toString();
                    }
                    query.exec("INSERT INTO test.users( user_login,password_login_md5,staff_id) VALUES ('"+login+"','"+password_md5+"','"+id_staff+"')RETURNING id");
                    while(query.next())
                    {
                        id_user = query.value(0).toString();
                    }
                    query.exec("INSERT INTO test.rights(user_id,select_patients, insert_patients, delete_patients, update_patients, delete_row, add_dynamic_view, edit_dynamic_view, del_dynamic_view, add_visits, edit_visits, del_visits, add_today_visits) VALUES ("+id_user+",'true','true','true','true','false','true','true','true','true','true','true','true')");
                    Dialog_control_user::accept();
                }
            }
            break;
        case 1:
            if(ui->lineEdit_password->text()=="" && ui->lineEdit_retry_password->text()=="")
            {
                //пароль не менялся
                query.exec("UPDATE test.staff SET fname='"+fname+"', name='"+name+"', mname='"+mname+"',status='"+status+"' WHERE id="+global_id);
                query.exec("UPDATE test.users SET user_login='"+login+"' WHERE staff_id = "+global_id);
                Dialog_control_user::accept();
            }
            else
            {
                QCryptographicHash hash(QCryptographicHash::Md5);
                QByteArray array(password.toStdString().c_str());
                hash.addData(array);
                QString password_md5 = hash.result().toHex().data();
                query.exec("UPDATE test.staff SET fname='"+fname+"', name='"+name+"', mname='"+mname+"',status='"+status+"' WHERE id="+global_id);
                query.exec("UPDATE test.users SET user_login='"+login+"',password_login_md5='"+password_md5+"' WHERE staff_id = "+global_id);
                Dialog_control_user::accept();
            }
            break;
        }

    }
    else
    {
        ui->label_status->setText("Пароли не совпадают!");
    }
}

