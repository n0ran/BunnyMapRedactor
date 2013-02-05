#include <QtWidgets/QApplication>
#include "mainwindow.h"

//#include "libxml/xmlexports.h"
//#pragma comment( lib, "libxml2.lib")

int main(int argc, char *argv[])
{
    Q_INIT_RESOURCE(resources);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    return a.exec();
}
