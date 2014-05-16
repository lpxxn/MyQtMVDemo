#ifndef ITEMOBJECT_H
#define ITEMOBJECT_H
#include<QList>
#include<QString>
#include<QIcon>
class ItemObject
{
public:
    ItemObject(ItemObject * parent =0);
    ItemObject(QString strName,QString strDesc,QString strIconPath,ItemObject * parent =0);
    ~ItemObject();
    void appendChild(ItemObject *child);
    void appendChildRange(QList<ItemObject *> childRange);
    ItemObject * getChild(int row);
    int childCount() const;
    int currentItemRow() const;

    QString getName() const;
    void setName(const QString &value);

    QString getDesc() const;
    void setDesc(const QString &value);

    QIcon getMyIcon() const;
    void setMyIcon(const QString strIconPath);

    ItemObject *getParentItem() const;
    void setParentItem(ItemObject *value);

private:
    ItemObject *parentItem;
    QList<ItemObject*> childItems;
    QString name;
    QString desc;
    QIcon myIcon;
};

#endif // ITEMOBJECT_H
