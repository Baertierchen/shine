#ifndef SHINEGUI_H
#define SHINEGUI_H

#include <QtCore>
#include <QWidget>
#include <QMainWindow>
#include <QGraphicsScene>
#include <QItemSelection>
#include <QMouseEvent>
#include <QUuid>

#include "keystore.h"
#include "huebridgeconnection.h"
#include "configuration.h"

#include "light.h"
#include "lights.h"
#include "lightDelegate.h"

#include "scene.h"
#include "scenes.h"
#include "sceneDelegate.h"
#include "sceneLightsDelegate.h"

#include "user.h"
#include "users.h"
#include "userDelegate.h"

#include "sensor.h"
#include "sensors.h"
#include "sensorDelegate.h"

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

    // scenes
    void scenesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void activateScene();

    // users
    void usersSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void removeUser();
    void pressLinkButton();

    // sensors
    void sensorsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void removeSensor();
    void addSensor();

private:
    void drawColorMap();
    void updateLightData();

    void updateSceneData();

    Ui::ShineGUI *ui;

    KeyStore keystore;
    HueBridgeConnection *bridge;
    Configuration configuration;
    QUuid uuid;

    // Lights
    Lights lights;
    LightDelegate lightDelegate;
    Light* activeLight = NULL;
    QModelIndex currentLightModelIndex;

    QPixmap *colorMap;
    QPixmap *colorMapWithLight;
    QPixmap *activeColorMap;
    QGraphicsScene colorMapScene;

    // Scenes
    Scenes scenes;
    SceneDelegate sceneDelegate;
    SceneLightsDelegate *sceneLightsDelegate;
    Scene* activeScene = NULL;
    QModelIndex currentSceneModelIndex;

    // Users
    Users users;
    UserDelegate userDelegate;
    User* activeUser = NULL;
    QModelIndex currentUserModelIndex;

    // Sensors
    Sensors* sensors;
    SensorDelegate sensorDelegate;
    Sensor* activeSensor;
    QModelIndex currentSensorModelIndex;
};

#endif // SHINEGUI_H
