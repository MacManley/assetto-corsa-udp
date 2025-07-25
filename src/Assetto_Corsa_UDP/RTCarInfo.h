#ifndef RTCARINFO_H
#define RTCARINFO_H

#include <inttypes.h>

#pragma pack(push, 1)

struct RTCarInfo
{
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

class PacketRTCarInfo {
public:
    PacketRTCarInfo();
    virtual ~PacketRTCarInfo();
	RTCarInfo rtCarInfo;
    void push(char*receiveBuffer);
private:
    char* pointerToFirstElement();
};

#pragma pack(pop)

#endif