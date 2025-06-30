#pragma once
#include "LeapC.h"
#include <deque>
#include <iostream>

class HistoryManager {
public:
	inline static const size_t maxTrackedFrames = 100;

	inline static std::deque<LEAP_HAND> leftHand = std::deque<LEAP_HAND>{};
	inline static std::deque<LEAP_HAND> rightHand = std::deque<LEAP_HAND>{};
	
	inline static LEAP_HAND left = LEAP_HAND{};
	inline static LEAP_HAND right = LEAP_HAND{};

	static inline void AddFrameDataToHistory(const LEAP_TRACKING_EVENT* frame) {
		left = LEAP_HAND{};
		right = LEAP_HAND{};

		if (frame->nHands > 0) {
			if (frame->pHands[0].type == eLeapHandType_Left) {
				left = frame->pHands[0];
				if (frame->nHands == 2) {
					right = frame->pHands[1];
				}
			}
			else {
				right = frame->pHands[0];
				if (frame->nHands == 2) {
					left = frame->pHands[1];
				}
			}
		}

		leftHand.push_back(left);
		rightHand.push_back(right);

		if (leftHand.size() > maxTrackedFrames) {
			leftHand.pop_front();
			rightHand.pop_front();
		}
	}
};