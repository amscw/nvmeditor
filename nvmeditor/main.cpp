#include "mainwindow.h"
#include <QApplication>

#include "regmap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    try {
        reg_c::LoadNVMImage("M:\\git\\nvmeditor\\build-nvmeditor-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\debug\\82574l.eep");
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }
    regEthernetAddress_c regEthernetAddress;
    regInitControl1_c regInitControl;

    return a.exec();
}
