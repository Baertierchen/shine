#include "keystore.h"

KeyStore::KeyStore(QObject *parent): QObject(parent),
    m_settings(QStandardPaths::standardLocations(QStandardPaths::ConfigLocation).first() + "/shine/shine.conf", QSettings::IniFormat)
{
}

QString KeyStore::apiKey() const
{
    return m_settings.value("apiKey").toString();
}

void KeyStore::setApiKey(const QString &apiKey)
{
    m_settings.setValue("apiKey", apiKey);
    emit apiKeyChanged();
}
