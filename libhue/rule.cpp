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

#include "rule.h"
#include "huebridgeconnection.h"

#include <QColor>
#include <QDebug>

Rule::Rule(const QString &id, const QString &name, QObject *parent)
    : QObject(parent)
    , m_id(id)
    , m_name(name)
{
//    refresh();
}

QString Rule::id() const
{
    return m_id;
}

QString Rule::name() const
{
    return m_name;
}

void Rule::setName(const QString &name)
{
    if (m_name != name) {
        m_name = name;
        emit nameChanged();
    }
}

Conditions* Rule::conditions()
{
    return &m_conditions;
}

void Rule::setConditions(const QVariantList &conditions)
{
    m_conditions.setConditions(conditions);
    emit conditionsChanged();
}

Actions* Rule::actions()
{
    return &m_actions;
}

void Rule::setActions(const QVariantList &actions)
{
    m_actions.setActions(actions);
    emit actionsChanged();
}

void Rule::refresh()
{
}
