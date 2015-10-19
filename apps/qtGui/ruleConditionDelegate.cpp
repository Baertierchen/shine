#include "ruleConditionDelegate.h"

RuleConditionDelegate::RuleConditionDelegate()
{

}

QSize RuleConditionDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    (void) option;
    QString string;
    QFont font;
    switch (index.column()){
    case 0:
        string = sensorName(index);
        font.setBold(true);
        break;
    case 1:
        string = resource(index);
        font.setItalic(true);
        break;
    case 2:
        string = operatorStr(index);
        break;
    case 3:
        string = value(index);
        break;
    }
    QFontMetrics fm(font);

    return(QSize(fm.width(string) + 2*SPACING,fm.height() + 2*MARGIN));
}

void RuleConditionDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    painter->save();

    QString string;
    QFont font;
    switch (index.column()){
    case 0:
        string = sensorName(index);
        font.setBold(true);
        break;
    case 1:
        string = resource(index);
        font.setItalic(true);
        break;
    case 2:
        string = operatorStr(index);
        break;
    case 3:
        string = value(index);
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

QString RuleConditionDelegate::buildString(const QModelIndex &index) const
{
    QString condString = QString("%1%2 %3 %4")
            .arg(sensorName(index))
            .arg(resource(index))
            .arg(operatorStr(index))
            .arg(value(index));
    return condString;
}

QString RuleConditionDelegate::sensorName(const QModelIndex &index) const
{
    QString sensorID = index.data(Conditions::RoleSensor).toString();
    Sensor* sensor = Sensors::instance()->findSensor(sensorID);
    QString sensorName;
    if (sensor == NULL){
        sensorName = "UNKNOWN_SENSOR";
    }else{
        sensorName = sensor->name();
    }
    return sensorName;
}

QString RuleConditionDelegate::resource(const QModelIndex &index) const
{
    QString resource = index.data(Conditions::RoleResource).toString();
    return resource;
}

QString RuleConditionDelegate::operatorStr(const QModelIndex &index) const
{
    Condition::Operator op = (Condition::Operator)index.data(Conditions::RoleOperator).toInt();
    QString operatorStr;
    switch (op){
    case Condition::eq: operatorStr = "equals"; break;
    case Condition::gt: operatorStr = "greater"; break;
    case Condition::lt: operatorStr = "less"; break;
    case Condition::dx: operatorStr = "changed"; break;
    case Condition::unknown: operatorStr = "unknown"; break;
    }
    return operatorStr;
}

QString RuleConditionDelegate::value(const QModelIndex &index) const
{
    QString value = index.data(Conditions::RoleValue).toString();
    return value;
}
