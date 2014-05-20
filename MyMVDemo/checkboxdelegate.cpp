#include "checkboxdelegate.h"
#include<QApplication>
#include<QMouseEvent>
#include<QIcon>
QRect CheckBoxDelegate::CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) const
{
    QStyleOptionButton check_box_style_option;
    QRect check_box_rect = QApplication::style()->subElementRect(
                QStyle::SE_CheckBoxIndicator,
                &check_box_style_option);
    //    check_box_rect.setWidth(15);
    //    check_box_rect.setHeight(15);
    QPoint check_box_point(view_item_style_options.rect.x() + 3,
                           view_item_style_options.rect.y() +
                           view_item_style_options.rect.height() / 2 -
                           check_box_rect.height() / 2);
    return QRect(check_box_point, check_box_rect.size());
}

bool CheckBoxDelegate::IsMouseHover(bool isHover)
{
    return isHover;
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
    //Ä¬ÈÏItemobjectµÄÄÚÈÝ
    QStyledItemDelegate::paint(painter, option, index);
    painter->save();
    //icon


    //checkbox
    QStyleOptionButton check_box_style_option;
    bool checked = index.model()->data(index, Qt::UserRole).toBool();
    check_box_style_option.state |= QStyle::State_Enabled;
    check_box_style_option.rect = CheckBoxRect(option);
    if (checked)
        check_box_style_option.state |= QStyle::State_On;
    else
        check_box_style_option.state |= QStyle::State_Off;

    //str
    QString & myItemStr = index.data(Qt::DisplayRole).toString();
    QFontMetrics fm(painter->font());
    QRect strRect = QRect(option.rect.topLeft()+QPoint(20,0),QSize(fm.width(myItemStr),fm.height()));

    //btn
    QStyleOptionButton opt;
    opt.state |= QStyle::State_Enabled|QStyle::State_MouseOver;

    //opt.rect = option.rect.adjusted(30,0,80,100);
    opt.rect=QRect(strRect.topRight()+QPoint(20, -5),QSize(50,20));
    opt.text = trUtf8("Button text");

    //QApplication::style()->drawControl(QStyle::CE_PushButton, &opt, painter,view);
    view->style()->drawControl(QStyle::CE_PushButton, &opt, painter,view);
    QApplication::style()->drawControl(QStyle::CE_CheckBox, &check_box_style_option, painter);
    //painter->drawText(strRect, myItemStr);
    painter->restore();
}

bool CheckBoxDelegate::editorEvent(QEvent *event,
                                   QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,
                                   const QModelIndex &index) {
    if(!(event->type() == QEvent::MouseButtonRelease))
        return false;

    QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
    if(mouse_event->button() != Qt::LeftButton)
        //||!CheckBoxRect(option).contains(mouse_event->pos()))
    {
        return false;
    }
    if(CheckBoxRect(option).contains(mouse_event->pos()))
    {
        bool checked = index.model()->data(index, Qt::UserRole).toBool();
        emit Checked(index,checked);
        return model->setData(index, !checked, Qt::EditRole|Qt::UserRole);
    }

    if(event->type() == QEvent::MouseButtonDblClick)
    {
        return true;
    }
}
