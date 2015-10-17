#ifndef SHINEGUI_H
#define SHINEGUI_H

#include <QMainWindow>

#include "keystore.h"

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
};

#endif // SHINEGUI_H
