#pragma once

#include "GestureType.h"
#include "LeapC.h"
#include "MathUtils.h"
#include "FingerSpread.h"

#include <string>
#include <iostream>

//Finger indexes for reference: 
//0: thumb, 1: index, 2: middle, 3:ring, 4: pinky
class GestureTypeUtils {
public:
	//Uses cosine similarity - 1 is perfectly in-line, -1 is exact opposite direction
	static const float OPEN_FINGER_ANGLE_THRESHOLD;
	static const float CLOSED_FINGER_ANGLE_THRESHOLD;

	static const float TIGHT_SPREAD_THRESHOLD;

	static GestureType GetGestureForLeapHand(LEAP_HAND* hand);

	static bool IsHandInOpenState(LEAP_HAND* hand);
	static bool IsHandInClosedState(LEAP_HAND* hand);
	
	static bool IsHandInOpenIndexState(LEAP_HAND* hand);
	static bool IsHandInCurvedIndexState(LEAP_HAND* hand);

	static bool IsHandInIndexMiddleState(LEAP_HAND* hand);
	static bool IsHandInIndexMiddleRingState(LEAP_HAND* hand);
	static bool IsHandInPinkyState(LEAP_HAND* hand);

	static bool IsHandInPinchOpenState(LEAP_HAND* hand);
	static bool IsHandInPinchClosedState(LEAP_HAND* hand);

	static bool IsFingerInOpenState(LEAP_DIGIT* finger);
	static bool IsFingerInClosedState(LEAP_DIGIT* finger);

	static std::string GestureToString(GestureType type);
};