#include "regmap.h"

/**
 * NB!
 * К сожалению на сегодняшний день еще не придуман способ итерирования битовых полей POD-структур :(
 * К каждому полю приходится обращаться явно
 */

regEthernetAddress_c::regEthernetAddress_c() : reg_c("Ethernet Address", 0x00, 3)
{
}
regEthernetAddress_c::~regEthernetAddress_c(){}

regPBA_c::regPBA_c() : reg_c("PBA", 0x08, 2)
{
}
regPBA_c::~regPBA_c(){}

// Init Control 1
regInitControl1_c::regInitControl1_c() : regViewer_c("Init Control 1", 0x0A, 1),
    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
{
    ToDefault();
    dumpWords();
}

regInitControl1_c::~regInitControl1_c(){}

void regInitControl1_c::ToDefault() noexcept
{
    m_listFields.clear();
    m_listFields.emplace_back("FRCSPD", static_cast<std::uint16_t>(flatp->FRCSPD));
    m_listFields.emplace_back("FD", static_cast<std::uint16_t>(flatp->FD));
    m_listFields.emplace_back("ILOS", static_cast<std::uint16_t>(flatp->ILOS));
    m_listFields.emplace_back("LoadSubsystemIDs", static_cast<std::uint16_t>(flatp->LoadSubsystemIDs));
    m_listFields.emplace_back("LoadDeviceID", static_cast<std::uint16_t>(flatp->LoadDeviceID));
}

void regInitControl1_c::Save() noexcept
{
    try
    {
        flatp->FRCSPD = GetFieldValue("FRCSPD");
        flatp->FD = GetFieldValue("FD");
        flatp->ILOS = GetFieldValue("ILOS");
        flatp->LoadSubsystemIDs = GetFieldValue("LoadSubsystemIDs");
        flatp->LoadDeviceID = GetFieldValue("LoadDeviceID");
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }
}

//// Subsystem ID
//regSubsystemID_c::regSubsystemID_c() :regViewer_c("Subsystem ID", 0x0B,1)
//{

//}

//regSubsystemVendorID_c::regSubsystemVendorID_c() :regViewer_c("Subsystem Vendor ID", 0x0C,1)
//{

//}

//regDeviceID_c::regDeviceID_c() :regViewer_c("Device ID", 0x0D,1)
//{

//}

//regInitControl2_c::regInitControl2_c() : regViewer_c("Init Control 2", 0x0F, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("APM_PME", static_cast<std::uint16_t>(flatp->APM_PME));
//    m_listFields.emplace_back("MNGM", static_cast<std::uint16_t>(flatp->MNGM));
//    m_listFields.emplace_back("NVMTYPE", static_cast<std::uint16_t>(flatp->NVMTYPE));
//    m_listFields.emplace_back("NVSIZE", static_cast<std::uint16_t>(flatp->NVSIZE));
//    dumpWords();
//}

//regNVMWord0_c::regNVMWord0_c() : regViewer_c("NVM Word 0", 0x10, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    dumpWords();
//}

//regNVMWord1_c::regNVMWord1_c() : regViewer_c("NVM Word 1", 0x11, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("FSECER", static_cast<std::uint16_t>(flatp->FSECER));
//    m_listFields.emplace_back("RAM_PWR_SAVE_EN", static_cast<std::uint16_t>(flatp->RAM_PWR_SAVE_EN));
//    dumpWords();
//}

//regNVMWord2_c::regNVMWord2_c() : regViewer_c("NVM Word 2", 0x12, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("SIGN", static_cast<std::uint16_t>(flatp->SIGN));
//    m_listFields.emplace_back("SECSIZE", static_cast<std::uint16_t>(flatp->SECSIZE));
//    dumpWords();
//}

//regPCIeElectricalIdleDelay_c::regPCIeElectricalIdleDelay_c() :regViewer_c("PCIe Electrical Idle Delay", 0x17, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    dumpWords();
//}

//regPCIeInitConfiguration1_c::regPCIeInitConfiguration1_c() : regViewer_c("PCIe Init Configuration 1", 0x18, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("L1_Act_Ext_Latency", static_cast<std::uint16_t>(flatp->L1_Act_Ext_Latency));
//    m_listFields.emplace_back("L1_Act_Acc_Latency", static_cast<std::uint16_t>(flatp->L1_Act_Acc_Latency));
//    m_listFields.emplace_back("L0s_Acc_Latency", static_cast<std::uint16_t>(flatp->L0s_Acc_Latency));
//    m_listFields.emplace_back("L0s_Se_Ext_Latency", static_cast<std::uint16_t>(flatp->L0s_Se_Ext_Latency));
//    m_listFields.emplace_back("L0s_Co_Ext_Latency", static_cast<std::uint16_t>(flatp->L0s_Co_Ext_Latency));
//    dumpWords();
//}

