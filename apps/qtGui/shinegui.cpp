#include "shinegui.h"
#include "ui_shinegui.h"

ShineGUI::ShineGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShineGUI)
{
    ui->setupUi(this);
    bridge = HueBridgeConnection::instance();
    bridge->setApiKey(keystore.apiKey());

    lights.setIconBasePath("../../icons");
    lights.setAutoRefresh(true);
    scenes.setAutoRefresh(true);

    ui->lv_lights->setModel(&lights);
    ui->lv_lights->setItemDelegate(&lightDelegate);
}

ShineGUI::~ShineGUI()
{
    delete ui;
}
