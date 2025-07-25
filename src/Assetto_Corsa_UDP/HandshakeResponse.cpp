// File: HandshakeResponse.cpp
#include "HandshakeResponse.h"
#include <string.h>

const int HANDSHAKERESPONSE_BUFFER_SIZE = 408;

PacketHandshakeResponse::PacketHandshakeResponse()
{}

PacketHandshakeResponse::~PacketHandshakeResponse()
{}

void PacketHandshakeResponse::push(char *receiveBuffer)
{
    memmove(pointerToFirstElement(), receiveBuffer, HANDSHAKERESPONSE_BUFFER_SIZE);
}

uint16_t* PacketHandshakeResponse::pointerToFirstElement(void)
{
    return handshakeResponse.carName;
}