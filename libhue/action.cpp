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

#include <QDebug>

#include "action.h"

Action::Action(QString address, Action::Method method, QVariantMap body, QObject *parent) :
    QObject(parent),
    m_address(address),
    m_method(method),
    m_body(body)
{
}

QVariantMap Action::getVariantMap()
{
    QVariantMap map;
    map.insert("address", m_address);

    QString method;
    switch (m_method){
    case POST: method = "POST"; break;
    case PUT: method = "PUT"; break;
    case DELETE: method = "DELETE"; break;
    case Unknown: return map;
    }
    map.insert("method", method);
    map.insert("body", m_body);

    return map;
}

QString Action::address() const
{
    return m_address;
}

Action::Method Action::method() const
{
    return m_method;
}

QVariantMap Action::body() const
{
    return m_body;
}

bool Action::operator==(const Action &other)
{
    if (m_address != other.address()) return false;
    if (m_method != other.method()) return false;
    return (m_body == other.body());
}
