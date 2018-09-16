#include "mainwindow.h"
#include <QApplication>

#include "reg.h"
#include "regwgt.h"
#include "regmap.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;



    regWgtViewer_c<regInitControl1_c> *pInitControl1;

    try {
        reg_c::LoadNVMImage("M:\\git\\nvmeditor\\build-nvmeditor-Desktop_Qt_5_10_0_MinGW_32bit-Debug\\debug\\82574l.eep");
        pInitControl1 = new regWgtViewer_c<regInitControl1_c>;
        pInitControl1->show();
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }


    w.show();

    return a.exec();
}
