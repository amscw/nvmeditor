#include "regmap.h"


regInitControl1_c::regInitControl1_c() : regViewer_c("Init Control 1", 0x0A, 1),
    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
{
    m_mapFields.emplace("FRCSPD", static_cast<std::uint16_t>(flatp->FRCSPD));
    m_mapFields.emplace("FD", static_cast<std::uint16_t>(flatp->FD));
    m_mapFields.emplace("ILOS", static_cast<std::uint16_t>(flatp->ILOS));
    m_mapFields.emplace("LoadSubsystemIDs", static_cast<std::uint16_t>(flatp->LoadSubsystemIDs));
    m_mapFields.emplace("LoadDeviceID", static_cast<std::uint16_t>(flatp->LoadDeviceID));
    dumpWords();
}

regEthernetAddress_c::regEthernetAddress_c() : reg_c("Ethernet Address", 0x00, 3)
{
}

regPCIeInitConfiguration3_c::regPCIeInitConfiguration3_c() : regViewer_c("PCIe Init Configuration 3", 0x1A, 1),
    flatp(reinterpret_cast<flatp_t>(&(*m_itBase)))
{
    m_mapFields.emplace("Master_Enable", static_cast<std::uint16_t>(flatp->Master_Enable));
    m_mapFields.emplace("Scram_dis", static_cast<std::uint16_t>(flatp->Scram_dis));
    m_mapFields.emplace("Ack_Nak_Sch", static_cast<std::uint16_t>(flatp->Ack_Nak_Sch));
    m_mapFields.emplace("Cache_Lsize", static_cast<std::uint16_t>(flatp->Cache_Lsize));
    m_mapFields.emplace("PCIE_Cap", static_cast<std::uint16_t>(flatp->PCIE_Cap));
    m_mapFields.emplace("IO_Sup", static_cast<std::uint16_t>(flatp->IO_Sup));
    m_mapFields.emplace("Packet_Size", static_cast<std::uint16_t>(flatp->Packet_Size));
    m_mapFields.emplace("Act_Stat_PM_Sup", static_cast<std::uint16_t>(flatp->Act_Stat_PM_Sup));
    m_mapFields.emplace("Slot_Clock_Cfg", static_cast<std::uint16_t>(flatp->Slot_Clock_Cfg));
    m_mapFields.emplace("LoopbackPolarityInversion", static_cast<std::uint16_t>(flatp->LoopbackPolarityInversion));
    dumpWords();
}
