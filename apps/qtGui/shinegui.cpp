#include "shinegui.h"
#include "ui_shinegui.h"

ShineGUI::ShineGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ShineGUI)
{
    ui->setupUi(this);
    bridge = HueBridgeConnection::instance();
    bridge->setApiKey(keystore.apiKey());

    // lights
    lights.setIconBasePath("../../icons");
    lights.setAutoRefresh(true);

    ui->lv_lights->setModel(&lights);
    ui->lv_lights->setItemDelegate(&lightDelegate);

    ui->gv_colorMapView->setScene(&colorMapScene);
    colorMap = new QPixmap(360, 255);
    colorMapWithLight = new QPixmap(360, 255);
    activeColorMap = colorMap;

    drawColorMap();

    connect(ui->lv_lights->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ShineGUI::lightsSelectionChanged);
    connect(ui->chk_power, &QCheckBox::toggled, this, &ShineGUI::lightPowerToggled);
    connect(ui->sl_brightness, &QSlider::valueChanged, this, &ShineGUI::lightBrightnessChanged);

    // scenes
    scenes.setAutoRefresh(true);
    ui->lv_scenes->setModel(&scenes);
    ui->lv_scenes->setItemDelegate(&sceneDelegate);

    sceneLightsDelegate = new SceneLightsDelegate(&lights);
    ui->lv_sceneBulbs->setItemDelegate(sceneLightsDelegate);

    connect(ui->lv_scenes->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ShineGUI::scenesSelectionChanged);
    connect(ui->btn_activateScene, &QPushButton::clicked, this, &ShineGUI::activateScene);

    // users
    users.setAutoRefresh(true);
    ui->lv_users->setModel(&users);
    ui->lv_users->setItemDelegate(&userDelegate);

    connect(ui->lv_users->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ShineGUI::usersSelectionChanged);
    connect(ui->btn_removeUser, &QPushButton::clicked, this, &ShineGUI::removeUser);
    connect(ui->btn_linkButton, &QPushButton::clicked, this, &ShineGUI::pressLinkButton);

    // sensors
    sensors = Sensors::instance();
    sensors->setAutoRefresh(true);
    ui->lv_sensors->setModel(sensors);
    ui->lv_sensors->setItemDelegate(&sensorDelegate);

    connect(ui->lv_sensors->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ShineGUI::sensorsSelectionChanged);
    connect(ui->btn_removeSensor, &QPushButton::clicked, this, &ShineGUI::removeSensor);
    connect(ui->btn_addSensor, &QPushButton::clicked, this, &ShineGUI::addSensor);

    ui->lv_sensors->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->lv_sensors->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    // rules
    rules.setAutoRefresh(true);
    ui->lv_rules->setModel(&rules);
    ui->lv_rules->setItemDelegate(&ruleDelegate);

    connect(ui->lv_rules->selectionModel(), &QItemSelectionModel::selectionChanged, this, &ShineGUI::rulesSelectionChanged);
    connect(ui->btn_removeRule, &QPushButton::clicked, this, &ShineGUI::removeRule);
}

ShineGUI::~ShineGUI()
{
    delete ui;
}

