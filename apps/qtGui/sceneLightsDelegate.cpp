#include "sceneLightsDelegate.h"

SceneLightsDelegate::SceneLightsDelegate(Lights* lights)
{
    this->lights = lights;
}

QString SceneLightsDelegate::displayText(const QVariant &value, const QLocale &locale) const
{
    Q_UNUSED(locale);
    int lightIndex = value.toInt();

    return lights->get(lightIndex-1)->name();
}
