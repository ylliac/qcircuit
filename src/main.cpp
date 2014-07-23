
#include <QtGui/QApplication>

#include "demo/MainWindow.h"
#include "editor/FBPEditor.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    MainWindow mainWindow;
    mainWindow.show();
    
//    FBPEditor fbpEditor;
//    fbpEditor.setGeometry(100, 100, 1500, 800);
//    fbpEditor.show();

    return app.exec();
}

