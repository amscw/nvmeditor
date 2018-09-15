#include "mainwindow.h"
#include <QApplication>

#include "regmap.h"
#include "regwgt.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    dummyReg_c *reg;
    try {
        reg_c::LoadNVMImage("M:\\git\\nvmeditor\\build-nvmeditor-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\debug\\82574l.eep");
        reg = new dummyReg_c;
        reg->show();
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }


    return a.exec();
}
