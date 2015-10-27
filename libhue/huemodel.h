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

#ifndef HUEMODEL_H
#define HUEMODEL_H

#include <QAbstractListModel>
#include <QTimer>

class HueModel: public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int count READ count NOTIFY countChanged)
    Q_PROPERTY(bool autoRefresh READ autoRefresh WRITE setAutoRefresh NOTIFY autoRefreshChanged)
    Q_PROPERTY(bool busy READ busy NOTIFY busyChanged)

public:

    explicit HueModel(QObject *parent = 0);

    int count() const { return rowCount(QModelIndex()); }

    bool autoRefresh() const;
    void setAutoRefresh(bool autoRefresh);
    bool busy() const;

public slots:
    virtual void refresh() = 0;

signals:
    void countChanged();
    void autoRefreshChanged();
    void busyChanged();

protected:
    template<class Type>
    void setNewList(QList<Type*> list){
        bool found=false;
        Type* current = NULL;
        for (int i=0; i<m_list.size(); i++){
            found = false;
            current = (Type*)m_list[i];
            foreach (Type* obj, list){
                if (*obj == *current){
                    found = true;
                    break;
                }
            }
            if (!found){
                beginRemoveRows(QModelIndex(), i, i);
                m_list.removeAt(i);
                endRemoveRows();
            }
        }

        for (int i=0; i<list.size(); i++){
            found = false;
            current = list[i];
            foreach (QObject* obj, m_list){
                Type* object = (Type*)obj;
                if (*object == *current){
                    found = true;
                    break;
                }
            }
            if (!found){
                beginInsertRows(QModelIndex(), m_list.size(), m_list.size());
                m_list.append(current);
                endInsertRows();
            }
        }
    }

    bool m_busy;
    QList<QObject*> m_list;

private:
    QTimer m_refreshTimer;
};

#endif
