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

#include "actions.h"

#include "huebridgeconnection.h"

#include <QDebug>

Actions::Actions(QObject *parent) :
    QAbstractListModel(parent)
{
    Q_UNUSED(parent)

    m_connection = HueBridgeConnection::instance();
#if QT_VERSION < 0x050000
    setRoleNames(roleNames());
#endif
}

int Actions::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_list.count();
}

int Actions::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return 3;
}

QVariant Actions::headerData(int section, Qt::Orientation orientation, int role) const
{
    Q_UNUSED(orientation)
    Q_UNUSED(role)
    switch (section){
    case 0: return "Address";
    case 1: return "Method";
    case 2: return "Body";
    }
    return QVariant();
}

QVariant Actions::data(const QModelIndex &index, int role) const
{
    Action *action = m_list.at(index.row());
    switch (role) {
    case RoleAddress:
        return action->address();
    case RoleMethod:
        return action->method();
    case RoleBody:
        return action->body();
    }
    return QVariant();
}

QHash<int, QByteArray> Actions::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles.insert(RoleAddress, "addresss");
    roles.insert(RoleMethod, "method");
    roles.insert(RoleBody, "body");
    return roles;
}

Action *Actions::get(int index) const
{
    if (index > -1 && index < m_list.count()) {
        return m_list.at(index);
    }
    return 0;
}

void Actions::setRuleID(QString ID)
{
    this->m_ruleID = ID;
}

bool Actions::setActions(QVariantList actions)
{
    beginRemoveRows(QModelIndex(), 0, m_list.size()-1);
    m_list.clear();
    endRemoveRows();

    beginInsertRows(QModelIndex(), 0, actions.size()-1);
    foreach(QVariant action, actions){
        QVariantMap actionMap = action.toMap();
        QString address = actionMap.value("address").toString();
        QString methodStr = actionMap.value("method").toString();
        QVariantMap body = actionMap.value("body").toMap();

        Action::Method method;
        if (methodStr == "POST") method = Action::POST;
        else if (methodStr == "PUT") method = Action::PUT;
        else if (methodStr == "DELETE") method = Action::DELETE;
        else method = Action::Unknown;

        Action *newAction = new Action(address, method, body);
        m_list.append(newAction);
    }
    endInsertRows();

    return true;
}

void Actions::addAction(QString address, Action::Method method, QVariantMap body)
{
    Action* action = new Action(address, method, body);

    beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
    m_list.append(action);
    endInsertRows();

    pushUpdates();
}

void Actions::deleteAction(int index)
{
    beginRemoveRows(QModelIndex(), index, index);
    m_list.removeAt(index);
    endRemoveRows();

    pushUpdates();
}

void Actions::updateFinished(int id, const QVariant &response)
{
    Q_UNUSED(id)

    QVariantMap result = response.toList().first().toMap();

    if (!result.contains("success")) {
        qDebug() << "An error occured while updating actions:" << response;
    }
}

void Actions::pushUpdates()
{
    QVariantList actionList;
    foreach (Action* action, m_list){
        actionList.append(action->getVariantMap());
    }
    QString address = "rules/";
    address.append(m_ruleID);

    QVariantMap map;
    map.insert("actions", actionList);
    m_connection->put(address, map, this, "updateFinished");
}
