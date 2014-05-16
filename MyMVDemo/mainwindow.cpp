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
   ItemModel * data =new ItemModel(Q_NULLPTR);
   data->setHeaderTitle(title);
   data->BindingData(values);
   QItemSelectionModel *selections = new QItemSelectionModel(data);

   QTableView *table = new QTableView;
   table->setModel(data);
   table->setSelectionModel(selections);
   table->setItemDelegate(new MyTableViewStyleDelegate());
   table->horizontalHeader()->setSectionsMovable(true);
   table->setSelectionBehavior(QAbstractItemView::SelectRows);
   table->verticalHeader()->setSectionsMovable(true);
   // Set StaticContents to enable minimal repaints on resizes.
   table->viewport()->setAttribute(Qt::WA_StaticContents);
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

   QListView *list = new QListView;
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
   page->addWidget(list);




   this->setCentralWidget(page);
}

MainWindow::~MainWindow()
{
    delete ui;
}
