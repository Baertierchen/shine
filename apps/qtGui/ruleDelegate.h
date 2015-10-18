#ifndef RULEDELEGATE_H
#define RULEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "rules.h"
#include "delegateConfig.h"

class RuleDelegate : public QStyledItemDelegate
{
public:
    RuleDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // RULEDELEGATE_H
