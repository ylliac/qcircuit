
#include <QtGui/QApplication>

#include "demo/MainWindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow mainWindow;
    mainWindow.show();
    int result = app.exec();

    return result;
    
//    QApplication app(argv, args);
//    MainWindow mainWindow;
//    mainWindow.setGeometry(100, 100, 800, 500);
//    mainWindow.show();
//
//    return app.exec();
}