//regPCIeInitConfiguration2_c::regPCIeInitConfiguration2_c() : regViewer_c("PCIe Init Configuration 2", 0x19, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("DLLPTimerEnable", static_cast<std::uint16_t>(flatp->DLLPTimerEnable));
//    m_listFields.emplace_back("SER_EN", static_cast<std::uint16_t>(flatp->SER_EN));
//    m_listFields.emplace_back("ExtraNFTS", static_cast<std::uint16_t>(flatp->ExtraNFTS));
//    m_listFields.emplace_back("NFTS", static_cast<std::uint16_t>(flatp->NFTS));
//    dumpWords();
//}

// PCIe Init Configuration 3
regPCIeInitConfiguration3_c::regPCIeInitConfiguration3_c() : regViewer_c("PCIe Init Configuration 3", 0x1A, 1),
    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
{
    ToDefault();
    dumpWords();
}

regPCIeInitConfiguration3_c::~regPCIeInitConfiguration3_c()
{

}

void regPCIeInitConfiguration3_c::ToDefault() noexcept
{
    m_listFields.clear();
    m_listFields.emplace_back("Master_Enable", static_cast<std::uint16_t>(flatp->Master_Enable));
    m_listFields.emplace_back("Scram_dis", static_cast<std::uint16_t>(flatp->Scram_dis));
    m_listFields.emplace_back("Ack_Nak_Sch", static_cast<std::uint16_t>(flatp->Ack_Nak_Sch));
    m_listFields.emplace_back("Cache_Lsize", static_cast<std::uint16_t>(flatp->Cache_Lsize));
    m_listFields.emplace_back("PCIE_Cap", static_cast<std::uint16_t>(flatp->PCIE_Cap));
    m_listFields.emplace_back("IO_Sup", static_cast<std::uint16_t>(flatp->IO_Sup));
    m_listFields.emplace_back("Packet_Size", static_cast<std::uint16_t>(flatp->Packet_Size));
    m_listFields.emplace_back("Act_Stat_PM_Sup", static_cast<std::uint16_t>(flatp->Act_Stat_PM_Sup));
    m_listFields.emplace_back("Slot_Clock_Cfg", static_cast<std::uint16_t>(flatp->Slot_Clock_Cfg));
    m_listFields.emplace_back("LoopbackPolarityInversion", static_cast<std::uint16_t>(flatp->LoopbackPolarityInversion));
}

void regPCIeInitConfiguration3_c::Save() noexcept
{
    try
    {
        flatp->Master_Enable = GetFieldValue("Master_Enable");
        flatp->Scram_dis = GetFieldValue("Scram_dis");
        flatp->Ack_Nak_Sch = GetFieldValue("Ack_Nak_Sch");
        flatp->Cache_Lsize = GetFieldValue("Cache_Lsize");
        flatp->PCIE_Cap = GetFieldValue("PCIE_Cap");
        flatp->IO_Sup = GetFieldValue("IO_Sup");
        flatp->Packet_Size = GetFieldValue("Packet_Size");
        flatp->Act_Stat_PM_Sup = GetFieldValue("Act_Stat_PM_Sup");
        flatp->Slot_Clock_Cfg = GetFieldValue("Slot_Clock_Cfg");
        flatp->LoopbackPolarityInversion = GetFieldValue("LoopbackPolarityInversion");
    } catch (regExc_c &exc) {
        exc.ToStderr();
    }
}

//regPCIeControl_c::regPCIeControl_c() : regViewer_c("PCIe Control", 0x1B, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("Latency_To_Enter_L1", static_cast<std::uint16_t>(flatp->Latency_To_Enter_L1));
//    m_listFields.emplace_back("ElectricalIDLE", static_cast<std::uint16_t>(flatp->ElectricalIDLE));
//    m_listFields.emplace_back("SkipDisable", static_cast<std::uint16_t>(flatp->SkipDisable));
//    m_listFields.emplace_back("L2Disable", static_cast<std::uint16_t>(flatp->L2Disable));
//    m_listFields.emplace_back("MSI_X_NUM", static_cast<std::uint16_t>(flatp->MSI_X_NUM));
//    m_listFields.emplace_back("LeakyBucketDisable", static_cast<std::uint16_t>(flatp->LeakyBucketDisable));
//    m_listFields.emplace_back("GoodRecovery", static_cast<std::uint16_t>(flatp->GoodRecovery));
//    m_listFields.emplace_back("PCIE_LTSSM", static_cast<std::uint16_t>(flatp->PCIE_LTSSM));
//    m_listFields.emplace_back("PCIEDownResetDisable", static_cast<std::uint16_t>(flatp->PCIEDownResetDisable));
//    m_listFields.emplace_back("Latency_To_Enter_L2", static_cast<std::uint16_t>(flatp->Latency_To_Enter_L2));
//    m_listFields.emplace_back("PCIE_RX_Valid", static_cast<std::uint16_t>(flatp->PCIE_RX_Valid));
//    dumpWords();
//}

