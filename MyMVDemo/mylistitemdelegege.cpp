#include "mylistitemdelegege.h"

MyListItemDelegege::MyListItemDelegege(QObject *parent) :
    QStyledItemDelegate(parent)
{
}

QSize MyListItemDelegege::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    return QSize(90, 100);
}
