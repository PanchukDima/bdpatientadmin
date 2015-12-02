#ifndef DIALOG_LOGIN_H
#define DIALOG_LOGIN_H

#include <QDialog>
#include <QSql>
#include <QSqlDatabase>
#include <QSettings>

namespace Ui {
class Dialog_login;
}

class Dialog_login : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_login(QWidget *parent = 0);
    ~Dialog_login();

private:
    Ui::Dialog_login *ui;
public slots:
    void login_db();
    void quit_app();
    void clear_label_status();
};

#endif // DIALOG_LOGIN_H
