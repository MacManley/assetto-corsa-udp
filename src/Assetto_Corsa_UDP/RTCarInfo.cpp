// File: RTCarInfo.cpp
#include "RTCarInfo.h"
#include <string.h>

const int CARINFO_BUFFER_SIZE = 328;

PacketRTCarInfo::PacketRTCarInfo()
{}

PacketRTCarInfo::~PacketRTCarInfo()
{}

void PacketRTCarInfo::push(char *receiveBuffer)
{
    memmove(pointerToFirstElement(), receiveBuffer, CARINFO_BUFFER_SIZE);
}

char* PacketRTCarInfo::pointerToFirstElement(void)
{
    return &rtCarInfo.identifier[0];
}