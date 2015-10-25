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

#include "conditions.h"

#include "huebridgeconnection.h"

#include <QDebug>

Conditions::Conditions(QObject *parent) :
    QAbstractListModel(parent)
{
    Q_UNUSED(parent)

    m_sensors = Sensors::instance();
    m_connection = HueBridgeConnection::instance();
#if QT_VERSION < 0x050000
    setRoleNames(roleNames());
#endif
}

int Conditions::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

int Conditions::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 4;
}

QVariant Conditions::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    switch (section){
    case 0: return "Sensor";
    case 1: return "Resource";
    case 2: return "Op";
    case 3: return "Value";
    }
    return QVariant();
}

QVariant Conditions::data(const QModelIndex &index, int role) const
{
    Condition *condition = m_list.at(index.row());
    switch (role) {
    case RoleSensor:
        return condition->sensorID();
    case RoleResource:
        return condition->resource();
    case RoleOperator:
        return condition->op();
    case RoleValue:
        return condition->value();
    }
    return QVariant();
}

QHash<int, QByteArray> Conditions::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(RoleSensor, "sensor");
    roles.insert(RoleResource, "resource");
    roles.insert(RoleOperator, "operator");
    roles.insert(RoleValue, "value");
    return roles;
}

Condition *Conditions::get(int index) const
{
    if (index > -1 && index < m_list.count()) {
        return m_list.at(index);
    }
    return 0;
}

void Conditions::setRuleID(QString ID)
{
    this->m_ruleID = ID;
}

bool Conditions::setConditions(QVariantList conditions)
{
    if (m_sensors == NULL) return false;

    beginRemoveRows(QModelIndex(), 0, m_list.size()-1);
    m_list.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, conditions.size()-1);
    foreach(QVariant condition, conditions){
        QVariantMap conditionMap = condition.toMap();
        QString address = conditionMap.value("address").toString();
        QString sensorID = address;
        sensorID.replace(QRegExp("^/sensors/(\\d+)/.*$"),"\\1");

        QString resource = address;
        resource.replace(QRegExp("^/sensors/\\d+(/.*)$"),"\\1");

        QString opStr = conditionMap.value("operator").toString();
        Condition::Operator op;
        if (opStr == "eq") op = Condition::eq;
        else if (opStr == "gt") op = Condition::gt;
        else if (opStr == "lt") op = Condition::lt;
        else if (opStr == "dx") op = Condition::dx;
        else op = Condition::unknown;

        Condition *cond = new Condition(sensorID, resource, op, conditionMap.value("value").toString());
        m_list.append(cond);
    }
    endInsertRows();

    return true;
}

void Conditions::addCondition(QString sensorID, QString resource, const Condition::Operator op, QString value)
{
    Condition* cond = new Condition(sensorID, resource, op, value);

    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(cond);
    endInsertRows();

    pushUpdates();
}

void Conditions::deleteCondition(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_list.removeAt(index);
    endRemoveRows();

    pushUpdates();
}

void Conditions::updateFinished(int id, const QVariant &response)
{
    Q_UNUSED(id)

    QVariantMap result = response.toList().first().toMap();

    if (!result.contains("success")) {
        qDebug() << "An error occured while updating conditions:" << response;
    }
}

void Conditions::pushUpdates()
{
    QVariantList conditionList;
    foreach (Condition* condition, m_list){
        conditionList.append(condition->getVariantMap());
    }
    QString address = "rules/";
    address.append(m_ruleID);

    QVariantMap map;
    map.insert("conditions", conditionList);
    m_connection->put(address, map, this, "updateFinished");
}
