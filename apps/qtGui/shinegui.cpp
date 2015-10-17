#include "shinegui.h"
#include "ui_shinegui.h"

ShineGUI::ShineGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShineGUI)
{
    ui->setupUi(this);
    qDebug() << keystore.apiKey();
}

ShineGUI::~ShineGUI()
{
    delete ui;
}
