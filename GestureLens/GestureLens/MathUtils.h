#pragma once

#include "LeapC.h"
#include <cmath>
#include <stdexcept>

class MathUtils {
public:
	inline static const float PERPENDICULARITY_THRESHOLD = 0.7f;
	static inline const LEAP_VECTOR UP{0, -1, 0}; // Assumes head mounted

	static LEAP_VECTOR Normalize(const LEAP_VECTOR& v) {
		float length = Magnitude(v);
		if (length == 0.0) {
			throw std::runtime_error("Cannot normalize zero-length vector.");
		}

		return LEAP_VECTOR{ v.x / length, v.y / length, v.z / length };
	}

	static LEAP_VECTOR Direction(const LEAP_VECTOR& from, const LEAP_VECTOR& to) {
		return Normalize(Difference(from, to));
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

	static float Distance(LEAP_VECTOR v1, LEAP_VECTOR v2) {
		return MathUtils::Magnitude(Difference(v1, v2));
	}

	static LEAP_VECTOR Difference(LEAP_VECTOR v1, LEAP_VECTOR v2) {
		return LEAP_VECTOR{ v2.x - v1.x, v2.y - v1.y, v2.z - v1.z };
	}

	static LEAP_VECTOR Midpoint(LEAP_VECTOR v1, LEAP_VECTOR v2) {
		LEAP_VECTOR v1v2 = Difference(v1, v2);
		LEAP_VECTOR halfV1V2 = { v1v2.x / 2.f, v1v2.y / 2.f, v1v2.z / 2.f };

		return {v1.x + halfV1V2.x, v1.y + halfV1V2.y, v1.z + halfV1V2.z};
	}

	static bool VectorsPerpendicular(LEAP_VECTOR v1, LEAP_VECTOR v2) {
		float palmNormalSimilarity = MathUtils::CosSimilarity(v1, v2);

		return 0 - PERPENDICULARITY_THRESHOLD < palmNormalSimilarity &&
			palmNormalSimilarity < 0 + PERPENDICULARITY_THRESHOLD;
	}
};