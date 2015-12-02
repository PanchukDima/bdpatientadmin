#ifndef DIALOG_CONTROL_USER_RIGHT_H
#define DIALOG_CONTROL_USER_RIGHT_H

#include <QDialog>

namespace Ui {
class Dialog_control_user_right;
}

class Dialog_control_user_right : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_control_user_right(QWidget *parent = 0);
    ~Dialog_control_user_right();

private:
    Ui::Dialog_control_user_right *ui;
public slots:
    void setParam(int, QString);
};

#endif // DIALOG_CONTROL_USER_RIGHT_H
