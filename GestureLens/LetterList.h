#pragma once
#include "Letter.h"

//To note: There are some references to "dominant" hands. Since I'm right-handed, these Letter objects were initialized with the 'dominant' being the second gesture.
//In order to be right/ left agnostic, the 'Letter' class will differentiate dominant gesture vs the support by always comparing to 'second' gesture references (requiredGestureTwo, secondGestureDominant etc.).

//Conventions:
// palmNormalsOpposing (Perpendicular, Aligned)
// palmDirectionsOpposing (Perpendicular, Aligned)

class LetterList {
public:
	inline static const Letter A = Letter('a', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < 0;

		if (GestureTypeUtils::AreFingersSpread(support) && palmNormalsOpposing) {
			float thumbIndexDistance = GestureTypeUtils::secondGestureDominant ?
				MathUtils::Distance(h1->digits[0].distal.next_joint, h2->digits[1].distal.next_joint) :
				MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[0].distal.next_joint);

				return thumbIndexDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return false;
	});

	inline static const Letter B = Letter('b', GestureType::CURVED_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1 + MathUtils::PERPENDICULARITY_THRESHOLD;
		bool h1Pinching = MathUtils::Distance(h1->digits[0].distal.next_joint, h1->digits[1].distal.next_joint) < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD;
		bool h2Pinching = MathUtils::Distance(h2->digits[0].distal.next_joint, h2->digits[1].distal.next_joint) < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD;

		bool distancesMatch =
			MathUtils::Distance(h1->digits[0].distal.next_joint, h2->digits[1].distal.next_joint) < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD &&
			MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[0].distal.next_joint) < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD; 

		return palmNormalsOpposing && distancesMatch;
	});

	inline static const Letter C = Letter('c', GestureType::NONE, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant = GestureTypeUtils::secondGestureDominant ? h2 : h1;
		
		bool thumbOpen = !GestureTypeUtils::IsFingerInClosedState(&dominant->digits[0]);
		bool oneHandVisible = (h1 == nullptr || h2 == nullptr);
		bool fingersSeparate = MathUtils::Distance(dominant->digits[1].distal.next_joint, dominant->digits[0].distal.next_joint) > GestureTypeUtils::THUMB_DISTANCE_THRESHOLD;

		return thumbOpen && oneHandVisible && fingersSeparate;
	});

	inline static const Letter D = Letter('d', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool thumbOpen = false;
		bool indexTouching = false;
		bool thumbIndexBaseTouching = false;

		if (GestureTypeUtils::secondGestureDominant) {
			thumbOpen = !GestureTypeUtils::IsFingerInClosedState(&h2->digits[0]);
			indexTouching = MathUtils::Distance(h2->digits[1].distal.next_joint, h1->digits[1].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
			thumbIndexBaseTouching = MathUtils::Distance(h2->digits[0].distal.next_joint, h1->digits[1].metacarpal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}
		else {
			thumbOpen = !GestureTypeUtils::IsFingerInClosedState(&h1->digits[0]);
			indexTouching = MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[1].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
			thumbIndexBaseTouching = MathUtils::Distance(h1->digits[0].distal.next_joint, h2->digits[1].metacarpal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return thumbOpen && indexTouching && thumbIndexBaseTouching;
	});

	inline static const Letter E = Letter('e', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		if (GestureTypeUtils::AreFingersSpread(support)) {
			float indexIndexDistance = MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[1].distal.next_joint);

			return indexIndexDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return false;
	});

	inline static const Letter F = Letter('f', GestureType::INDEX_MIDDLE, GestureType::INDEX_MIDDLE, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_VECTOR directionH1 = MathUtils::Direction(h1->digits[1].metacarpal.prev_joint, h1->digits[1].distal.next_joint);
		LEAP_VECTOR directionH2 = MathUtils::Direction(h2->digits[1].metacarpal.prev_joint, h2->digits[1].distal.next_joint);

		bool fingersPerpendicular = MathUtils::VectorsPerpendicular(directionH1, directionH2);

		LEAP_VECTOR centrePointH1 = MathUtils::Midpoint(h1->digits[1].proximal.next_joint, h1->digits[2].proximal.next_joint);
		LEAP_VECTOR centrePointH2 = MathUtils::Midpoint(h2->digits[1].proximal.next_joint, h2->digits[2].proximal.next_joint);

		bool centresClose = MathUtils::Distance(centrePointH1, centrePointH2) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return fingersPerpendicular && centresClose;
	});

	inline static const Letter G = Letter('g', GestureType::CLOSED, GestureType::CLOSED, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsAligned = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) > 1 - GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD;

		float handTapDistanceOne = MathUtils::Distance(h1->digits[1].metacarpal.prev_joint, h2->digits[4].metacarpal.prev_joint);
		float handTapDistanceTwo = MathUtils::Distance(h2->digits[1].metacarpal.prev_joint, h1->digits[4].metacarpal.prev_joint);

		bool handsStackedOne = handTapDistanceOne < GestureTypeUtils::TAP_DISTANCE_THRESHOLD;
		bool handsStackedTwo = handTapDistanceTwo < GestureTypeUtils::TAP_DISTANCE_THRESHOLD;

		return palmNormalsAligned && (handsStackedOne || handsStackedTwo);
	});

	inline static const Letter H = Letter('h', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* leftHand = h1->type == eLeapHandType_Left ? h1 : h2;
		LEAP_HAND* rightHand = h1->type == eLeapHandType_Left ? h2 : h1;

		bool isLeftSupport = MathUtils::CosSimilarity(leftHand->palm.normal, MathUtils::UP) > 0;

		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1.f + GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD;
		bool palmDirectionsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.direction, h2->palm.direction);
		bool middleIndexEntryPoint = GestureTypeUtils::secondGestureDominant ?
			MathUtils::Distance(h2->digits[1].distal.next_joint, h1->digits[2].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD:
			MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[2].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		if (palmNormalsOpposing && palmDirectionsPerpendicular && middleIndexEntryPoint) {
			return GestureTypeUtils::HPalmCrossDetectedInHistory(isLeftSupport);
		}
		else {
			return false;
		}
	});

	inline static const Letter I = Letter('i', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		if (GestureTypeUtils::AreFingersSpread(support)) {
			float middleIndexDistance = GestureTypeUtils::secondGestureDominant ?
				MathUtils::Distance(h1->digits[2].distal.next_joint, h2->digits[1].distal.next_joint) :
				MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[2].distal.next_joint);

			return middleIndexDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return false;
	});

	inline static const Letter J = Letter('j', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool isLeftHandDominant = false;
		LEAP_HAND* leftHand = h1->type == eLeapHandType_Left ? h1 : h2;
		LEAP_HAND* rightHand = h1->type == eLeapHandType_Left ? h2 : h1;
		LEAP_HAND* dominant;
		LEAP_HAND* support;

		if (GestureTypeUtils::secondGestureDominant) {
			support = h1;
			dominant = h2;
		}
		else {
			isLeftHandDominant = true;
			support = h2;
			dominant = h1;
		}

		LEAP_VECTOR exitPointOptionOne = support->digits[0].proximal.next_joint;
		LEAP_VECTOR exitPointOptionTwo = MathUtils::Midpoint(support->digits[0].proximal.next_joint, support->digits[1].metacarpal.next_joint);
		LEAP_VECTOR exitPointOptionThree = support->palm.position;

		float distanceOptionTwo = MathUtils::Distance(exitPointOptionOne, dominant->digits[1].distal.next_joint);
		float distanceOptionOne = MathUtils::Distance(exitPointOptionTwo, dominant->digits[1].distal.next_joint);
		float distanceOptionThree = MathUtils::Distance(exitPointOptionThree, dominant->digits[1].distal.next_joint);
		 
		if (distanceOptionOne < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD || 
			distanceOptionTwo < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD ||
			distanceOptionThree < GestureTypeUtils::TAP_DISTANCE_THRESHOLD) {
			return GestureTypeUtils::JCurveDetectedInHistory(isLeftHandDominant);
		}

		return false;
	});

	inline static const Letter K = Letter('k', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.normal, h2->palm.normal);
		bool proximalDistanceWithinThreshold = MathUtils::Distance(h1->digits[1].proximal.next_joint, h2->digits[1].proximal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmNormalsPerpendicular && proximalDistanceWithinThreshold;
	});

	inline static const Letter L = Letter('l', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant = GestureTypeUtils::secondGestureDominant ? h2 : h1;
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		if (GestureTypeUtils::AreFingersSpread(support)) {
			bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1 + MathUtils::PERPENDICULARITY_THRESHOLD;
			bool touchPointMet = MathUtils::Distance(support->palm.position, dominant->digits[1].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
			
			return palmNormalsOpposing && touchPointMet;
		}

		return false;
	});

	inline static const Letter M = Letter('m', GestureType::OPEN, GestureType::INDEX_MIDDLE_RING, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant;
		LEAP_HAND* support;

		if (GestureTypeUtils::secondGestureDominant) {
			support = h1;
			dominant = h2;
		}
		else {
			support = h2;
			dominant = h1;
		}

		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1.f + GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD;
		
		bool IMFingersClosed = MathUtils::Distance(dominant->digits[1].distal.next_joint, dominant->digits[2].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		bool MRFingersClosed = MathUtils::Distance(dominant->digits[2].distal.next_joint, dominant->digits[3].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		bool tapRegistered = MathUtils::Distance(dominant->digits[2].distal.next_joint, support->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmNormalsOpposing && IMFingersClosed && MRFingersClosed && tapRegistered;
	});

	inline static const Letter N = Letter('n', GestureType::OPEN, GestureType::INDEX_MIDDLE, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant;
		LEAP_HAND* support;

		if (GestureTypeUtils::secondGestureDominant) {
			support = h1;
			dominant = h2;
		}
		else {
			support = h2;
			dominant = h1;
		}

		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1.f + GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD;
		bool fingersClosed = MathUtils::Distance(dominant->digits[1].distal.next_joint, dominant->digits[2].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		bool tapRegistered = MathUtils::Distance(dominant->digits[2].distal.next_joint, support->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmNormalsOpposing && fingersClosed && tapRegistered;
	});

	inline static const Letter O = Letter('o', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		if (GestureTypeUtils::AreFingersSpread(support)) {
			float ringIndexDistance = GestureTypeUtils::secondGestureDominant ?
				MathUtils::Distance(h1->digits[3].distal.next_joint, h2->digits[1].distal.next_joint) :
				MathUtils::Distance(h1->digits[1].distal.next_joint, h2->digits[3].distal.next_joint);

			return ringIndexDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return false;
	});

	inline static const Letter P = Letter('p', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant = GestureTypeUtils::secondGestureDominant ? h2 : h1;
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		bool dominantPinching = MathUtils::Distance(dominant->digits[0].distal.next_joint, dominant->digits[1].distal.next_joint) < GestureTypeUtils::THUMB_DISTANCE_THRESHOLD;
		bool indexTouching = MathUtils::Distance(support->digits[1].distal.next_joint, dominant->digits[1].distal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return dominantPinching && indexTouching;
	});

	inline static const Letter Q = Letter('q', GestureType::PINCH_OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.normal, h2->palm.normal);

		bool qShapeFound = GestureTypeUtils::secondGestureDominant ?
			MathUtils::Distance(h2->digits[1].distal.prev_joint, h1->digits[0].distal.prev_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD :
			MathUtils::Distance(h1->digits[1].distal.prev_joint, h2->digits[0].distal.prev_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmNormalsPerpendicular && qShapeFound;
	});

	inline static const Letter R = Letter('r', GestureType::OPEN, GestureType::CURVED_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.normal, h2->palm.normal);
		
		bool hookShapeFound = GestureTypeUtils::secondGestureDominant ?
			(
				MathUtils::Distance(h2->digits[1].distal.prev_joint, h1->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD &&
				MathUtils::Distance(h2->digits[1].proximal.next_joint, h1->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD
			) :
			(
				MathUtils::Distance(h1->digits[1].distal.prev_joint, h2->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD&&
				MathUtils::Distance(h1->digits[1].proximal.next_joint, h2->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD
			);

		return palmNormalsPerpendicular && hookShapeFound;
	});

	inline static const Letter S = Letter('s', GestureType::PINKY, GestureType::PINKY, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmNormalsOpposing = MathUtils::CosSimilarity(h1->palm.normal, h2->palm.normal) < -1 + MathUtils::PERPENDICULARITY_THRESHOLD;
		bool pinkyLink = MathUtils::Distance(h1->digits[4].proximal.next_joint, h2->digits[4].proximal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmNormalsOpposing && pinkyLink;
	});

	inline static const Letter T = Letter('t', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_VECTOR pinkyMidPoint;
		LEAP_VECTOR indexPosition;
		LEAP_VECTOR supportPalmCentre;

		if (GestureTypeUtils::secondGestureDominant) {
			pinkyMidPoint = MathUtils::Midpoint(h1->digits[4].metacarpal.prev_joint, h1->digits[4].metacarpal.next_joint);
			indexPosition = h2->digits[1].distal.next_joint;
			supportPalmCentre = h1->palm.position;
		}
		else {
			pinkyMidPoint = MathUtils::Midpoint(h2->digits[4].metacarpal.prev_joint, h2->digits[4].metacarpal.next_joint);
			indexPosition = h1->digits[1].distal.next_joint;
			supportPalmCentre = h2->palm.position;
		}

		bool closeToPalmEdgeMidpoint = MathUtils::Distance(indexPosition, pinkyMidPoint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		bool closeToPalmMidpoint = MathUtils::Distance(indexPosition, supportPalmCentre) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return closeToPalmEdgeMidpoint && !closeToPalmMidpoint;
	});

	inline static const Letter U = Letter('u', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;
		LEAP_HAND* dominant = GestureTypeUtils::secondGestureDominant ? h2 : h1;

		if (GestureTypeUtils::AreFingersSpread(support)) {
			float pinkyIndexDistance = MathUtils::Distance(dominant->digits[1].distal.next_joint, support->digits[4].distal.next_joint);

			return pinkyIndexDistance < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		}

		return false;
	});

	inline static const Letter V = Letter('v', GestureType::OPEN, GestureType::INDEX_MIDDLE, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant;
		LEAP_HAND* support;

		if (GestureTypeUtils::secondGestureDominant) {
			support = h1;
			dominant = h2;
		}
		else {
			support = h2;
			dominant = h1;
		}

		bool fingersOpen = MathUtils::Distance(dominant->digits[1].distal.next_joint, dominant->digits[2].distal.next_joint) > GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;
		bool tapRegistered = MathUtils::Distance(MathUtils::Midpoint(dominant->digits[1].distal.next_joint, dominant->digits[2].distal.next_joint), support->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return fingersOpen && tapRegistered;
	});

	inline static const Letter W = Letter('w', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* topHand;
		LEAP_HAND* bottomHand;
		if (h1->digits[1].proximal.next_joint.y < h2->digits[1].proximal.next_joint.y) {
			topHand = h1;
			bottomHand = h2;
		}
		else {
			topHand = h2;
			bottomHand = h1;
		}

		LEAP_VECTOR indexMiddleCentre = MathUtils::Midpoint(topHand->digits[1].proximal.next_joint, topHand->digits[2].proximal.next_joint);
		LEAP_VECTOR middleRingCentre = MathUtils::Midpoint(topHand->digits[2].proximal.next_joint, topHand->digits[3].proximal.next_joint);

		bool interlocked = MathUtils::Distance(indexMiddleCentre, bottomHand->digits[1].proximal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD &&
			MathUtils::Distance(middleRingCentre, bottomHand->digits[2].proximal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		bool palmsNormalsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.normal, h2->palm.normal);

		return palmsNormalsPerpendicular && interlocked;
	});

	inline static const Letter X = Letter('x', GestureType::OPEN_INDEX, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_VECTOR directionH1 = MathUtils::Direction(h1->digits[1].metacarpal.prev_joint, h1->digits[1].distal.next_joint);
		LEAP_VECTOR directionH2 = MathUtils::Direction(h2->digits[1].metacarpal.prev_joint, h2->digits[1].distal.next_joint);

		bool fingersPerpendicular = MathUtils::VectorsPerpendicular(directionH1, directionH2);
		bool centresClose = MathUtils::Distance(h1->digits[1].proximal.next_joint, h2->digits[1].proximal.next_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return fingersPerpendicular && centresClose;
	});

	inline static const Letter Y = Letter('y', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		LEAP_HAND* dominant = GestureTypeUtils::secondGestureDominant ? h2 : h1;
		LEAP_HAND* support = GestureTypeUtils::secondGestureDominant ? h1 : h2;

		bool palmNormalsAligned = MathUtils::CosSimilarity(dominant->palm.normal, support->palm.normal) > 1.f - MathUtils::PERPENDICULARITY_THRESHOLD;
		bool positioningCorrect = MathUtils::Distance(dominant->digits[1].distal.next_joint, support->digits[0].proximal.prev_joint) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		LEAP_VECTOR domIndexDirection = MathUtils::Direction(dominant->digits[1].proximal.prev_joint, dominant->digits[1].distal.next_joint);
		LEAP_VECTOR supIndexDirection = MathUtils::Direction(support->digits[1].proximal.prev_joint, support->digits[1].distal.next_joint);
		LEAP_VECTOR supThumbDirection = MathUtils::Direction(support->digits[0].proximal.prev_joint, support->digits[0].distal.next_joint);


		float indexThumbSimilarity = MathUtils::CosSimilarity(domIndexDirection, supIndexDirection);
		float indexIndexSimilarity = MathUtils::CosSimilarity(domIndexDirection, supThumbDirection);

		bool centeredAngle = std::abs(indexThumbSimilarity - indexIndexSimilarity) < GestureTypeUtils::ANGLE_SIMILARITY_THRESHOLD;

		return palmNormalsAligned && positioningCorrect && centeredAngle;
	});

	inline static const Letter Z = Letter('z', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		bool palmsNormalsPerpendicular = MathUtils::VectorsPerpendicular(h1->palm.normal, h2->palm.normal);
		bool positioning = MathUtils::Distance(h1->digits[2].distal.next_joint, h2->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD ||
			MathUtils::Distance(h2->digits[2].distal.next_joint, h1->palm.position) < GestureTypeUtils::TOUCH_DISTANCE_THRESHOLD;

		return palmsNormalsPerpendicular && positioning;
	});

	inline static const Letter None = Letter('-', GestureType::NONE, GestureType::NONE, [](LEAP_HAND* h1, LEAP_HAND* h2) {
		return false;
	});

	inline static const int NUM_LETTERS = 26;
	inline static const Letter arr[NUM_LETTERS] = { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
};