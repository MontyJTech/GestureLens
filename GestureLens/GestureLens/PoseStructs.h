#pragma once
#include <LeapC.h>
#include <vector>

struct BoneSample {
    LEAP_VECTOR start;
    LEAP_VECTOR end;
};

struct FingerPose {
    BoneSample* bones = new BoneSample[4];
};

struct HandPoseFrame {
    FingerPose* fingers = new FingerPose[5];
};

struct DuoHandPose {
    HandPoseFrame left;
    HandPoseFrame right;
};