#ifndef USERDELEGATE_H
#define USERDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "users.h"
#include "delegateConfig.h"

class UserDelegate : public QStyledItemDelegate
{
public:
    UserDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // USERDELEGATE_H
