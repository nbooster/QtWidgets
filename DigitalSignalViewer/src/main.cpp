#include "digitalsignalviewerwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Renesas Electronics");
    QCoreApplication::setOrganizationDomain("www.renesas.com");
    QCoreApplication::setApplicationName("Digital Signal Viewer");
    QCoreApplication::setApplicationVersion("1.0.0");
    DigitalSignalViewerWidget w;
    w.show();
    return a.exec();
}
