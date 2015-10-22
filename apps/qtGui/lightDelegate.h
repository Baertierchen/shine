#ifndef LIGHTDELEGATE_H
#define LIGHTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "lights.h"

#define SPACING 5 // horizontal gaps
#define MARGIN 3 // vertical gaps

class LightDelegate : public QStyledItemDelegate
{
public:
    LightDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // LIGHTDELEGATE_H
