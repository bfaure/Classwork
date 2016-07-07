#include "mainwindow.h"
#include <QApplication>
#include "shared_data.h"

//Written by Brian Faure
//Tested by Brian Faure
//Debugged by Brian Faure

int main(int argc, char *argv[])
{
    QApplication prog(argc, argv);
    MainWindow w;
    w.show();
    qRegisterMetaType<shared_data>("shared_data");

    return prog.exec();
}
