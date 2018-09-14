#ifndef REGMAP_H
#define REGMAP_H

#include "reg.h"

class regEthernetAddress_c : public reg_c
{

public:
    regEthernetAddress_c();
    virtual ~regEthernetAddress_c();
};



class regPBA_c : public reg_c
{
public:
    regPBA_c();
    virtual ~regPBA_c();
};


class regInitControl1_c : public regViewer_c
{
    using flatp_t = struct
    {
        std::uint16_t LoadDeviceID : 1;
        std::uint16_t LoadSubsystemIDs : 1;
        std::uint16_t : 2;
        std::uint16_t ILOS : 1;
        std::uint16_t : 5;
        std::uint16_t FD : 1;
        std::uint16_t FRCSPD : 1;
        std::uint16_t : 4;
    } __attribute__((__packed__)) * ;

    const flatp_t flatp;

public:
    regInitControl1_c();
    virtual ~regInitControl1_c();

    virtual void ToDefault() noexcept;
    virtual void Save() noexcept;
};

//class regSubsystemID_c: public regViewer_c
//{
//public:
//    regSubsystemID_c();
//    virtual ~regSubsystemID_c(){}
//};


//class regSubsystemVendorID_c: public regViewer_c
//{
//public:
//    regSubsystemVendorID_c();
//    virtual ~regSubsystemVendorID_c(){}
//};

//class regDeviceID_c: public regViewer_c
//{
//public:
//    regDeviceID_c();
//    virtual ~regDeviceID_c(){}
//};

//class regInitControl2_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 8;
//        std::uint16_t NVSIZE : 4;
//        std::uint16_t NVMTYPE: 1;
//        std::uint16_t MNGM : 2;
//        std::uint16_t APM_PME : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regInitControl2_c();
//    virtual ~regInitControl2_c(){}
//};

//class regNVMWord0_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regNVMWord0_c();
//    virtual ~regNVMWord0_c(){}
//};

//class regNVMWord1_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t RAM_PWR_SAVE_EN: 1;
//        std::uint16_t : 7;
//        std::uint16_t FSECER: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regNVMWord1_c();
//    virtual ~regNVMWord1_c(){}
//};

//class regNVMWord2_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 2;
//        std::uint16_t SECSIZE: 2;
//        std::uint16_t : 4;
//        std::uint16_t SIGN: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regNVMWord2_c();
//    virtual ~regNVMWord2_c(){}
//};

//class regPCIeElectricalIdleDelay_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regPCIeElectricalIdleDelay_c();
//    virtual ~regPCIeElectricalIdleDelay_c(){}
//};

//class  regPCIeInitConfiguration1_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t L0s_Co_Ext_Latency : 3;
//        std::uint16_t L0s_Se_Ext_Latency : 3;
//        std::uint16_t L0s_Acc_Latency : 3;
//        std::uint16_t L1_Act_Acc_Latency : 3;
//        std::uint16_t L1_Act_Ext_Latency : 3;
//        std::uint16_t : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regPCIeInitConfiguration1_c();
//    virtual ~regPCIeInitConfiguration1_c(){}
//};

//class  regPCIeInitConfiguration2_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t NFTS : 8;
//        std::uint16_t ExtraNFTS : 4;
//        std::uint16_t SER_EN : 1;
//        std::uint16_t : 2;
//        std::uint16_t DLLPTimerEnable : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regPCIeInitConfiguration2_c();
//    virtual ~regPCIeInitConfiguration2_c(){}
//};


class  regPCIeInitConfiguration3_c : public regViewer_c
{
    using flatp_t = struct
    {
        std::uint16_t LoopbackPolarityInversion : 1;
        std::uint16_t Slot_Clock_Cfg : 1;
        std::uint16_t Act_Stat_PM_Sup : 2;
        std::uint16_t : 4;
        std::uint16_t Packet_Size : 1;
        std::uint16_t IO_Sup : 1;
        std::uint16_t PCIE_Cap : 2;
        std::uint16_t Cache_Lsize : 1;
        std::uint16_t Ack_Nak_Sch : 1;
        std::uint16_t Scram_dis : 1;
        std::uint16_t Master_Enable : 1;
    } __attribute__((__packed__)) * ;

    const flatp_t flatp;

public:
    regPCIeInitConfiguration3_c();
    virtual ~regPCIeInitConfiguration3_c();

    virtual void ToDefault() noexcept;
    virtual void Save() noexcept;
};

//class  regPCIeControl_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t Latency_To_Enter_L1 : 2;
//        std::uint16_t ElectricalIDLE : 1;
//        std::uint16_t : 1;
//        std::uint16_t SkipDisable: 1;
//        std::uint16_t L2Disable : 1;
//        std::uint16_t : 1;
//        std::uint16_t MSI_X_NUM : 3;
//        std::uint16_t LeakyBucketDisable : 1;
//        std::uint16_t GoodRecovery : 1;
//        std::uint16_t PCIE_LTSSM : 1;
//        std::uint16_t PCIEDownResetDisable : 1;
//        std::uint16_t Latency_To_Enter_L2 : 1;
//        std::uint16_t PCIE_RX_Valid : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regPCIeControl_c();
//    virtual ~regPCIeControl_c(){}
//};

//class  regPHYConfiguration_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t LED1Mode : 4;
//        std::uint16_t : 1;
//        std::uint16_t LED1BlinkMode : 1;
//        std::uint16_t LED1Invert : 1;
//        std::uint16_t LED1Blink : 1;
//        std::uint16_t : 1;
//        std::uint16_t D0LPLU : 1;
//        std::uint16_t LPLU : 1;
//        std::uint16_t Disable1000inNon_D0a : 1;
//        std::uint16_t ClassAB : 1;
//        std::uint16_t : 1;
//        std::uint16_t GigaDisable : 1;
//        std::uint16_t : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regPHYConfiguration_c();
//    virtual ~regPHYConfiguration_c(){}
//};