//regPHYConfiguration_c::regPHYConfiguration_c() : regViewer_c("PHY Configuration | LEDCTL 1", 0x1C, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("LED1Mode", static_cast<std::uint16_t>(flatp->LED1Mode));
//    m_listFields.emplace_back("LED1BlinkMode", static_cast<std::uint16_t>(flatp->LED1BlinkMode));
//    m_listFields.emplace_back("LED1Invert", static_cast<std::uint16_t>(flatp->LED1Invert));
//    m_listFields.emplace_back("LED1Blink", static_cast<std::uint16_t>(flatp->LED1Blink));
//    m_listFields.emplace_back("D0LPLU", static_cast<std::uint16_t>(flatp->D0LPLU));
//    m_listFields.emplace_back("LPLU", static_cast<std::uint16_t>(flatp->LPLU));
//    m_listFields.emplace_back("Disable1000inNon_D0a", static_cast<std::uint16_t>(flatp->Disable1000inNon_D0a));
//    m_listFields.emplace_back("ClassAB", static_cast<std::uint16_t>(flatp->ClassAB));
//    m_listFields.emplace_back("GigaDisable", static_cast<std::uint16_t>(flatp->GigaDisable));
//    dumpWords();
//}

//regDeviceREVID_c::regDeviceREVID_c() : regViewer_c("Device REV ID", 0x1E, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    dumpWords();
//}

//regLED0_2_c::regLED0_2_c() : regViewer_c("LED 0-2", 0x1F, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("LED0Mode", static_cast<std::uint16_t>(flatp->LED0Mode));
//    m_listFields.emplace_back("LED0BlinkMode", static_cast<std::uint16_t>(flatp->LED0BlinkMode));
//    m_listFields.emplace_back("LED0Invert", static_cast<std::uint16_t>(flatp->LED0Invert));
//    m_listFields.emplace_back("LED0Blink", static_cast<std::uint16_t>(flatp->LED0Blink));
//    m_listFields.emplace_back("LED2Mode", static_cast<std::uint16_t>(flatp->LED2Mode));
//    m_listFields.emplace_back("LED2BlinkMode", static_cast<std::uint16_t>(flatp->LED2BlinkMode));
//    m_listFields.emplace_back("LED2Invert", static_cast<std::uint16_t>(flatp->LED2Invert));
//    m_listFields.emplace_back("LED2Blink", static_cast<std::uint16_t>(flatp->LED2Blink));
//    dumpWords();
//}

//regFlashParameters_c::regFlashParameters_c() : regViewer_c("Flash Parameters", 0x20, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("FDEVER", static_cast<std::uint16_t>(flatp->FDEVER));
//    m_listFields.emplace_back("FLSSTn", static_cast<std::uint16_t>(flatp->FLSSTn));
//    m_listFields.emplace_back("LONGC", static_cast<std::uint16_t>(flatp->LONGC));
//    dumpWords();
//}

//regFlashLANAddress_c::regFlashLANAddress_c() : regViewer_c("Flash LAN Address", 0x21, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("DISLFB", static_cast<std::uint16_t>(flatp->DISLFB));
//    m_listFields.emplace_back("LANSIZE", static_cast<std::uint16_t>(flatp->LANSIZE));
//    m_listFields.emplace_back("LBADD", static_cast<std::uint16_t>(flatp->LBADD));
//    m_listFields.emplace_back("DISLEXP", static_cast<std::uint16_t>(flatp->DISLEXP));
//    dumpWords();
//}

//regLANPowerConsumption_c::regLANPowerConsumption_c() : regViewer_c("LAN Power Consumption", 0x22, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("LAND0Power", static_cast<std::uint16_t>(flatp->LAND0Power));
//    m_listFields.emplace_back("LAND3Power", static_cast<std::uint16_t>(flatp->LAND3Power));
//    dumpWords();
//}

//regSWFlashVendorDetection_c::regSWFlashVendorDetection_c() : regViewer_c("SW Flash Vendor Detection", 0x23, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("ChecksumValidity", static_cast<std::uint16_t>(flatp->ChecksumValidity));
//    m_listFields.emplace_back("DeepSmartPowerDown", static_cast<std::uint16_t>(flatp->DeepSmartPowerDown));
//    m_listFields.emplace_back("FlashVendorDetect", static_cast<std::uint16_t>(flatp->FlashVendorDetect));
//    dumpWords();
//}

