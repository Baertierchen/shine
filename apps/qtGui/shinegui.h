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

#include "light.h"
#include "lights.h"
#include "lightDelegate.h"
#include "scenes.h"

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
    void lightsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void lightStateChanged();
    void lightPowerToggled(bool on);
    void lightBrightnessChanged(int bri);

private:
    void drawColorMap();
    void updateLightData();

    Ui::ShineGUI *ui;

    KeyStore keystore;
    HueBridgeConnection *bridge;

    Light* activeLight = NULL;
    Lights lights;
    LightDelegate lightDelegate;
    Scenes scenes;
    QModelIndex currentLightModelIndex;

    QPixmap *colorMap;
    QPixmap *colorMapWithLight;
    QPixmap *activeColorMap;
    QGraphicsScene colorMapScene;
};

#endif // SHINEGUI_H
