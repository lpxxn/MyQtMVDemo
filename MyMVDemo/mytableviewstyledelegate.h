#ifndef MYTABLEVIEWSTYLEDELEGATE_H
#define MYTABLEVIEWSTYLEDELEGATE_H

#include <QStyledItemDelegate>

class MyTableViewStyleDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    MyTableViewStyleDelegate(QObject *parent = 0);
    ~MyTableViewStyleDelegate();

    // QAbstractItemDelegate interface
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // MYTABLEVIEWSTYLEDELEGATE_H
