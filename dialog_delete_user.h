#ifndef DIALOG_DELETE_USER_H
#define DIALOG_DELETE_USER_H

#include <QDialog>

namespace Ui {
class Dialog_delete_user;
}

class Dialog_delete_user : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_delete_user(QWidget *parent = 0);
    ~Dialog_delete_user();
    QString global_id;

private:
    Ui::Dialog_delete_user *ui;
public slots:
    void setParam(QString,QString);
};

#endif // DIALOG_DELETE_USER_H
