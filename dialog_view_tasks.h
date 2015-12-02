#ifndef DIALOG_VIEW_TASKS_H
#define DIALOG_VIEW_TASKS_H

#include <QDialog>
#include <QtSql>

#include <QTimer>
#include <QDate>

namespace Ui {
class Dialog_view_tasks;
}

class Dialog_view_tasks : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_view_tasks(QWidget *parent = 0);
    ~Dialog_view_tasks();
    QTimer * timer_tasks_upd = new QTimer(this);

private:
    Ui::Dialog_view_tasks *ui;
public slots:
    void load_tasks();
    void settings_ui();
    void clear_task_table();
};

#endif // DIALOG_VIEW_TASKS_H
