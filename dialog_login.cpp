#include "dialog_login.h"
#include "ui_dialog_login.h"

Dialog_login::Dialog_login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_login)
{
    ui->setupUi(this);
    connect(ui->pushButton_ok,SIGNAL(clicked()),SLOT(login_db()));
    connect(ui->pushButton_cancel,SIGNAL(clicked()),SLOT(quit_app()));
    connect(ui->lineEdit_login,SIGNAL(selectionChanged()),SLOT(clear_label_status()));
    connect(ui->lineEdit_password,SIGNAL(selectionChanged()),SLOT(clear_label_status()));
}

Dialog_login::~Dialog_login()
{
    delete ui;
}
void Dialog_login::login_db()
{
    QSettings *settings = new QSettings("settings_user.ini",QSettings::IniFormat);
    QString ipdatabase = settings->value("ipdatabase").toString();
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setUserName(ui->lineEdit_login->text());
    db.setPassword(ui->lineEdit_password->text());
    db.setHostName(ipdatabase);
    db.setDatabaseName("newpsqldb");
    db.setPort(5432);
    if(db.open())
    {
        Dialog_login::accept();
    }
    else
    {
        ui->lineEdit_password->setText("");
        ui->label_3->setText("Неправильный логин или пароль");
    }
}
void Dialog_login::quit_app()
{
    exit(0);
}
void Dialog_login::clear_label_status()
{
    ui->label_3->setText("");
}
