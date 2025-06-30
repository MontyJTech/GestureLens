#include "GestureUtils.h"

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
	if (IsHandInPinchOpenState(hand)) {
		return GestureType::PINCH_OPEN;
	}

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
	bool middleNotOpen = IsFingerInClosedState(&hand->digits[2]);
	bool ringNotOpen = IsFingerInClosedState(&hand->digits[3]);

	return indexOpen && middleNotOpen && ringNotOpen;
}

bool GestureTypeUtils::IsHandInCurvedIndexState(LEAP_HAND* hand) {
	bool indexCurved = !IsFingerInOpenState(&hand->digits[1]) && !IsFingerInClosedState(&hand->digits[1]);
	bool middleNotOpen = !IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);


	return indexCurved && middleNotOpen && ringNotOpen;
}

bool GestureTypeUtils::IsHandInIndexMiddleState(LEAP_HAND* hand)
{
	bool indexOpen = IsFingerInOpenState(&hand->digits[1]);
	bool middleOpen = IsFingerInOpenState(&hand->digits[2]);
	bool ringClosed = IsFingerInClosedState(&hand->digits[3]);

	return indexOpen && middleOpen && ringClosed;
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

bool GestureTypeUtils::IsHandInPinchOpenState(LEAP_HAND* hand)
{
	bool indexThumbDistance = MathUtils::Distance(hand->digits[0].distal.next_joint, hand->digits[1].distal.next_joint) < THUMB_DISTANCE_THRESHOLD;
	bool middleNotClosed = !IsFingerInClosedState(&hand->digits[2]);
	bool ringNotClosed = !IsFingerInClosedState(&hand->digits[3]);
	bool pinkyNotClosed = !IsFingerInClosedState(&hand->digits[4]);

	return indexThumbDistance && middleNotClosed && ringNotClosed && pinkyNotClosed;
}

bool GestureTypeUtils::IsHandInPinchClosedState(LEAP_HAND* hand)
{
	bool indexThumbDistance = MathUtils::Distance(hand->digits[0].distal.next_joint, hand->digits[1].distal.next_joint) < THUMB_DISTANCE_THRESHOLD;
	bool middleNotOpen = !IsFingerInOpenState(&hand->digits[2]);
	bool ringNotOpen = !IsFingerInOpenState(&hand->digits[3]);
	bool pinkyNotOpen = !IsFingerInOpenState(&hand->digits[4]);

	return indexThumbDistance && middleNotOpen && ringNotOpen && pinkyNotOpen;
}

bool GestureTypeUtils::IsFingerInOpenState(LEAP_DIGIT* finger) {
	
	LEAP_VECTOR metacarpalDir = MathUtils::Direction(finger->metacarpal.prev_joint, finger->metacarpal.next_joint);
	LEAP_VECTOR fingerDir = MathUtils::Direction(finger->intermediate.prev_joint, finger->intermediate.next_joint);

	float similarity = MathUtils::CosSimilarity(metacarpalDir, fingerDir);

	return similarity > OPEN_FINGER_ANGLE_THRESHOLD;
}

bool GestureTypeUtils::IsFingerInClosedState(LEAP_DIGIT* finger) {
	LEAP_VECTOR jointOneDir;
	LEAP_VECTOR jointTwoDir;
	float similarity = 100;

	if (finger->finger_id == 0) { //is thumb - can't use metacarpal bone.
		jointOneDir = MathUtils::Direction(finger->distal.prev_joint, finger->distal.next_joint);
		jointTwoDir = MathUtils::Direction(finger->proximal.prev_joint, finger->proximal.next_joint);
		similarity = MathUtils::CosSimilarity(jointOneDir, jointTwoDir);
	}
	else {
		jointOneDir = MathUtils::Direction(finger->metacarpal.prev_joint, finger->metacarpal.next_joint);
		jointTwoDir = MathUtils::Direction(finger->intermediate.prev_joint, finger->intermediate.next_joint);
		similarity = MathUtils::CosSimilarity(jointOneDir, jointTwoDir);
	}

	return similarity < CLOSED_FINGER_ANGLE_THRESHOLD;
}

bool GestureTypeUtils::AreFingersSpread(LEAP_HAND* hand)
{
	float distanceAverage = 0;
	for (int i = 1; i < NUM_GAPS_BETWEEN_FINGERS + 1; i++) {
		distanceAverage += MathUtils::Distance(hand->digits[i].distal.next_joint, hand->digits[i + 1].distal.next_joint);
	}
	distanceAverage /= NUM_GAPS_BETWEEN_FINGERS;

	return distanceAverage > FINGER_SPREAD_DISTANCE_THRESHOLD;
}

bool GestureTypeUtils::HPalmCrossDetectedInHistory(bool isLeftSupportHand) {
	std::deque<LEAP_HAND>* support = isLeftSupportHand ? &HistoryManager::leftHand : &HistoryManager::rightHand;
	std::deque<LEAP_HAND>* dominant = isLeftSupportHand ? &HistoryManager::rightHand : &HistoryManager::leftHand;

	int counter = support->size() - 1;
	float exitPointDistance = 0;

	while (counter >= 0) {
		LEAP_HAND supportHand = support->at(counter);
		LEAP_HAND dominantHand = dominant->at(counter);

		exitPointDistance = MathUtils::Distance(dominantHand.digits[1].distal.next_joint, supportHand.digits[1].metacarpal.next_joint);

		if (exitPointDistance != 0 && exitPointDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD) {
			break;
		}
		counter--;
	}
	if (counter == -1) {
		return false;
	}

	return true;
}

bool GestureTypeUtils::JCurveDetectedInHistory(bool isLeftSupportHand)
{
	std::deque<LEAP_HAND>* support = isLeftSupportHand ? &HistoryManager::leftHand : &HistoryManager::rightHand;
	std::deque<LEAP_HAND>* dominant = isLeftSupportHand ? &HistoryManager::rightHand : &HistoryManager::leftHand;

	int counter = support->size() - 1;
	bool entryPointFound = false;

	while (counter >= 0) {
		LEAP_HAND* supportHand = &support->at(counter);
		LEAP_HAND* dominantHand = &dominant->at(counter);

		entryPointFound = MathUtils::Distance(dominantHand->digits[1].distal.next_joint, supportHand->digits[2].distal.next_joint) < GestureTypeUtils::TAP_DISTANCE_THRESHOLD;
		if (entryPointFound) {
			break;
		}
		counter--;
	}

	if (entryPointFound && counter < support->size() - 5) {
		int jArraySize = support->size() - 1 - counter;
		int jSplit = jArraySize / 2;

		std::deque<LEAP_HAND> jStraightDomSubset(dominant->end() - jSplit, dominant->end());

		LEAP_VECTOR startToMidStraightVector = MathUtils::Difference(jStraightDomSubset.front().digits[1].distal.next_joint, jStraightDomSubset.at(jStraightDomSubset.size() / 2).digits[1].distal.next_joint);
		LEAP_VECTOR midToEndStraightVector = MathUtils::Difference(jStraightDomSubset.at(jStraightDomSubset.size() / 2).digits[1].distal.next_joint, jStraightDomSubset.back().digits[1].distal.next_joint);

		if (MathUtils::CosSimilarity(startToMidStraightVector, midToEndStraightVector) > 1 - GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD) {
			std::deque<LEAP_HAND> JCurveSubset(dominant->end() - jArraySize, dominant->end() - jSplit);
			
			LEAP_VECTOR startToMidCurveVector = MathUtils::Difference(JCurveSubset.front().digits[1].distal.next_joint, JCurveSubset.at(JCurveSubset.size() / 2).digits[1].distal.next_joint);
			LEAP_VECTOR midToEndCurveVector = MathUtils::Difference(JCurveSubset.at(JCurveSubset.size() / 2).digits[1].distal.next_joint, JCurveSubset.back().digits[1].distal.next_joint);

			float similarity = MathUtils::CosSimilarity(startToMidCurveVector, midToEndCurveVector);
			return -0.5f < similarity && similarity < 0.5f;
		}
	}
	
	return false;
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