void ShineGUI::drawColorMap()
{
    QPainter painter;
    painter.begin(colorMap);
    for (int hue = 0; hue<359; hue++){
        for (int sat = 0; sat<255; sat++){
            QPen pen(QColor::fromHsv(hue, sat, 255));
            painter.setPen(pen);
            painter.drawPoint(hue, sat);
        }
    }
    painter.end();

    colorMapScene.clear();
    colorMapScene.setSceneRect(0,0,ui->gv_colorMapView->width(), ui->gv_colorMapView->height());
    colorMapScene.addPixmap(colorMap->scaled(ui->gv_colorMapView->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); // SmoothTransformation
}

void ShineGUI::updateLightData()
{
    bool editingPossible = false;
    if (activeLight != NULL){
        bool isReachable = activeLight->reachable();
        bool on = activeLight->on();
        ui->chk_power->setChecked(on);

        int bri = activeLight->bri();
        ui->sl_brightness->setValue(bri);

        if (isReachable){
            editingPossible = true;
            activeColorMap = colorMapWithLight;

            int hue = activeLight->hue() * 360 / 65536;
            int sat = activeLight->sat();
            *colorMapWithLight = *colorMap;

            QPainter painter;
            painter.begin(colorMapWithLight);
            QBrush brush(Qt::black);
            painter.setBrush(brush);
            QPoint point(hue, sat);
            painter.drawEllipse(point, 2, 2);
            painter.end();

            colorMapScene.clear();
            colorMapScene.setSceneRect(0,0,ui->gv_colorMapView->width(), ui->gv_colorMapView->height());
            colorMapScene.addPixmap(colorMapWithLight->scaled(ui->gv_colorMapView->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); // SmoothTransformation
        }else{
            activeColorMap = colorMap;
            activeLight = NULL;
            resizeEvent(NULL);
        }
    }

    ui->chk_power->setEnabled(editingPossible);
    ui->sl_brightness->setEnabled(editingPossible);
    ui->gv_colorMapView->setEnabled(editingPossible);
}

void ShineGUI::updateSceneData()
{

}

void ShineGUI::resizeEvent(QResizeEvent *)
{
    colorMapScene.clear();
    colorMapScene.setSceneRect(0,0,ui->gv_colorMapView->width(), ui->gv_colorMapView->height());
    colorMapScene.addPixmap(activeColorMap->scaled(ui->gv_colorMapView->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation)); // SmoothTransformation
}

void ShineGUI::lightsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    (void) deselected;
    if (selected.size() == 1){
        currentLightModelIndex = selected.first().topLeft();
        activeLight = lights.get(currentLightModelIndex.row());
        connect(activeLight, &Light::stateChanged, this, &ShineGUI::lightStateChanged);

        updateLightData();
    }else{
        activeLight = NULL;
    }
}

void ShineGUI::lightStateChanged()
{
    updateLightData();
}

void ShineGUI::lightPowerToggled(bool on)
{
    if (activeLight == NULL) return;
    activeLight->setOn(on);
}

void ShineGUI::lightBrightnessChanged(int bri)
{
    if (activeLight == NULL) return;
    activeLight->setBri(bri);
}

void ShineGUI::scenesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    (void) deselected;
    if (selected.size() == 1){
        currentSceneModelIndex = selected.first().topLeft();
        activeScene = scenes.get(currentSceneModelIndex.row());
        ui->lv_sceneBulbs->setModel(activeScene);
    }else{
        activeScene = NULL;
    }
}

void ShineGUI::activateScene()
{
    if (activeScene != NULL){
        scenes.recallScene(activeScene->id());
    }
}

void ShineGUI::usersSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    (void) deselected;
    if (selected.size() == 1){
        currentUserModelIndex = selected.first().topLeft();
        activeUser = users.get(currentUserModelIndex.row());
    }else{
        activeUser = NULL;
    }
}

void ShineGUI::removeUser()
{
    if (activeUser != NULL){
        users.deleteUser(currentUserModelIndex.row());
    }
}

void ShineGUI::pressLinkButton()
{
    configuration.pressLinkButton();
}

void ShineGUI::sensorsSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    (void) deselected;
    if (selected.size() == 1){
        currentSensorModelIndex = selected.first().topLeft();
        activeSensor = sensors->get(currentSensorModelIndex.row());
    }else{
        activeSensor = NULL;
    }
}

void ShineGUI::removeSensor()
{
    if (activeSensor != NULL){
        sensors->deleteSensor(activeSensor->id());
    }
}

void ShineGUI::addSensor()
{
    QString name = ui->txt_sensorName->text();
    if (name == ""){
        qDebug() << "Name must not be empty";
        return;
    }

    if (name.contains(' ')){
        qDebug() << "Name must not contain spaces";
        return;
    }

    QString id = QString::number(qrand());
    sensors->createSensor(name, id);
}

void ShineGUI::rulesSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected)
{
    (void) deselected;
    if (selected.size() == 1){
        currentRuleModelIndex = selected.first().topLeft();
        activeRule = rules.get(currentRuleModelIndex.row());
    }else{
        activeRule = NULL;
    }
}

void ShineGUI::removeRule()
{
    if (activeRule != NULL){
        rules.deleteRule(activeRule->id());
    }
}

void ShineGUI::addRule()
{

}
