#include "shinegui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ShineGUI w;
    w.show();

    return a.exec();
}
