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

#ifndef USERS_H
#define USERS_H

#include <QAbstractListModel>
#include <QTimer>

class User;

class Users : public QAbstractListModel
{
    Q_OBJECT
public:
    enum Roles {
        RoleId,
        RoleName,
        RoleLastUsed,
        RoleCreated
    };

    explicit Users(QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QHash<int, QByteArray> roleNames() const;
    Q_INVOKABLE User* get(int index) const;

public slots:
    void usersReceived(int id, const QVariant &variant);
    void deleteUserFinished(int id, const QVariant &variant);
    void refresh();
    Q_INVOKABLE void deleteUser(int index);

private:
    QList<User*> m_list;
};

#endif // USERS_H
