#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialog_login.h"
#include "dialog_control_user.h"
#include "dialog_control_user_right.h"
#include "dialog_delete_user.h"
#include "dialog_delete_user_right.h"
#include "dialog_view_tasks.h"
#include <QtSql>
#include <QTimer>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QStandardItemModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    QTimer * timer_tasks = new QTimer(this);


private:
    Ui::MainWindow *ui;
public slots:
    void get_users();
    void settings_ui();
    void get_user_right();
    void checkedItemTree(QTreeWidgetItem*, int column);
    void clear_users_table();
    void add_user();
    void edit_user();
    void del_user();
    void save_user_right();
    void get_count_tasks();
    void view_tasks();
};

#endif // MAINWINDOW_H
