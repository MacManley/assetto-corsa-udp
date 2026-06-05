// File: RTCarInfo.cpp
#include "RTLapInfo.h"
#include <string.h>

const int LAPINFO_BUFFER_SIZE = 212;

PacketRTLapInfo::PacketRTLapInfo()
{}

PacketRTLapInfo::~PacketRTLapInfo()
{}

void PacketRTLapInfo::push(char *receiveBuffer)
{
    memmove(pointerToFirstElement(), receiveBuffer, LAPINFO_BUFFER_SIZE);
}

uint32_t* PacketRTLapInfo::pointerToFirstElement(void)
{
    return &rtLapInfo.carIdentifierNumber;
}