#include "dialog_delete_user_right.h"
#include "ui_dialog_delete_user_right.h"

Dialog_delete_user_right::Dialog_delete_user_right(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_delete_user_right)
{
    ui->setupUi(this);
}

Dialog_delete_user_right::~Dialog_delete_user_right()
{
    delete ui;
}
void Dialog_delete_user_right::setParam(QString id, QString name)
{
    global_id = id;
    ui->label_username->setText(name);
}
