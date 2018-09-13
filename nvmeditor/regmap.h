#ifndef REGMAP_H
#define REGMAP_H

#include "reg.h"

class regEthernetAddress_c : public reg_c
{
public:
    regEthernetAddress_c();
    virtual ~regEthernetAddress_c(){}
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
    virtual ~regInitControl1_c(){}
};

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
    virtual ~regPCIeInitConfiguration3_c(){}
};

#endif // REGMAP_H