//regInitControl3_c::regInitControl3_c() : regViewer_c("Init Control 3", 0x24, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("APMEnable", static_cast<std::uint16_t>(flatp->APMEnable));
//    m_listFields.emplace_back("No_Phy_Rst", static_cast<std::uint16_t>(flatp->No_Phy_Rst));
//    dumpWords();
//}

//regAPTSMBusAddress_c::regAPTSMBusAddress_c() : regViewer_c("APT SMBus Address", 0x25, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("SMBusAddress", static_cast<std::uint16_t>(flatp->SMBusAddress));
//    m_listFields.emplace_back("MCSMBusAddress", static_cast<std::uint16_t>(flatp->MCSMBusAddress));
//    dumpWords();
//}

//regAPTRxEnableParameters_c::regAPTRxEnableParameters_c() : regViewer_c("APT Rx Enable Parameters", 0x26, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("AlertValue", static_cast<std::uint16_t>(flatp->AlertValue));
//    m_listFields.emplace_back("InterfaceData", static_cast<std::uint16_t>(flatp->InterfaceData));
//    dumpWords();
//}

//regAPTSMBusControl_c::regAPTSMBusControl_c() : regViewer_c("APT SMBus Control", 0x27, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("SMBusFragmentSize", static_cast<std::uint16_t>(flatp->SMBusFragmentSize));
//    m_listFields.emplace_back("NotificationTimeout", static_cast<std::uint16_t>(flatp->NotificationTimeout));
//    dumpWords();
//}

//regAPTInitFlags_c::regAPTInitFlags_c() : regViewer_c("APT Init Flags", 0x28, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("ForceTCOEnable", static_cast<std::uint16_t>(flatp->ForceTCOEnable));
//    m_listFields.emplace_back("SMBARPDisabled", static_cast<std::uint16_t>(flatp->SMBARPDisabled));
//    m_listFields.emplace_back("SMBBlockReadCommand", static_cast<std::uint16_t>(flatp->SMBBlockReadCommand));
//    m_listFields.emplace_back("NotificationMethod", static_cast<std::uint16_t>(flatp->NotificationMethod));
//    dumpWords();
//}

//regAPTManagementConfiguration_c::regAPTManagementConfiguration_c() : regViewer_c("APT Management Configuration", 0x29, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("CodeSize", static_cast<std::uint16_t>(flatp->CodeSize));
//    m_listFields.emplace_back("RAMPartitioning", static_cast<std::uint16_t>(flatp->RAMPartitioning));
//    dumpWords();
//}

//regAPTuCodePointer_c::regAPTuCodePointer_c() : regViewer_c("APT uCode Pointer", 0x2A, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("Pointer", static_cast<std::uint16_t>(flatp->Pointer));
//    dumpWords();
//}

//regLeastSignificantWordOfFirmwareID_c::regLeastSignificantWordOfFirmwareID_c() : regViewer_c("Least Significant Word of Firmware ID", 0x2B, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("FirmwareID", static_cast<std::uint16_t>(flatp->FirmwareID));
//    dumpWords();
//}

//regMostSignificantWordOfFirmwareID_c::regMostSignificantWordOfFirmwareID_c() : regViewer_c("Most Significant Word of Firmware ID", 0x2C, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("FirmwareID", static_cast<std::uint16_t>(flatp->FirmwareID));
//    dumpWords();
//}

//regNC_SIManagementConfiguration_c::regNC_SIManagementConfiguration_c() : regViewer_c("NC-SI Management Configuration", 0x2D, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("CodeSize", static_cast<std::uint16_t>(flatp->CodeSize));
//    m_listFields.emplace_back("RAMPartitioning", static_cast<std::uint16_t>(flatp->RAMPartitioning));
//    dumpWords();
//}

//regNC_SIConfiguration_c::regNC_SIConfiguration_c() : regViewer_c("NC-SI Configuration", 0x2E, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("PackageID", static_cast<std::uint16_t>(flatp->PackageID));
//    m_listFields.emplace_back("uCodePointer", static_cast<std::uint16_t>(flatp->uCodePointer));
//    dumpWords();
//}

//regVPDPointer_c::regVPDPointer_c() : regViewer_c("VPD Pointer", 0x2F, 1),
//    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
//{
//    m_listFields.emplace_back("VDP", static_cast<std::uint16_t>(flatp->VDP));
//    dumpWords();
//}

//regSWSection_c::regSWSection_c() : regViewer_c("SW Section", 0x30, 15)
//{

//}

//regSoftwareChecksum_c::regSoftwareChecksum_c() : regViewer_c("Software Checksum, Words 0x00 Through 0x3F", 0x3F, 1)
//{

//}
