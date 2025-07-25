// File: AC_UDP.h
#ifndef AC_UDP_H
#define AC_UDP_H

#include "HandshakeResponse.h"
#include <WiFiUdp.h>
#include "RTCarInfo.h"
#include "RTLapInfo.h"

struct HandshakeMessage {
    int identifier;
    int version;
    int operationID;
};

class AC_Parser
{
public:
    AC_Parser();
    virtual ~AC_Parser();
    void begin(const IPAddress acServerIP);
    void read(void);
    void performHandshake(int handshakeType);
    PacketHandshakeResponse* packetHandshakeResponse(void);
    PacketRTCarInfo* packetRTCarInfo(void);
    PacketRTLapInfo* packetRTLapInfo(void);

private:
    void push(char * receiveBuffer, int packetSize);
    PacketHandshakeResponse* packetHandshakeResponse_;
    PacketRTCarInfo* packetRTCarInfo_;
    PacketRTLapInfo* packetRTLapInfo_;
    IPAddress remoteIP;
    WiFiUDP Udp;
    //fill in rest
};

#endif

