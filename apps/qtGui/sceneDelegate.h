#ifndef SCENEDELEGATE_H
#define SCENEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "scenes.h"
#include "delegateConfig.h"

class SceneDelegate : public QStyledItemDelegate
{
public:
    SceneDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SCENEDELEGATE_H
