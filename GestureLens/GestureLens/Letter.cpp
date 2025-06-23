#include "Letter.h"

bool Letter::CheckGesturesCondition(GestureType g1, GestureType g2) const
{
	if (requiredGestureOne == g1 && requiredGestureTwo == g2) {
		//secondGestureDominant = true;
		return true;
	}
	if(requiredGestureOne == g2 && requiredGestureTwo == g1) {
		//secondGestureDominant = false;
		return true;
	}
	return false;
}

bool Letter::CheckCustomCondition(LEAP_HAND h1, LEAP_HAND h2) {
	if (customCondition == nullptr) {
		return true;
	}
	return customCondition(h1, h2);
}

char Letter::GetChar()
{
	return character;
}
