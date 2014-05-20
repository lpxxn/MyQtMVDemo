#include "mylineitemdelegate.h"
#include<QLineEdit>
#include<QDebug>
MyLineItemDelegate::MyLineItemDelegate(QObject *parent) :
    QItemDelegate (parent)
{
}

MyLineItemDelegate::~MyLineItemDelegate()
{

}

QWidget *MyLineItemDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QLineEdit *editor = new QLineEdit(parent);
    //    QRegExp regExp("[0-9]{0,10}");
    //    editor->setValidator(new QRegExpValidator(regExp, parent));

    return editor;
}

void MyLineItemDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    if(lineEdit->text().length()>0)
    {
        qDebug()<<lineEdit->text();
        lineEdit->setText(text);
    }
}

void MyLineItemDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QLineEdit *lineEdit = static_cast<QLineEdit*>(editor);
    if(lineEdit->text().length()>0)
    {
        QString text = lineEdit->text();
        model->setData(index, text, Qt::EditRole);
    }
}

void MyLineItemDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}

QSize MyLineItemDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QSize size=QSize(30,option.rect.height());
    return size;
}


