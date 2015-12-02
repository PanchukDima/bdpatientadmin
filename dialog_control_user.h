#ifndef DIALOG_CONTROL_USER_H
#define DIALOG_CONTROL_USER_H

#include <QDialog>
#include <QSql>
#include <QSqlQuery>
#include <QCryptographicHash>


namespace Ui {
class Dialog_control_user;
}

class Dialog_control_user : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_control_user(QWidget *parent = 0);
    ~Dialog_control_user();
    int global_param;
    QString global_id;

private:
    Ui::Dialog_control_user *ui;
public slots:
    void setParam(int,QString);
    void getUser(QString);
    void sendUser();
};

#endif // DIALOG_CONTROL_USER_H
