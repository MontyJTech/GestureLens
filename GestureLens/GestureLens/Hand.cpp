#include "Hand.h"

Hand::Hand(LEAP_HAND l_hand) {
	//l_hand -> digits (fingers)
	//
}

/*
	* The finger bone wholly inside the hand.
	* For thumbs, this bone is set to have zero length and width, an identity basis matrix,
	* and its joint positions are equal.
	* Note that this is anatomically incorrect; in anatomical terms, the intermediate phalange
	* is absent in a real thumb, rather than the metacarpal bone. In the Leap Motion model,
	* however, we use a "zero" metacarpal bone instead for ease of programming.
	* @since 3.0.0
	LEAP_BONE metacarpal;

	The phalange extending from the knuckle. @since 3.0.0 
	LEAP_BONE proximal;

	The bone between the proximal phalange and the distal phalange. @since 3.0.0 
	LEAP_BONE intermediate;

	The distal phalange terminating at the finger tip. @since 3.0.0 
	LEAP_BONE distal;
*/

/*
	typedef struct _LEAP_BONE {
	The base of the bone, closer to the heart. The bones origin. @since 3.0.0 
	LEAP_VECTOR prev_joint;

	The end of the bone, further from the heart. @since 3.0.0 
	LEAP_VECTOR next_joint;

	The average width of the flesh around the bone in millimeters. @since 3.0.0 
	float width;

	Rotation in world space from the forward direction.
	 * Convert the quaternion to a matrix to derive the basis vectors.
	 * @since 3.1.2
 
	LEAP_QUATERNION rotation;
	} LEAP_BONE;
*/