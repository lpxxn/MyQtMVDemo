#include "checkboxdelegate.h"
#include<QApplication>
#include<QMouseEvent>
QRect CheckBoxDelegate::CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) const
{
    QStyleOptionButton check_box_style_option;
    QRect check_box_rect = QApplication::style()->subElementRect(
                QStyle::SE_CheckBoxIndicator,
                &check_box_style_option);
    check_box_rect.setWidth(15);
    check_box_rect.setHeight(15);
    QPoint check_box_point(view_item_style_options.rect.x() + 3,
                           view_item_style_options.rect.y() +
                           view_item_style_options.rect.height() / 2 -
                           check_box_rect.height() / 2);
    return QRect(check_box_point, check_box_rect.size());
}


CheckBoxDelegate::CheckBoxDelegate(QTableView* tableView)
{
    int gridHint = tableView->style()->styleHint(QStyle::SH_Table_GridLineColor, new QStyleOptionViewItemV4());
    QColor gridColor = static_cast<QRgb>(gridHint);
    pen = QPen(gridColor,0,tableView->gridStyle());
    view = tableView;
}

void CheckBoxDelegate::paint(QPainter* painter, const QStyleOptionViewItem& option,const QModelIndex& index)const
{
    painter->save();
    QStyledItemDelegate::paint(painter, option, index);
    painter->restore();


    QStyleOptionButton check_box_style_option;
    bool checked = index.model()->data(index, Qt::UserRole).toBool();

    check_box_style_option.state |= QStyle::State_Enabled;

    check_box_style_option.rect = CheckBoxRect(option);

    if (checked)
        check_box_style_option.state |= QStyle::State_On;
    else
        check_box_style_option.state |= QStyle::State_Off;


    QApplication::style()->drawControl(QStyle::CE_CheckBox, &check_box_style_option, painter);

}

bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {

    if((event->type() == QEvent::MouseButtonRelease) ||
           (event->type() == QEvent::MouseButtonDblClick))
       {
           QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
           if(mouse_event->button() != Qt::LeftButton ||
              !CheckBoxRect(option).contains(mouse_event->pos()))
           {
               return false;
           }

           if(event->type() == QEvent::MouseButtonDblClick)
           {
               return true;
           }
       }
       else if(event->type() == QEvent::KeyPress)
       {
           if(static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
              static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
           {
               return false;
           }
       }
       else
       {
           return false;
       }

       bool checked = index.model()->data(index, Qt::UserRole).toBool();
       emit Checked(index,checked);
       return model->setData(index, !checked, Qt::EditRole|Qt::UserRole);

}
