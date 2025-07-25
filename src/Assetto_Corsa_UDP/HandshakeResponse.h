#ifndef HANDSHAKERESPONSE_H
#define HANDSHAKERESPONSE_H
#define MAXLENGTH 50 // change to 100 if no work

#include <inttypes.h>

#pragma pack(push, 1)

struct HandshakeResponse {
    uint16_t carName[MAXLENGTH]; // Name of the car (UTF-16LE)
    uint16_t driverName[MAXLENGTH]; // Username of the driver (UTF-16LE)
    uint32_t identifier; // Status 
    uint32_t version; // Packet version
    uint16_t trackName[MAXLENGTH]; // Name of the track (UTF-16LE)
    uint16_t trackConfig[MAXLENGTH]; // Track configuration (UTF-16LE)
};

class PacketHandshakeResponse {
public:
    PacketHandshakeResponse();
    virtual ~PacketHandshakeResponse();
    HandshakeResponse handshakeResponse;
    void push(char*receiveBuffer);
private:
    uint16_t* pointerToFirstElement();
};

#pragma pack(pop)

#endif