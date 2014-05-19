#ifndef CHECKBOXDELEGATE_H
#define CHECKBOXDELEGATE_H

#include <QStyledItemDelegate>
#include<QTableView>
#include<QPen>
#include<QPainter>
#include<QEvent>
#include<QRect>
class CheckBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    CheckBoxDelegate(QTableView* tableView);
protected:
    void paint(QPainter* painter,const QStyleOptionViewItem& option,const QModelIndex& index) const;
    bool editorEvent(QEvent *event,
                                         QAbstractItemModel *model,
                                         const QStyleOptionViewItem &option,
                                         const QModelIndex &index) ;
private:
    QPen         pen;
    QTableView*  view;
    QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) const;
signals:
    void Checked(const QModelIndex& index,bool isChecked);
};

#endif // CHECKBOXDELEGATE_H
