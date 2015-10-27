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

#ifndef ACTION_H
#define ACTION_H

#include <QObject>
#include <QAbstractListModel>

class Action: public QObject
{
    Q_OBJECT

public:
    enum Method{
        POST, PUT, DELETE, Unknown
    };

    Action(QString address, Method method, QVariantMap body, QObject *parent = 0);

    QVariantMap getVariantMap();

    QString address() const;
    Method method() const;
    QVariantMap body() const;

    bool operator==(const Action& other);

signals:

private:
    QString m_address;
    Method m_method;
    QVariantMap m_body;
};

#endif
