﻿#include "itemmodel.h"
#include<QFileIconProvider>
ItemModel::ItemModel(QObject *parent) :
    QAbstractItemModel(parent)
{
}

ItemModel::~ItemModel()
{

}

QModelIndex ItemModel::index(int row, int column, const QModelIndex &parent) const
{
    if(!hasIndex(row,column,parent))
        return QModelIndex();

    ItemObject *parentItem;
    if(!parent.isValid())
    {
        parentItem=rootItem;
    }else
    {
        parentItem=static_cast<ItemObject*>(parent.internalPointer());
    }

    ItemObject *childItem=parentItem->getChild(row);
    if(childItem)
        return createIndex(row,column,childItem); // 展开树形,为子节点建立索引
    else
        return QModelIndex();
}

QModelIndex ItemModel::parent(const QModelIndex &child) const
{
    if(!child.isValid())
    {
        return QModelIndex();
    }
    ItemObject *childItem=static_cast<ItemObject *>(child.internalPointer());
    ItemObject *parentItem=childItem->getParentItem();

    if(parentItem==rootItem)
        return QModelIndex();

    return createIndex(parentItem->currentItemRow(),0,parentItem);
}

int ItemModel::rowCount(const QModelIndex &parent) const
{
    ItemObject *parentItem;

    if(!parent.isValid())
        parentItem=rootItem;
    else
        parentItem=static_cast<ItemObject*>(parent.internalPointer());

    return parentItem->childCount();
}

int ItemModel::columnCount(const QModelIndex &parent) const
{
    return headerTitle.count();
}

QVariant ItemModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    ItemObject *item=static_cast<ItemObject*>(index.internalPointer());





    switch(role)
    {
    case Qt::DecorationRole:
        // 添加图标
        if(index.column()==0)
        {
            return item->getMyIcon();
            //        QFileIconProvider iconProvider;
            //        return iconProvider.icon(QFileIconProvider::File);
        }
        break;
    case Qt::DisplayRole:
        // 显示节点数据值
        if(index.column()==0)
        {
            return item->getName();
        }
        else if(index.column()==1)
        {
            return item->getDesc();
        }
        break;

    case Qt::UserRole:
        return item->getIsChecked();
        break;
    }

    return QVariant();
}

bool ItemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() ) {
        ItemObject *item=static_cast<ItemObject*>(index.internalPointer());
        switch(role)
        {
            case Qt::EditRole|Qt::DisplayRole:

            if(value.toString().length()>0)
            {
                item->setName(value.toString());
                emit dataChanged(index, index);
                return true;
            }
            break;
        case Qt::EditRole|Qt::UserRole:
            item->setIsChecked(value.toBool());
            emit dataChanged(index, index);
            return true;
            break;
        }


    }
    return false;
}

QVariant ItemModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if(orientation==Qt::Horizontal&&role==Qt::DisplayRole)
        return headerTitle.value(section);
    return QVariant();
}

Qt::ItemFlags ItemModel::flags(const QModelIndex &index) const
{
    if(!index.isValid())
        return 0;

    return Qt::ItemIsEnabled|Qt::ItemIsSelectable|QAbstractItemModel::flags(index)|Qt::ItemIsEditable;
}

QList<QVariant> ItemModel::getHeaderTitle() const
{
    return headerTitle;
}

void ItemModel::setHeaderTitle(const QList<QVariant> &value)
{
    headerTitle = value;
}

void ItemModel::BindingData(QList<ItemObject *> data)
{

    if(rootItem==Q_NULLPTR)
    {
        delete rootItem;
        rootItem=NULL;
    }
    beginResetModel();
    rootItem=new ItemObject();
    QListIterator<ItemObject*> iter(data);
    while(iter.hasNext())
    {
        iter.next()->setParentItem(rootItem);
    }
    rootItem->appendChildRange(data);
    endResetModel();
}

