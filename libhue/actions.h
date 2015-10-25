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

#ifndef ACTIONS_H
#define ACTIONS_H

#include <QAbstractListModel>

#include "huemodel.h"
#include "action.h"

class Actions : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        RoleAddress = Qt::UserRole,
        RoleMethod,
        RoleBody
    };

    explicit Actions(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    virtual int columnCount(const QModelIndex &parent) const;
    virtual QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE Action* get(int index) const;

    bool setActions(QVariantList actions);

private:
    QList<Action*> m_list;
};

#endif // ACTIONS_H
