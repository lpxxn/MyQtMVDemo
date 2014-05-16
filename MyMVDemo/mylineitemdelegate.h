#ifndef MYLINEITEMDELEGATE_H
#define MYLINEITEMDELEGATE_H

#include <QItemDelegate>
#include<QString>
class MyLineItemDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit MyLineItemDelegate(QObject *parent = 0);
    ~MyLineItemDelegate();
    // QAbstractItemDelegate interface
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const;
signals:

public slots:

private:
    QString strText;

};


class ReadOnlyDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    ReadOnlyDelegate(QObject *parent = 0): QItemDelegate(parent) { }
    QWidget *createEditor(QWidget*parent, const QStyleOptionViewItem &option,
        const QModelIndex &index) const
    {
        return NULL;
    }
};
#endif // MYLINEITEMDELEGATE_H
