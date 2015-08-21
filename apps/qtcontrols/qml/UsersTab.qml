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

import QtQuick 2.1
import QtQuick.Controls 1.1
import QtQuick.Layouts 1.1
import Hue 0.1

Tab {
    id: root
    property var users

    SplitView {
        anchors.fill: parent

        ColumnLayout {
            TableView {
                id: usersView
                Layout.fillHeight: true
                Layout.fillWidth: true

                model: root.users

                TableViewColumn {
                    role: "name"
                    title: "User name"
                }
                TableViewColumn {
                    role: "created"
                    title: "Created"
                }
                TableViewColumn {
                    role: "lastUsed"
                    title: "last use"
                }
                TableViewColumn {
                    role: "id"
                    title: "ID"
                }
            }

            Button {
                id: deleteButton
                Layout.fillWidth: true
                text: "Delete User"
                onClicked: {
                    usersView.selection.forEach( function(rowIndex) {root.users.deleteUser(rowIndex) } )
                }
            }
        }
    }
}