//class  regDeviceREVID_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regDeviceREVID_c();
//    virtual ~regDeviceREVID_c(){}
//};

//class  regLED0_2_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t LED0Mode: 4;
//        std::uint16_t : 1;
//        std::uint16_t LED0BlinkMode: 1;
//        std::uint16_t LED0Invert: 1;
//        std::uint16_t LED0Blink: 1;
//        std::uint16_t LED2Mode: 4;
//        std::uint16_t : 1;
//        std::uint16_t LED2BlinkMode: 1;
//        std::uint16_t LED2Invert: 1;
//        std::uint16_t LED2Blink: 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regLED0_2_c();
//    virtual ~regLED0_2_c(){}
//};

//class  regFlashParameters_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 4;
//        std::uint16_t LONGC: 1;
//        std::uint16_t FLSSTn: 1;
//        std::uint16_t : 2;
//        std::uint16_t FDEVER: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regFlashParameters_c();
//    virtual ~regFlashParameters_c(){}
//};

//class  regFlashLANAddress_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 7;
//        std::uint16_t DISLEXP: 1;
//        std::uint16_t LBADD: 4;
//        std::uint16_t LANSIZE: 3;
//        std::uint16_t DISLFB: 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regFlashLANAddress_c();
//    virtual ~regFlashLANAddress_c(){}
//};

//class  regLANPowerConsumption_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t LAND3Power: 5;
//        std::uint16_t : 3;
//        std::uint16_t LAND0Power: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regLANPowerConsumption_c();
//    virtual ~regLANPowerConsumption_c(){}
//};

//class  regSWFlashVendorDetection_c : public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t FlashVendorDetect: 8;
//        std::uint16_t : 6;
//        std::uint16_t DeepSmartPowerDown: 1;
//        std::uint16_t ChecksumValidity: 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;

//public:
//    regSWFlashVendorDetection_c();
//    virtual ~regSWFlashVendorDetection_c(){}
//};

//class regInitControl3_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t No_Phy_Rst: 1;
//        std::uint16_t : 9;
//        std::uint16_t APMEnable: 1;
//        std::uint16_t : 5;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regInitControl3_c();
//    virtual ~regInitControl3_c(){}
//};

//class regAPTSMBusAddress_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t : 1;
//        std::uint16_t MCSMBusAddress: 7;
//        std::uint16_t : 1;
//        std::uint16_t SMBusAddress: 7;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTSMBusAddress_c();
//    virtual ~regAPTSMBusAddress_c(){}
//};

//class regAPTRxEnableParameters_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t InterfaceData: 8;
//        std::uint16_t AlertValue: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTRxEnableParameters_c();
//    virtual ~regAPTRxEnableParameters_c(){}
//};

//class regAPTSMBusControl_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t NotificationTimeout: 8;
//        std::uint16_t SMBusFragmentSize: 8;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTSMBusControl_c();
//    virtual ~regAPTSMBusControl_c(){}
//};

//class regAPTInitFlags_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t NotificationMethod: 2;
//        std::uint16_t SMBBlockReadCommand: 1;
//        std::uint16_t SMBARPDisabled: 1;
//        std::uint16_t ForceTCOEnable: 1;
//        std::uint16_t : 11;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTInitFlags_c();
//    virtual ~regAPTInitFlags_c(){}
//};

//class regAPTManagementConfiguration_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t RAMPartitioning: 2;
//        std::uint16_t : 2;
//        std::uint16_t CodeSize: 10;
//        std::uint16_t : 2;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTManagementConfiguration_c();
//    virtual ~regAPTManagementConfiguration_c(){}
//};

//class regAPTuCodePointer_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t Pointer: 4;
//        std::uint16_t : 12;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regAPTuCodePointer_c();
//    virtual ~regAPTuCodePointer_c(){}
//};

//class regLeastSignificantWordOfFirmwareID_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t FirmwareID: 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regLeastSignificantWordOfFirmwareID_c();
//    virtual ~regLeastSignificantWordOfFirmwareID_c(){}
//};

//class regMostSignificantWordOfFirmwareID_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t FirmwareID: 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regMostSignificantWordOfFirmwareID_c();
//    virtual ~regMostSignificantWordOfFirmwareID_c(){}
//};

//class regNC_SIManagementConfiguration_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t RAMPartitioning: 2;
//        std::uint16_t : 2;
//        std::uint16_t CodeSize: 10;
//        std::uint16_t : 2;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regNC_SIManagementConfiguration_c();
//    virtual ~regNC_SIManagementConfiguration_c(){}
//};

//class regNC_SIConfiguration_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t uCodePointer: 12;
//        std::uint16_t PackageID: 3;
//        std::uint16_t : 1;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regNC_SIConfiguration_c();
//    virtual ~regNC_SIConfiguration_c(){}
//};

//class regVPDPointer_c: public regViewer_c
//{
//    using flatp_t = struct
//    {
//        std::uint16_t VDP: 16;
//    } __attribute__((__packed__)) * ;

//    const flatp_t flatp;
//public:
//    regVPDPointer_c();
//    virtual ~regVPDPointer_c(){}
//};

//class regSWSection_c: public regViewer_c
//{
//public:
//    regSWSection_c();
//    virtual ~regSWSection_c(){}
//};

//class regSoftwareChecksum_c: public regViewer_c
//{
//public:
//    regSoftwareChecksum_c();
//    virtual ~regSoftwareChecksum_c(){}
//};

#endif // REGMAP_H
