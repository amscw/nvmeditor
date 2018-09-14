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
        regInitControl1_c regInitControl;
        regPCIeInitConfiguration3_c regPCIeInitConfiguration3;
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }


    return a.exec();
}
