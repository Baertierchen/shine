/*
 * Copyright 2015 Steffen Köhler
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
 *      Steffen Köhler <mail@steffenkoehler.net>
 */

#ifndef CONDITIONS_H
#define CONDITIONS_H

#include <QAbstractListModel>
#include <QRegExp>

#include "huebridgeconnection.h"
#include "huemodel.h"
#include "condition.h"
#include "sensors.h"

class Conditions : public HueModel
{
    Q_OBJECT
public:
    enum Roles {
        RoleSensor = Qt::UserRole,
        RoleResource,
        RoleOperator,
        RoleValue
    };

    explicit Conditions(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE Condition* get(int index) const;

    void setRuleID(QString ID);
    bool setConditions(QVariantList conditions);

    void addCondition(QString sensorID, QString resource, const Condition::Operator op, QString value);
    void deleteCondition(int index);

private slots:
    void updateFinished(int id, const QVariant &response);

    // HueModel interface
public slots:
    virtual void refresh();

private:
    void pushUpdates();

    HueBridgeConnection *m_connection;
    QString m_ruleID;
    Sensors* m_sensors;
};

#endif // CONDITIONS_H
