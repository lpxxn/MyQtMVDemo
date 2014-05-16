#ifndef MYLISTITEMDELEGEGE_H
#define MYLISTITEMDELEGEGE_H

#include <QStyledItemDelegate>

class MyListItemDelegege : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit MyListItemDelegege(QObject *parent = 0);

signals:

public slots:


    // QAbstractItemDelegate interface
public:
    QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYLISTITEMDELEGEGE_H
