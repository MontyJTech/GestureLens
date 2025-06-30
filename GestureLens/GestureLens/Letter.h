#pragma once
#include "GestureType.h"
#include "GestureUtils.h"

#include <functional>

class Letter {
public:
	Letter(char character, GestureType requiredGestureOne, GestureType requiredGestureTwo, std::function<bool(LEAP_HAND*, LEAP_HAND*)> customCondition) {
		this->character = character;
		this->requiredGestureOne = requiredGestureOne;
		this->requiredGestureTwo = requiredGestureTwo;

		this->customCondition = customCondition;
	}

	bool CheckGesturesCondition(GestureType g1, GestureType g2) const;
	bool CheckCustomCondition(LEAP_HAND* h1, LEAP_HAND* h2) const;

	char GetChar() const;

private:
	char character;

	GestureType requiredGestureOne;
	GestureType requiredGestureTwo;



	std::function<bool(LEAP_HAND*, LEAP_HAND*)> customCondition;
};