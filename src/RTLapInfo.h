#ifndef RTLAPINFO_H
#define RTLAPINFO_H
#define MAXLENGTH 50 // change to 100 if no work

#include <inttypes.h>

#pragma pack(push, 1)
struct RTLapInfo
{
    uint32_t carIdentifierNumber; // Identifier number of the car
    uint32_t lapNumber; // Lap number of lap just finished
    uint16_t driverName[MAXLENGTH]; // Driver name (UTF-16LE)
    uint16_t carName[MAXLENGTH]; // Car name (UTF-16LE)
    uint32_t lapTime; // Lap time of lap just finished
};

class PacketRTLapInfo {
public:
    PacketRTLapInfo();
    virtual ~PacketRTLapInfo();
    RTLapInfo rtLapInfo;
    void push(char*receiveBuffer);
private:
    uint32_t* pointerToFirstElement();
};

#pragma pack(pop)

#endif