#ifndef DIALOG_DELETE_USER_RIGHT_H
#define DIALOG_DELETE_USER_RIGHT_H

#include <QDialog>

namespace Ui {
class Dialog_delete_user_right;
}

class Dialog_delete_user_right : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_delete_user_right(QWidget *parent = 0);
    ~Dialog_delete_user_right();
    QString global_id;

private:
    Ui::Dialog_delete_user_right *ui;
public slots:
    void setParam(QString,QString);
};

#endif // DIALOG_DELETE_USER_RIGHT_H
