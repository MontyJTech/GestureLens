#include "Letter.h"

bool Letter::CheckGesturesCondition(GestureType g1, GestureType g2) const
{
	if (requiredGestureOne == g1 && requiredGestureTwo == g2) {
		GestureTypeUtils::secondGestureDominant = true;
		return true;
	}
	if(requiredGestureOne == g2 && requiredGestureTwo == g1) {
		GestureTypeUtils::secondGestureDominant = false;
		return true;
	}
	return false;
}

bool Letter::CheckCustomCondition(LEAP_HAND* h1, LEAP_HAND* h2) const 
{
	return (customCondition != nullptr) ? customCondition(h1, h2) : true;
}

char Letter::GetChar() const
{
	return character;
}
