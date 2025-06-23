#pragma once

#include "LeapC.h"
#include <cmath>
#include <stdexcept>

class MathUtils {
public:
	static LEAP_VECTOR Normalize(const LEAP_VECTOR& v) {
		float length = Magnitude(v);
		if (length == 0.0) {
			throw std::runtime_error("Cannot normalize zero-length vector.");
		}

		return LEAP_VECTOR{ v.x / length, v.y / length, v.z / length };
	}

	static LEAP_VECTOR Direction(const LEAP_VECTOR& from, const LEAP_VECTOR& to) {
		LEAP_VECTOR dir{ to.x - from.x, to.y - from.y, to.z - from.z };
		return Normalize(dir);
	}

	static float Dot(const LEAP_VECTOR& v1, const LEAP_VECTOR& v2) {
		return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
	}

	static float CosSimilarity(const LEAP_VECTOR& v1, const LEAP_VECTOR& v2) {
		float dot = Dot(v1, v2);
		float magOne = Magnitude(v1);
		float magTwo = Magnitude(v2);
		
		if (magOne == 0.0 || magTwo == 0.0) {
			return 0.0;
		}

		return dot / (magOne * magTwo);
	}

	static float Magnitude(const LEAP_VECTOR& v) {
		return std::sqrt(v.x * v.x + v.y * v.y + v.z * v.z);
	}
};