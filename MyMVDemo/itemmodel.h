#ifndef ITEMMODEL_H
#define ITEMMODEL_H

#include <QAbstractItemModel>
#include "itemobject.h"

class ItemModel : public QAbstractItemModel
{
    Q_OBJECT
public:
    explicit ItemModel(QObject *parent = 0);
    ~ItemModel();

 // QAbstractItemModel interface
    QModelIndex index(int row, int column, const QModelIndex &parent) const;
    QModelIndex parent(const QModelIndex &child) const;
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

    QList<QVariant> getHeaderTitle() const;
    void setHeaderTitle(const QList<QVariant> &value);
    void BindingData(QList<ItemObject*> data);
private:
    ItemObject * rootItem;
    QList<QVariant> headerTitle;
signals:

public slots:





};

#endif // ITEMMODEL_H
