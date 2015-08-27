#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>
#include "easyblocksmodel.h"

#define DEBUG 0

#if DEBUG
#include "testcode/testcode.h"
#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    /*QTranslator translator;
    translator.load(":/translations/easyblocks_nl.qm");
    a.installTranslator(&translator);*/

    MainWindow w(&a);
    w.showMaximized();

    QStringList args = QCoreApplication::arguments();
    if (args.size() > 1)
        w.openProject(args.at(1));

#if DEBUG
    testCode();
#endif

    return a.exec();
}

