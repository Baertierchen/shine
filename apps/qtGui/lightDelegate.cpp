#include "lightDelegate.h"

LightDelegate::LightDelegate()
{

}

QSize LightDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    QIcon icon = qvariant_cast<QIcon>(index.data(Lights::RoleIcon));
    QString name = qvariant_cast<QString>(index.data(Lights::RoleName));
    QSize iconsize = icon.actualSize(option.decorationSize);
    QFont font;
    QFontMetrics fm(font);

    return(QSize(iconsize.width() + fm.width(name) + 3*SPACING,iconsize.height() + 2*MARGIN));
}

void LightDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    bool on = qvariant_cast<bool>(index.data(Lights::RoleOn));
    Lights::Roles iconRole = Lights::RoleIcon;
    if (on) iconRole = Lights::RoleIconOutline;
    QIcon icon = qvariant_cast<QIcon>(index.data(iconRole));
    QString name = qvariant_cast<QString>(index.data(Lights::RoleName));
    bool reachable = qvariant_cast<bool>(index.data(Lights::RoleReachable));

    QFont font;
    if (!reachable){
        font.setItalic(true);
        painter->setPen(QPen(QColor("red")));
    }
    QFontMetrics fm(font);

    QSize iconsize = icon.actualSize(option.decorationSize);

    QRect nameRect, iconRect;

    iconRect.setLeft(option.rect.left() + SPACING);
    iconRect.setRight(iconRect.left() + iconsize.width());
    iconRect.setTop(option.rect.top() + MARGIN);
    iconRect.setBottom(option.rect.bottom() - MARGIN);

    nameRect.setLeft(iconRect.right() + SPACING);
    nameRect.setTop(option.rect.top() + option.rect.height()/2 - fm.height()/2);
    nameRect.setBottom(option.rect.bottom() - option.rect.height()/2 + fm.height()/2);
    nameRect.setRight(option.rect.right());

    if (option.state & QStyle::State_Selected){
        painter->fillRect(option.rect, option.palette.highlight());
    }

    painter->drawPixmap(iconRect, icon.pixmap(iconsize.width(),iconsize.height()));

    painter->setFont(font);
    painter->drawText(nameRect,name);

    painter->restore();
}
