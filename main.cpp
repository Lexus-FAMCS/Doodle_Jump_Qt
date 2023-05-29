
#include "controller.h"

#include <time.h>
#include <QApplication>
#include <QFont>
#include <QFontDatabase>
#include <QStringList>

int main(int argc, char *argv[])
{
    srand(time(0));
    QApplication a(argc, argv);
    Controller w;
    w.show();
    QStringList list = QFontDatabase().families();
    qDebug() << "Is contain" << list.contains("Aqua");
    return a.exec();
}
