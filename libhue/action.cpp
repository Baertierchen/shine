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

#include "action.h"

Action::Action(QString address, Action::Method method, QString body, QObject *parent) :
    m_address(address),
    m_method(method),
    m_body(body),
    QObject(parent)
{

}

QString Action::address()
{
    return m_address;
}

Action::Method Action::method()
{
    return m_method;
}

QString Action::body()
{
    return m_body;
}
