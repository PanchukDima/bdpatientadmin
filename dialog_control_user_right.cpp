#include "dialog_control_user_right.h"
#include "ui_dialog_control_user_right.h"

Dialog_control_user_right::Dialog_control_user_right(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_control_user_right)
{
    ui->setupUi(this);
}

Dialog_control_user_right::~Dialog_control_user_right()
{
    delete ui;
}
void Dialog_control_user_right::setParam(int param, QString id)
{

}
