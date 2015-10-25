/*
 * Copyright 2015 Michael Zanetti
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 2.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors:
 *      Michael Zanetti <michael_zanetti@gmx.net>
 */

#ifndef RULE_H
#define RULE_H

#include <QObject>
#include <QAbstractListModel>

#include "huebridgeconnection.h"
#include "conditions.h"
#include "actions.h"

class Rule: public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString id READ id CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    //Q_PROPERTY(QVariantList conditions READ conditions NOTIFY conditionsChanged)
    //Q_PROPERTY(QVariantList actions READ actions NOTIFY actionsChanged)

public:
    Rule(const QString &id, const QString &name, QObject *parent = 0);

    QString id() const;

    QString name() const;
    void setName(const QString &name);

    Conditions* conditions();
    void setConditions(const QVariantList &conditions);

    Actions *actions();
    void setActions(const QVariantList &actions);

public slots:
    void refresh();
    void updateFinished(int id, const QVariant &response);

signals:
    void nameChanged();
    void conditionsChanged();
    void actionsChanged();

private:
    HueBridgeConnection* m_connection;
    QString m_id;
    QString m_name;
    Conditions m_conditions;
    Actions m_actions;
};

#endif
