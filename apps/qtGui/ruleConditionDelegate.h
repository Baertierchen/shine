#ifndef RULECONDITIONDELEGATE_H
#define RULECONDITIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "conditions.h"
#include "sensor.h"
#include "sensors.h"
#include "delegateConfig.h"

class RuleConditionDelegate : public QStyledItemDelegate
{
public:
    RuleConditionDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    QString buildString(const QModelIndex &index) const;
    QString sensorName(const QModelIndex &index) const;
    QString resource(const QModelIndex &index) const;
    QString operatorStr(const QModelIndex &index) const;
    QString value(const QModelIndex &index) const;
};

#endif // RULECONDITIONDELEGATE_H
