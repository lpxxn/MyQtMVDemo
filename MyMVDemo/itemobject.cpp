#include "itemobject.h"
#include<QDebug>
#include<QPixmap>
#include<QString>

ItemObject::ItemObject(ItemObject * parent)
{
    parentItem=parent;
}

ItemObject::ItemObject(QString strName, QString strDesc, QString strIconPath, ItemObject *parent):
    name(strName),desc(strDesc),parentItem(parent)
{
    setMyIcon(strIconPath);
}

ItemObject::~ItemObject()
{
    qDeleteAll(childItems);
    //delete parentItem;
}

void ItemObject::appendChild(ItemObject *child)
{
    childItems.append(child);
}

void ItemObject::appendChildRange(QList<ItemObject *> childRange)
{
    childItems.append(childRange);
}

ItemObject * ItemObject::getChild(int row)
{
    return childItems.value(row);
}

int ItemObject::childCount() const
{
    return childItems.count();
}

int ItemObject::currentItemRow() const
{
    if(parentItem)
    {
        return parentItem->childItems.indexOf(const_cast<ItemObject *>(this));
    }
    return 0;
}
QString ItemObject::getName() const
{
    return name;
}

void ItemObject::setName(const QString &value)
{
    name = value;
}

QString ItemObject::getDesc() const
{
    return desc;
}

void ItemObject::setDesc(const QString &value)
{
    desc = value;
}
QIcon ItemObject::getMyIcon() const
{
    return myIcon;
}

void ItemObject::setMyIcon(const QString strIconPath)
{
    QString imagepath = strIconPath;//"://images/folder.png";
    QPixmap image0(imagepath);
    QPixmap image = image0.scaled(QSize(100,100));
    qDebug() << image.size();
    myIcon =  QIcon(image);

}

void ItemObject::setParentItem(ItemObject *value)
{
    parentItem = value;
}

ItemObject *ItemObject::getParentItem() const
{
    return parentItem;
}






