#include "sensorDelegate.h"

SensorDelegate::SensorDelegate()
{

}

QSize SensorDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void) option;
    QString name;
    switch (index.column()){
    case 0:
        name = index.data(Sensors::RoleName).toString();
        break;
    case 1:
        name = index.data(Sensors::RoleStatus).toString();
        break;
    }
    QFont font;
    QFontMetrics fm(font);

    return(QSize(fm.width(name) + 2*SPACING, fm.height() + 2*MARGIN));
}

void SensorDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();
    QFont font;
    QFontMetrics fm(font);

    switch (index.column()){
    case 0:
    {
        QString name = index.data(Sensors::RoleName).toString();
        QRect nameRect;

        nameRect.setLeft(option.rect.left() + SPACING);
        nameRect.setTop(option.rect.top() + option.rect.height()/2 - fm.height()/2);
        nameRect.setBottom(option.rect.bottom() - option.rect.height()/2 + fm.height()/2);
        nameRect.setRight(option.rect.right());

        if (option.state & QStyle::State_Selected){
            painter->fillRect(option.rect, option.palette.highlight());
        }

        painter->setFont(font);
        painter->drawText(nameRect,name);
        break;
    }
    case 1:
    {
        QVariant status = index.data(Sensors::RoleStatus);
        QRect stateRect;

        stateRect.setLeft(option.rect.left() + SPACING);
        stateRect.setTop(option.rect.top() + option.rect.height()/2 - fm.height()/2);
        stateRect.setBottom(option.rect.bottom() - option.rect.height()/2 + fm.height()/2);
        stateRect.setRight(option.rect.right());

        if (option.state & QStyle::State_Selected){
            painter->fillRect(option.rect, option.palette.highlight());
        }

        painter->setFont(font);
        painter->drawText(stateRect, status.toString());
        break;
    }
    }

    painter->restore();
}
