#ifndef RULEACTIONDELEGATE_H
#define RULEACTIONDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QDebug>

#include "actions.h"
#include "sensors.h"
#include "delegateConfig.h"

class RuleActionDelegate : public QStyledItemDelegate
{
public:
    RuleActionDelegate();

    // QAbstractItemDelegate interface
public:
    virtual QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    virtual void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    Sensors* sensors;

    QString address(const QModelIndex &index) const;
    QString methodStr(const QModelIndex &index) const;
    QString body(const QModelIndex &index) const;
};

#endif // RULEACTIONDELEGATE_H
