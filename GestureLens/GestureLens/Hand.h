#pragma once
#include "GestureType.h"
#include <LeapC.h>

class Hand {
public:
	Hand(LEAP_HAND l_hand);

private:
	GestureType gesture = GestureType::NONE;

	GestureType GetGestureFromDetectedHand(LEAP_HAND l_hand);
};