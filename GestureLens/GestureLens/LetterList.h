#pragma once
#include "Letter.h"

//To note: There are some references to "dominant" hands. Since I'm right-handed, these Letter objects were initialized with the 'dominant' being the second gesture.
//In order to be right/ left agnostic, the 'Letter' class will differentiate dominant gesture vs the support by always comparing to 'second' gesture references (requiredGestureTwo, secondGestureDominant etc.).

class LetterList {
public:
	inline static const Letter A = Letter('a', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter B = Letter('b', GestureType::PINCH_CLOSED, GestureType::PINCH_CLOSED, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter C = Letter('c', GestureType::NONE, GestureType::CURVED_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter D = Letter('d', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter E = Letter('e', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter F = Letter('f', GestureType::INDEX_MIDDLE, GestureType::INDEX_MIDDLE, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter G = Letter('g', GestureType::CLOSED, GestureType::CLOSED, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter H = Letter('h', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter I = Letter('i', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter J = Letter('j', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter K = Letter('k', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter L = Letter('l', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter M = Letter('m', GestureType::OPEN, GestureType::INDEX_MIDDLE_RING, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter N = Letter('n', GestureType::OPEN, GestureType::INDEX_MIDDLE, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter O = Letter('o', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter P = Letter('p', GestureType::OPEN_INDEX, GestureType::CURVED_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter Q = Letter('q', GestureType::PINCH_OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter R = Letter('r', GestureType::OPEN, GestureType::CURVED_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter S = Letter('s', GestureType::PINKY, GestureType::PINKY, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter T = Letter('t', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter U = Letter('u', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter V = Letter('v', GestureType::OPEN, GestureType::INDEX_MIDDLE, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter W = Letter('w', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter X = Letter('x', GestureType::OPEN_INDEX, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter Y = Letter('y', GestureType::OPEN, GestureType::OPEN_INDEX, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const Letter Z = Letter('z', GestureType::OPEN, GestureType::OPEN, [](LEAP_HAND h1, LEAP_HAND h2) {
		return false;
	});

	inline static const int NUM_LETTERS = 26;
	inline static const Letter arr[NUM_LETTERS] = { A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z };
};