#include "dialog_delete_user.h"
#include "ui_dialog_delete_user.h"

Dialog_delete_user::Dialog_delete_user(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_delete_user)
{
    ui->setupUi(this);
}

Dialog_delete_user::~Dialog_delete_user()
{
    delete ui;
}
void Dialog_delete_user::setParam(QString id, QString name)
{
    global_id = id;
    ui->label_username->setText(name);
}
