#ifndef SENSORDELEGATE_H
#define SENSORDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "sensors.h"
#include "delegateConfig.h"

class SensorDelegate : public QStyledItemDelegate
{
public:
    SensorDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // SENSORDELEGATE_H
