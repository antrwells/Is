#include "IsScriptEditor.h"
#include <QtWidgets/QApplication>
#include <QtWidgets/QApplication>
#include "qfile.h"
#include "qdrag.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file("c:/trinity/themes/Photoxo.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());



    qApp->setStyleSheet(styleSheet);
    IsScriptEditor w;
    w.show();
    return a.exec();
}
