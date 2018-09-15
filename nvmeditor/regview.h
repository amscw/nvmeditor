#ifndef REGVIEW_H
#define REGVIEW_H

#include "regwgt.h"

class InitControl1_c : public regWidget_c
{
    void createReg();

public:
    InitControl1_c(QWidget *pwgt = nullptr);
};

class PCIeInitConfiguration3_c : public regWidget_c
{
    void createReg();

public:
    PCIeInitConfiguration3_c(QWidget *pwgt = nullptr);
};


#endif // REGVIEW_H
