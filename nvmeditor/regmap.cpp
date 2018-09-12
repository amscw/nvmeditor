#include "regmap.h"

regInitControl1_c::regInitControl1_c() : reg_c("Init Control 1", 0x0A, 1)
{
}

regEthernetAddress_c::regEthernetAddress_c() : reg_c("Ethernet Address", 0x00, 3)
{
}
