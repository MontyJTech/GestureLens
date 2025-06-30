#pragma once

#include "HistoryManager.h"
#include "GestureType.h"
#include "MathUtils.h"

#include <string>

class GestureTypeUtils {
public:
	inline static const float FINGER_SPREAD_DISTANCE_THRESHOLD = 35.f;
	inline static const float TOUCH_DISTANCE_THRESHOLD = 45.f;
	inline static const float THUMB_DISTANCE_THRESHOLD = 80.f;
	inline static const float TAP_DISTANCE_THRESHOLD = 130.f;
	inline static const float ANGLE_SIMILARITY_THRESHOLD = 0.3f; //from cosine similarity - values range from -1 to 1, perpendicularity is detected at 0 +- threshold.

	inline static const float OPEN_FINGER_ANGLE_THRESHOLD = 0.8f;
	inline static const float CLOSED_FINGER_ANGLE_THRESHOLD = -0.2f;
	inline static const float TIGHT_SPREAD_THRESHOLD = 0.0f;
	
	inline static const int NUM_GAPS_BETWEEN_FINGERS = 3;

	inline static bool secondGestureDominant = true;

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
	static bool AreFingersSpread(LEAP_HAND* hand);

	static bool HPalmCrossDetectedInHistory(bool isLeftSupportHand);
	static bool JCurveDetectedInHistory(bool isLeftSupportHand);

	static std::string GestureToString(GestureType type);
};