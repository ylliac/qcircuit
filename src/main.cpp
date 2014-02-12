
#include <QtGui/QApplication>

#include "demo/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    int result = app.exec();

    return result;
}

