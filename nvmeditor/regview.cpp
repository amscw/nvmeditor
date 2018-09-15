#include "regview.h"
#include "regmap.h"

// TODO: кодогенераторы нам в помощь! (MAKE_SOMETH...)

// InitControl1_c
InitControl1_c::InitControl1_c(QWidget *pwgt) : regWidget_c(pwgt)
{
    try {
        createReg();
    } catch (regExc_c &) {
        throw;
    }
    build();
}

void InitControl1_c::createReg()
{
    std::unique_ptr<reg_c> p;
    try {
        p = std::make_unique<regInitControl1_c>();
    } catch (regExc_c &) {
        throw ;
    }
    m_reg.swap(p);
}

// PCIeInitConfiguration3_c
PCIeInitConfiguration3_c::PCIeInitConfiguration3_c(QWidget *pwgt) : regWidget_c(pwgt)
{
    try {
        createReg();
    } catch (regExc_c &) {
        throw;
    }
    build();
}

void PCIeInitConfiguration3_c::createReg()
{
    std::unique_ptr<reg_c> p;
    try {
        p = std::make_unique<regPCIeInitConfiguration3_c>();
    } catch (regExc_c &) {
        throw ;
    }
    m_reg.swap(p);
}
