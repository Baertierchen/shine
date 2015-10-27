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

#include "condition.h"

Condition::Condition(QString sensorID, QString resource, const Operator op, QString value, QObject *parent) :
    m_sensorID(sensorID),
    m_resource(resource),
    m_op(op),
    m_value(value)
{
    Q_UNUSED(parent);
}

QVariantMap Condition::getVariantMap()
{
    QVariantMap map;
    QString address = "/sensors/";
    address.append(m_sensorID);
    address.append(m_resource);

    map.insert("address", address);

    QString op;
    switch (m_op){
    case eq: op = "eq"; break;
    case gt: op = "gt"; break;
    case lt: op = "lt"; break;
    case dx: op = "dx"; break;
    case unknown: return map;
    }
    map.insert("operator", op);

    if (m_op != dx){
        map.insert("value", m_value);
    }

    return map;
}

QString Condition::sensorID() const
{
    return m_sensorID;
}

QString Condition::resource() const
{
    return m_resource;
}

Condition::Operator Condition::op() const
{
    return m_op;
}

QString Condition::value() const
{
    return m_value;
}

bool Condition::operator==(const Condition &other)
{
    if (m_sensorID != other.sensorID()) return false;
    if (m_resource != other.resource()) return false;
    if (m_op != other.op()) return false;
    return (m_value == other.value());
}
