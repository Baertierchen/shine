#ifndef ICON_MAP
#define ICON_MAP

#include <QObject>
#include <QMap>
#include <QString>
#include <QDebug>

class IconMap : public QObject {
    Q_OBJECT

public:
    IconMap(){
        iconMap["LCT001"] = "icons/a19_filled.svg";
        iconMap["LCT002"] = "icons/br30_filled.svg";
        iconMap["LCT003"] = "icons/gu10_filled.svg";
        iconMap["LST001"] = "icons/lightstrip_filled.svg";
        iconMap["LLC010"] = "icons/lc_iris_filled.svg";
        iconMap["LLC011"] = "icons/lc_bloom_filled.svg";
        iconMap["LLC012"] = "icons/lc_bloom_filled.svg";
        iconMap["LLC006"] = "icons/lc_iris_filled.svg";
        iconMap["LLC007"] = "icons/lc_aura_filled.svg";
        iconMap["LLC013"] = "icons/storylight_filled.svg";
        iconMap["LWB004"] = "icons/a19_filled.svg";
        iconMap["LLM001"] = "icons/entity_filled.svg";
        iconMap["LLM010"] = "icons/entity_filled.svg";
        iconMap["LLM011"] = "icons/entity_filled.svg";
        iconMap["LLM012"] = "icons/entity_filled.svg";
        iconMap["LLC020"] = "icons/huego_filled.svg";
    }

    static IconMap* instance(){
        if (!s_instance) {
            s_instance = new IconMap();
        }
        return s_instance;
    }

    Q_INVOKABLE QString getIcon(QString modelID){
        return iconMap[modelID];
    }

private:
    QMap<QString, QString> iconMap;
    static IconMap* s_instance;
};

#endif // ICON_MAP

