#include "GestureUtils.h"

const float GestureTypeUtils::OPEN_FINGER_ANGLE_THRESHOLD = 0.8f;
const float GestureTypeUtils::CLOSED_FINGER_ANGLE_THRESHOLD = -0.5f;
const float GestureTypeUtils::TIGHT_SPREAD_THRESHOLD = 0.0f;

GestureType GestureTypeUtils::GetGestureForLeapHand(LEAP_HAND* hand) {
	if (IsHandInOpenState(hand)) {
		return GestureType::OPEN;
	}
	if (IsHandInClosedState(hand)) {
		return GestureType::CLOSED;
	}
	if (IsHandInOpenIndexState(hand)) {
		return GestureType::OPEN_INDEX;
	}
	if (IsHandInCurvedIndexState(hand)) {
		return GestureType::CURVED_INDEX;
	}
	if (IsHandInIndexMiddleState(hand)) {
		return GestureType::INDEX_MIDDLE;
	}
	if (IsHandInIndexMiddleRingState(hand)) {
		return GestureType::INDEX_MIDDLE_RING;
	}
	if (IsHandInPinkyState(hand)) {
		return GestureType::PINKY;
	}

	//pinch ones missing. ------------------------------------------------------------------------- TODO

	return GestureType::NONE;
}

bool GestureTypeUtils::IsHandInOpenState(LEAP_HAND* hand) {
	bool indexOpen = IsFingerInOpenState(&hand->digits[1]);
	bool middleOpen = IsFingerInOpenState(&hand->digits[2]);
	bool ringOpen = IsFingerInOpenState(&hand->digits[3]);
	bool pinkyOpen = IsFingerInOpenState(&hand->digits[4]);

	return indexOpen && middleOpen && ringOpen && pinkyOpen;
}

bool GestureTypeUtils::IsHandInClosedState(LEAP_HAND* hand)
{
	bool indexClosed = IsFingerInClosedState(&hand->digits[1]);
	bool middleClosed = IsFingerInClosedState(&hand->digits[2]);
	bool ringClosed = IsFingerInClosedState(&hand->digits[3]);
	bool pinkyClosed = IsFingerInClosedState(&hand->digits[4]);

	return indexClosed && middleClosed && ringClosed && pinkyClosed;
}

bool GestureTypeUtils::IsHandInOpenIndexState(LEAP_HAND* hand) {
	bool indexOpen = IsFingerInOpenState(&hand->digits[1]);
	bool middleNotOpen = !IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotOpen = !IsFingerInOpenState(&hand->digits[4]);

	return indexOpen && middleNotOpen && ringNotOpen && pinkyNotOpen;
}

bool GestureTypeUtils::IsHandInCurvedIndexState(LEAP_HAND* hand) {
	bool indexCurved = !IsFingerInOpenState(&hand->digits[1]) && !IsFingerInClosedState(&hand->digits[1]);
	bool middleNotOpen = !IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotOpen = !IsFingerInOpenState(&hand->digits[4]);

	return indexCurved && middleNotOpen && ringNotOpen && pinkyNotOpen;
}

bool GestureTypeUtils::IsHandInIndexMiddleState(LEAP_HAND* hand)
{
	bool indexOpen = IsFingerInOpenState(&hand->digits[1]);
	bool middleOpen = IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotOpen = !IsFingerInOpenState(&hand->digits[4]);

	return indexOpen && middleOpen && ringNotOpen && pinkyNotOpen;
}

bool GestureTypeUtils::IsHandInIndexMiddleRingState(LEAP_HAND* hand)
{
	bool indexOpen = IsFingerInOpenState(&hand->digits[1]);
	bool middleOpen = IsFingerInOpenState(&hand->digits[2]);
	bool ringOpen = IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotOpen = !IsFingerInOpenState(&hand->digits[4]);

	return indexOpen && middleOpen && ringOpen && pinkyNotOpen;
}

bool GestureTypeUtils::IsHandInPinkyState(LEAP_HAND* hand)
{
	bool indexNotOpen = !IsFingerInOpenState(&hand->digits[1]);
	bool middleNotOpen = !IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotClosed = !IsFingerInClosedState(&hand->digits[4]);

	return indexNotOpen && middleNotOpen && ringNotOpen && pinkyNotClosed;
}

bool GestureTypeUtils::IsFingerInOpenState(LEAP_DIGIT* finger) {
	
	LEAP_VECTOR metacarpalDir = MathUtils::Direction(finger->metacarpal.prev_joint, finger->metacarpal.next_joint);
	LEAP_VECTOR fingerDir = MathUtils::Direction(finger->intermediate.prev_joint, finger->intermediate.next_joint);

	float similarity = MathUtils::CosSimilarity(metacarpalDir, fingerDir);

	return similarity > OPEN_FINGER_ANGLE_THRESHOLD;
}

bool GestureTypeUtils::IsFingerInClosedState(LEAP_DIGIT* finger) {
	LEAP_VECTOR metacarpalDir = MathUtils::Direction(finger->metacarpal.prev_joint, finger->metacarpal.next_joint);
	LEAP_VECTOR fingerDir = MathUtils::Direction(finger->intermediate.prev_joint, finger->intermediate.next_joint);

	float similarity = MathUtils::CosSimilarity(metacarpalDir, fingerDir);

	return similarity < CLOSED_FINGER_ANGLE_THRESHOLD;
}

std::string GestureTypeUtils::GestureToString(GestureType type) {
	switch (type) {
		case GestureType::OPEN:
			return "OPEN";
		case GestureType::PINCH_OPEN:
			return "PINCH_OPEN";
		case GestureType::PINCH_CLOSED:
			return "PINCH_CLOSED";
		case GestureType::CLOSED:
			return "CLOSED";
		case GestureType::OPEN_INDEX:
			return "OPEN_INDEX";
		case GestureType::CURVED_INDEX:
			return "CURVED_INDEX";
		case GestureType::INDEX_MIDDLE:
			return "INDEX_MIDDLE";
		case GestureType::INDEX_MIDDLE_RING:
			return "INDEX_MIDDLE_RING";
		case GestureType::PINKY:
			return "PINKY";
		case GestureType::NONE:
		default:
			return "NONE";
	}
}
