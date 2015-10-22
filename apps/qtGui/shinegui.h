#ifndef SHINEGUI_H
#define SHINEGUI_H

#include <QMainWindow>

#include "keystore.h"
#include "huebridgeconnection.h"

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

private:
    Ui::ShineGUI *ui;

    KeyStore keystore;
    HueBridgeConnection *bridge;

    Lights lights;
    LightDelegate lightDelegate;
    Scenes scenes;
};

#endif // SHINEGUI_H
