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

Condition::Condition(Sensor* sensor, QString resource, const Operator op, QString value, QObject *parent) :
    m_sensor(sensor),
    m_resource(resource),
    m_op(op),
    m_value(value)
{
    Q_UNUSED(parent);
}

Sensor *Condition::sensor()
{
    return m_sensor;
}

QString Condition::resource()
{
    return m_resource;
}

Condition::Operator Condition::op()
{
    return m_op;
}

QString Condition::value()
{
    return m_value;
}
