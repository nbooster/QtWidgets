#include "fileassociationmanagerwidget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QCoreApplication::setOrganizationName("Renesas Electronics");
    QCoreApplication::setOrganizationDomain("www.renesas.com");
    QCoreApplication::setApplicationName("File Association Manager");
    QCoreApplication::setApplicationVersion("1.0.0");
    FileAssociationManagerWidget w;
    w.resize(1500, 800);
    w.setWindowFlags(w.windowFlags() & ~Qt::WindowContextHelpButtonHint);
    w.show();
    return a.exec();
}
