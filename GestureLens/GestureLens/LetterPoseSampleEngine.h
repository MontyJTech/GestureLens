#pragma once
#include <string>
#include <LeapC.h>

#include "PoseStructs.h"

static class LetterPoseSampleEngine {
public:
	static void InitializeSampleEngine();
	static void WriteNewSampleToRADataset(LEAP_HAND* left, LEAP_HAND* right);
	static void SaveSampleSetToFile();

	static LEAP_VECTOR Subtract(const LEAP_VECTOR& a, const LEAP_VECTOR& b) {
		return { a.x - b.x, a.y - b.y, a.z - b.z };
	}

	static LEAP_VECTOR GetRollingAverage(const LEAP_VECTOR& curAvg, const LEAP_VECTOR& vectorToAdd, const int numSamples) {
		return { 0,0,0 };
	}

private:
	static int sampleCount;
	static DuoHandPose avgPose;
};