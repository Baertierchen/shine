#ifndef SCENELIGHTSDELEGATE_H
#define SCENELIGHTSDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>

#include "scene.h"
#include "light.h"
#include "lights.h"
#include "delegateConfig.h"

class SceneLightsDelegate : public QStyledItemDelegate
{
public:
    SceneLightsDelegate(Lights* lights);

public:
    virtual QString displayText(const QVariant &value, const QLocale &locale) const;

private:
    Lights* lights;
};

#endif // SCENELIGHTSDELEGATE_H
