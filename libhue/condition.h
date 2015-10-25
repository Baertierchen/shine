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

#ifndef CONDITION_H
#define CONDITION_H

#include <QObject>
#include <QAbstractListModel>

#include "sensor.h"

class Condition: public QObject
{
    Q_OBJECT

public:
    enum Operator{
        eq, gt, lt, dx, unknown
    };

    Condition(Sensor* sensor, QString resource, const Operator op, QString value, QObject *parent = 0);

    Sensor* sensor();
    QString resource();
    Operator op();
    QString value();

signals:

private:
    Sensor* m_sensor;
    QString m_resource;
    Operator m_op;
    QString m_value;
};

#endif
