#include "LetterPoseSampleEngine.h"

int LetterPoseSampleEngine::sampleCount = 0;
DuoHandPose LetterPoseSampleEngine::avgPose;

void LetterPoseSampleEngine::InitializeSampleEngine() {
	sampleCount = 0;
}


void LetterPoseSampleEngine::WriteNewSampleToRADataset(LEAP_HAND* left, LEAP_HAND* right) {
	LEAP_VECTOR l_wrist = left->arm.prev_joint;
	LEAP_VECTOR r_wrist = right->arm.prev_joint;

	// Each finger
	for (int f = 0; f < 5; f++) {
		FingerPose& l_fingerPose = avgPose.left.fingers[f];
		FingerPose& r_fingerPose = avgPose.right.fingers[f];

		for (int b = 0; b < 4; ++b) {
			const LEAP_BONE& l_bone = left->digits[f].bones[b];
			const LEAP_BONE& r_bone = right->digits[f].bones[b];

			BoneSample boneSample;
			boneSample.start = Subtract(l_bone.prev_joint, l_wrist);
			boneSample.end = Subtract(r_bone.next_joint, r_wrist);

			//fingerPose.bones[b] = boneSample;
		}
	}
}