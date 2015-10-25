#include "ruleActionDelegate.h"

RuleActionDelegate::RuleActionDelegate()
{
    sensors = Sensors::instance();
}

QSize RuleActionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void) option;
    QString string;
    QFont font;
    switch (index.column()){
    case 0:
        string = address(index);
        font.setBold(true);
        break;
    case 1:
        string = methodStr(index);
        font.setItalic(true);
        break;
    case 2:
        string = body(index);
        break;
    }
    QFontMetrics fm(font);

    return(QSize(fm.width(string) + 2*SPACING,fm.height() + 2*MARGIN));
}

void RuleActionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QString string;
    QFont font;
    switch (index.column()){
    case 0:
        string = address(index);
        font.setBold(true);
        break;
    case 1:
        string = methodStr(index);
        font.setItalic(true);
        break;
    case 2:
        string = body(index);
        break;
    }

    QFontMetrics fm(font);
    QRect nameRect;

    nameRect.setLeft(option.rect.left() + SPACING);
    nameRect.setTop(option.rect.top() + option.rect.height()/2 - fm.height()/2);
    nameRect.setBottom(option.rect.bottom() - option.rect.height()/2 + fm.height()/2);
    nameRect.setRight(option.rect.right());

    if (option.state & QStyle::State_Selected){
        painter->fillRect(option.rect, option.palette.highlight());
    }

    painter->setFont(font);
    painter->drawText(nameRect,string);

    painter->restore();
}

QString RuleActionDelegate::address(const QModelIndex &index) const
{
    QString address = index.data(Actions::RoleAddress).toString();
    if (address == "/groups/0/action") return "All Lights";
    if (address.left(9) == "/sensors/"){
        address = address.mid(9);
        int slashPos = address.indexOf("/");
        QString sensorID = address.left(slashPos);
        Sensor* sensor = sensors->findSensor(sensorID);
        if (sensor == NULL) return QString("Unknown Sensor (%1)").arg(sensorID);
        return sensor->name();
    }
    return address;
}

QString RuleActionDelegate::methodStr(const QModelIndex &index) const
{
    Action::Method method = (Action::Method)index.data(Actions::RoleMethod).toInt();
    QString methodStr;
    switch (method){
    case Action::POST: methodStr = "POST"; break;
    case Action::PUT: methodStr = "PUT"; break;
    case Action::DELETE: methodStr = "DELETE"; break;
    case Action::Unknown: methodStr = "unknown"; break;
    }
    return methodStr;
}

QString RuleActionDelegate::body(const QModelIndex &index) const
{
    QString bodyStr;
    QVariantMap body = index.data(Actions::RoleBody).toMap();
    for (QVariantMap::Iterator it = body.begin(); it != body.end(); it++){
        bodyStr.append(it.key());
        bodyStr.append(":");
        bodyStr.append(it.value().toString());
        bodyStr.append(", ");
    }

    return bodyStr.left(bodyStr.length()-2);
}
