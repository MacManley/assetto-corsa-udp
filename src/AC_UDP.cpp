// File: PCars2_UDP.cpp
#include <stdio.h>
#include <WiFiUdp.h>
#include "AC_UDP.h"
#include "HandshakeResponse.h"
#include "RTCarInfo.h"
#include "RTLapInfo.h"

constexpr int remotePort = 9996;

AC_Parser::AC_Parser()
{
    packetHandshakeResponse_ = new PacketHandshakeResponse();
    packetRTCarInfo_ = new PacketRTCarInfo();
    packetRTLapInfo_ = new PacketRTLapInfo(); 
}

AC_Parser::~AC_Parser()
{
    delete packetHandshakeResponse_;
    delete packetRTCarInfo_;
    delete packetRTLapInfo_;
    
}

void AC_Parser::begin(const IPAddress playstationIP) {
    Udp.begin(remotePort);
    remoteIP = playstationIP;
    performHandshake(0);
}

void AC_Parser::performHandshake(int handshakeType) {
    HandshakeMessage handshake;

    if (handshakeType < 4 && handshakeType >= 0) {

        handshake.identifier = 1;
        handshake.version = 1;
        handshake.operationID = handshakeType;

        Udp.beginPacket(remoteIP, remotePort);
        Udp.write((uint8_t *)&handshake, sizeof(handshake));
        Udp.endPacket();
    }
}

void AC_Parser::read(void) {
    int packetSize = Udp.parsePacket();
    if (packetSize) {
        char packetBuffer[packetSize];
        while (Udp.available()) {
            Udp.read(packetBuffer, packetSize);
        }
        push(packetBuffer, packetSize);
    }
}

void AC_Parser::push(char * receiveBuffer, int packetSize)
{
    switch(packetSize) 
    {
        case 408: packetHandshakeResponse_->push(receiveBuffer);
            break;
        case 328: packetRTCarInfo_->push(receiveBuffer);
            break;
        case 212: packetRTLapInfo_->push(receiveBuffer);
            break;
        default:; // blow up or sum idk
    }
    
}

PacketHandshakeResponse* AC_Parser::packetHandshakeResponse(void)
{
    return packetHandshakeResponse_;
}

PacketRTCarInfo* AC_Parser::packetRTCarInfo(void)
{
    return packetRTCarInfo_;
}

PacketRTLapInfo* AC_Parser::packetRTLapInfo(void)
{
    return packetRTLapInfo_;
}