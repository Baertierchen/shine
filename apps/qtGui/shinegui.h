#ifndef SHINEGUI_H
#define SHINEGUI_H

#include <QtCore>
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QItemSelection>
#include <QMouseEvent>

#include "keystore.h"
#include "huebridgeconnection.h"
#include "configuration.h"

#include "light.h"
#include "lights.h"
#include "lightDelegate.h"
#include "scenes.h"

#include "user.h"
#include "users.h"
#include "userDelegate.h"

namespace Ui {
class ShineGUI;
}

class ShineGUI : public QMainWindow
{
    Q_OBJECT

public:
    explicit ShineGUI(QWidget *parent = 0);
    ~ShineGUI();

    // QWidget interface
protected:
    virtual void resizeEvent(QResizeEvent *);

private slots:
    // lights
    void lightsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void lightStateChanged();
    void lightPowerToggled(bool on);
    void lightBrightnessChanged(int bri);

    // users
    void usersSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void removeUser();
    void pressLinkButton();

private:
    void drawColorMap();
    void updateLightData();

    Ui::ShineGUI *ui;

    KeyStore keystore;
    HueBridgeConnection *bridge;
    Configuration configuration;

    // Lights
    Light* activeLight = NULL;
    Lights lights;
    LightDelegate lightDelegate;
    Scenes scenes;
    QModelIndex currentLightModelIndex;

    QPixmap *colorMap;
    QPixmap *colorMapWithLight;
    QPixmap *activeColorMap;
    QGraphicsScene colorMapScene;

    // Users
    User* activeUser = NULL;
    Users users;
    UserDelegate userDelegate;
    QModelIndex currentUserModelIndex;
};

#endif // SHINEGUI_H
