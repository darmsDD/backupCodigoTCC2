#include "inc/mainwindow.h"
#include "inc/threadcontroller.h"
#include <QApplication>
#include <QThread>
int main(int argc, char *argv[])
{
    qputenv("QT_IM_MODULE", QByteArray("qtvirtualkeyboard"));
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    ThreadController b;

    return a.exec();
}
