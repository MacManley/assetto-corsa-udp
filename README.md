# Assetto Corsa UDP | Library for use on ESP 32 / ESP8266 devices
**Data Output from the Assetto Corsa**

> Note: UDP telemetry differs between PC and Console versions of Assetto Corsa, therefore this library is tested and trialed on console editions of the game.

This program captures and parses packets that are sent by UDP from the Assetto Corsa game on Playstation/Xbox. This library is written specifically for usage on the ESP32 and ESP8266.

# Usage:
```c++
#include "AC_UDP.h"
AC_Parser acParser;
IPAddress playstationIP;
char packetType;

void setup()
{
    acParser.begin(playstationIP, packetType);
}

void loop()
{
    packetContent = gt7Telem.read();
}
```

### Initialising Handshake

In order to receive data from the game via UDP, handshakes need to be sent from the board to intialise communication. The game expects an initial handshake, alongside a secondary handshake to confirm whether the user wants to subscribe to car or lap info.

## Handshake Structure

The handshake is comprised of three components. 

Size: 12 bytes

Frequency: Once to initialize a specific communication

```c++
struct handshake {
uint32_t identifier; // iPhone = 0, iPad = 1, androidPhone = 2, androidTablet = 3
uint32_t version; // The telemetry version the device expects to speak with (default is 1)
uint32_t operationID; // Type of operation needed from the game 
}
```

The operation ID is needed to access specific data from the game and is a core part of the handshake. Each ID corresponds to a specific function

| ID   | Operation | Description |
| - | ---------- | ----------- |
| 0  | HANDSHAKE  | Begin communication |
| 1 | UPDATE | Receive car info |
| 2 | SPOT | Receive lap info |
| 3  | DISMISS | Cease communication |

### Packet Types

The following data types are used in the structure:

| Type   | Description             |
| ------ | ----------------------- |
| uint8  | Unsigned 8-bit integer  |
| uint16 | Unsigned 16-bit integer |
| uint32 | Unsigned 32-bit integer |
| float  | Floating point (32-bit) |

The 3 different types of packets are emitted depending on the operationID sent.

| OperationID | Packet Type | Occurs |
| - | ----------------------- | ------------- |
| 0 | Handshake | On initial handshake |
| 1 | Car Info  | When subscribed to update |
| 2 | Lap Info  | When subscribed to spot |

## Handshake:

The handshake features base information such as the current track and car name.

Size: 408 bytes

Frequency: 60Hz (not available in Sport Mode)

```c++
//...
struct HandshakeResponse {
uint16_t carName[MAXLENGTH]; // Name of the car (UTF-16LE)
uint16_t driverName[MAXLENGTH]; // Username of the driver (UTF-16LE)
uint32_t identifier; // Status 
uint32_t version; // Packet version
uint16_t trackName[MAXLENGTH]; // Name of the track (UTF-16LE)
uint16_t trackConfig[MAXLENGTH]; // Track configuration (UTF-16LE)
};
```

## Car Info: 

This packet details various telemetry points such as car coordinates, speed, car flags and more.

Size: 328 bytes

Frequency: 60Hz

```c++
struct RTCarInfo {
char identifier[4]; // Data type
uint32_t size; // Size of structured data
float speedKmh; // Speed in km/h
float speedMph; // Speed in miles per hour
float speedMs; // Speed in m/s
uint8_t isAbsEnabled; // ABS turned on flag
uint8_t isAbsInAction; // ABS active flag
uint8_t isTcInAction; // TCS active flag
uint8_t isTcEnabled; // TCS turned on flag
uint8_t isInPit; // In pit flag
uint8_t isEngineLimiterOn; // Engine rev limiter on flag
uint8_t unknownByteA; // Unknown byte flag A
uint8_t unknownByteB; // Unknown byte flag B
float heave; // G force vertical
float sway; // G force horizontally
float surge; // G force front-back
uint32_t lapTime; // Lap time
uint32_t lastLap; // Lap time previous lap
uint32_t bestLap; // Fastest lap time
uint32_t lapCount; // Amount of laps passed
float throttle; // Throttle 
float brake; // Brake
float clutch; // Clutch
float engineRPM; // RPM of the engine
float steer; // Steering angle in degrees
uint32_t gear; // Gear, where reverse is 0, neutral is 1, first is 2, second is 3 etc...
float cgHeight; // Center of gravity height in meters
float wheelAngularSpeed[4]; // Angular speed of all 4 wheels in RPM (FL -> FR -> RL -> RR)
float slipAngle[4]; // Slip angle for all tyres (FL -> FR -> RL -> RR)
float slipAngleContactPatch[4]; // Slip angle contact patch for all 4 tyres (FL -> FR -> RL -> RR)
float slipRatio[4]; // Slip ratio for all 4 tyres (FL -> FR -> RL -> RR)
float tyreSlip[4]; // Tyre slip for all 4 tyres (FL -> FR -> RL -> RR)
float ndSlip[4]; // Normalized dynamic slip for all 4 tyres (FL -> FR -> RL -> RR)
float verticalLoad[4]; // Vertical load on all four tyres (FL -> FR -> RL -> RR)
float lateralLoad[4]; // Lateral load on all four tyres (FL -> FR -> RL -> RR)
float selfAligningTorque[4]; // Self aligning torque (FL -> FR -> RL -> RR)
float tyreDirtyLevel[4]; // Amount of dirt on tyres (maxes out at 5) (FL -> FR -> RL -> RR)
float camber[4]; // Camber in radians
float tyreRadius[4]; // Radius of tyres in meters
float tyreLoadedRadius[4]; // Loaded tyre radius in meters
float suspensionHeight[4]; // Suspension height in meters
float carPositionNormalized; // How much the car has completed the circuit (0 is none, 1 is finished)
float carSlope; // Slope of car relative to road
float carCoordinates[3]; // Coordinates of car in the world
};
```

## Lap Info:

This packet includes lap time data for every car in the session.

Size: 212 Bytes

Frequency: End of each lap

```c++
//...
struct RTLapInfo {
    uint32_t carIdentifierNumber; // Identifier number of the car
    uint32_t lapNumber; // Lap number of lap just finished
    uint16_t driverName[MAXLENGTH]; // Driver name (UTF-16LE)
    uint16_t carName[MAXLENGTH]; // Car name (UTF-16LE)
    uint32_t lapTime; // Lap time of lap just finished
};
```
