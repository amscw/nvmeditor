#include "mainwindow.h"
#include <QApplication>

#include "reg.h"
#include "regview.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    InitControl1_c *pInitControl1;
    PCIeInitConfiguration3_c *pPCIeInitConfiguration3;

    try {
        reg_c::LoadNVMImage("M:\\git\\nvmeditor\\build-nvmeditor-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\debug\\82574l.eep");
        pInitControl1 = new InitControl1_c;
        pPCIeInitConfiguration3 = new PCIeInitConfiguration3_c;
        pInitControl1->show();
        pPCIeInitConfiguration3->show();
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }


    w.show();

    return a.exec();
}
