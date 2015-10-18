#include "ruleDelegate.h"

RuleDelegate::RuleDelegate()
{

}

QSize RuleDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void) option;
    QString name = index.data(Rules::RoleName).toString();
    QFont font;
    QFontMetrics fm(font);

    return(QSize(fm.width(name) + 2*SPACING,fm.height() + 2*MARGIN));
}

void RuleDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QString name = index.data(Rules::RoleName).toString();
    QFont font;
    QFontMetrics fm(font);
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

    painter->restore();
}
