#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "itemmodel.h"
#include<QTableView>
#include<QListView>
#include<QMenu>
#include<QAction>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void IniMenu();
private:
    Ui::MainWindow *ui;
    ItemModel * data;
    QTableView *table;
    QListView *list;
    QMenu * myMenu;
    QAction * reNameAction;

public slots:
    void customMenuRequested(QPoint pos);
    void customHeaderMenuRequested(QPoint pos);
};

#endif // MAINWINDOW_H
