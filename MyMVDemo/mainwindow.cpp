#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTableView>
#include <QHeaderView>
#include <QSplitter>
#include<QVBoxLayout>
#include "itemmodel.h"
#include "itemobject.h"
#include "QItemSelectionModel"
#include "mylistitemdelegege.h"
#include<QListView>
#include<QTreeView>
#include<QDebug>
#include<QListWidget>
#include<QPixmap>
#include "mytableviewstyledelegate.h"
#include<QModelIndex>
#include"mylineitemdelegate.h"
#include "tablecheckedheader.h"
#include "checkboxdelegate.h"
void GetData(QList<ItemObject* > &data)
{
    QString strPath(":/MyImages/folder.png");
    for(int i=0;i<5;i++)
    {
        ItemObject* item=new ItemObject();
        item->setName("name"+QString::number(i));
        item->setDesc("desc"+QString::number(i));
        item->setMyIcon(strPath);
        for(int j=0;j<i+1;j++)
        {
            ItemObject* child=new ItemObject(item);
            child->setName("child "+QString::number(j));
            child->setMyIcon(strPath);
            item->appendChild(child);
        }
        data.append(item);
    }
}
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    //:/image/cat.jpg

    ui->setupUi(this);

    QString imagepath = ":/new/prefix1/folder.png";
    QPixmap image0(imagepath);
    QPixmap image = image0.scaled(QSize(100,100));
    qDebug() << image.size();
    QIcon myIcon =  QIcon(image);



    QSplitter *page= new QSplitter();

    //customer
    QList<QVariant> title;
    title<<"one"<<"two";

    QList<ItemObject*> values;
    GetData(values);
    data =new ItemModel(Q_NULLPTR);
    data->setHeaderTitle(title);
    data->BindingData(values);
    selections = new QItemSelectionModel(data);

    table = new QTableView;
    table->setModel(data);
    table->setSelectionModel(selections);
    table->setItemDelegate(new MyTableViewStyleDelegate());
    table->horizontalHeader()->setSectionsMovable(true);
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->verticalHeader()->setSectionsMovable(true);
    table->horizontalHeader()->setStretchLastSection(true);
    // Set StaticContents to enable minimal repaints on resizes.
    table->viewport()->setAttribute(Qt::WA_StaticContents);
    table->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(table, SIGNAL(customContextMenuRequested(QPoint)),SLOT(customMenuRequested(QPoint)));

    //table->setStyleSheet("QTableView{background-color: rgb(250, 250, 115);" "alternate-background-color: rgb(141, 163, 215);}");
    //table->setItemDelegateForColumn(0,new MyLineItemDelegate());
    table->setItemDelegateForColumn(0,new CheckBoxDelegate(table));

    table->setItemDelegateForColumn(1,new ReadOnlyDelegate());
    table->setSelectionBehavior(QAbstractItemView::SelectRows);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    table->setIconSize(QSize(1,1));
    //header checkbox
    TableCheckedHeader *m_customHeader = NULL;
    m_customHeader = new TableCheckedHeader(Qt::Horizontal, this);
    table->setHorizontalHeader(m_customHeader);
    connect(m_customHeader, SIGNAL(toggled(bool)), this, SLOT(_headertoggled(bool)));
    page->addWidget(table);


    QTreeView *tree = new QTreeView;
    tree->setModel(data);
    tree->setSelectionModel(selections);

    tree->setUniformRowHeights(true);
    tree->header()->setStretchLastSection(false);
    tree->viewport()->setAttribute(Qt::WA_StaticContents);
    // Disable the focus rect to get minimal repaints when scrolling on Mac.
    tree->setAttribute(Qt::WA_MacShowFocusRect, false);
    page->addWidget(tree);

    list = new QListView;
    //QObject::connect(list,SIGNAL(doubleClicked(QModelIndex),this,SLOT(doubleClicked(QModelIndex))));
    list->setModel(data);
    list->setIconSize(QSize(80,80));

    list->setItemDelegate(new MyListItemDelegege());
    list->setSelectionModel(selections);
    list->setSpacing(5);
    list->setViewMode(QListView::IconMode);
    list->setDragEnabled(false);
    list->setSelectionRectVisible(false);
    //list->setSelectionMode(QAbstractItemView::ExtendedSelection);
    list->setAlternatingRowColors(false);
    list->setResizeMode(QListWidget::Adjust);
    //list->viewport()->setAttribute(Qt::WA_StaticContents);

    list->setAttribute(Qt::WA_MacShowFocusRect, true);
    //list->setItemDelegateForColumn(1,new MyLineItemDelegate());

    list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //menu
    list->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(list,SIGNAL(customContextMenuRequested(QPoint)),SLOT(CustomListMenuRequested(QPoint)));
    page->addWidget(list);




    this->setCentralWidget(page);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IniMenu()
{
    myMenu =new QMenu();
    reNameAction =new QAction(this);
    reNameAction->setText("reName");

}

void MainWindow::customMenuRequested(QPoint pos)
{
    QModelIndex index=selections->currentIndex();//table->indexAt(pos);
    ItemObject *item=static_cast<ItemObject*>(index.internalPointer());
    if(item)
    {
        //        QMenu *menu=new QMenu(this);
        //           menu->addAction(new QAction("Action 1", this));
        //           menu->addAction(new QAction("Action 2", this));
        //           menu->addAction(new QAction("Action 3", this));
        table->setEditTriggers(QAbstractItemView::AllEditTriggers);
        table->edit(index);
        //menu->popup(table->viewport()->mapToGlobal(pos));
        table->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void MainWindow::customHeaderMenuRequested(QPoint pos)
{

}

void MainWindow::CustomListMenuRequested(QPoint pos)
{
    QModelIndex index=selections->currentIndex();//table->indexAt(pos);
    ItemObject *item=static_cast<ItemObject*>(index.internalPointer());

    if(item)
    {
        qDebug()<<index.row()<<index.column()<<"name"<<item->getName();
        //        QMenu *menu=new QMenu(this);
        //           menu->addAction(new QAction("Action 1", this));
        //           menu->addAction(new QAction("Action 2", this));
        //           menu->addAction(new QAction("Action 3", this));
        list->setEditTriggers(QAbstractItemView::AllEditTriggers);
        list->edit(index);
        //menu->popup(table->viewport()->mapToGlobal(pos));
        list->setEditTriggers(QAbstractItemView::NoEditTriggers);
    }
}

void MainWindow::resizeEvent(QResizeEvent *)
{
//    table->setColumnWidth(0, this->width()/3);
//        table->setColumnWidth(1, this->width()/3);
//        table->setColumnWidth(2, this->width()/3);
    //QMainWindow::resizeEvent(event);
}
