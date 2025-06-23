#include <iostream>
#include "LeapC.h"
#include <thread>
#include <chrono>
#include <conio.h>
#include <vector>

#include "GestureType.h"
#include "GestureUtils.h"
#include "LetterList.h"

bool InitializeLeapDevice(LEAP_CONNECTION* connection, LEAP_CONNECTION_MESSAGE* message);
bool UserRequestQuit();
const char* GetLetterFromPose(const LEAP_TRACKING_EVENT* frame);

void print_vector(const char* label, LEAP_VECTOR v) {
	std::cout << label << ": (" << v.x << ", " << v.y << ", " << v.z << ")" << std::endl;
}

int main()
{
	LEAP_CONNECTION connection;
	LEAP_CONNECTION_MESSAGE message;

	if (!InitializeLeapDevice(&connection, &message)) {
		return -1;
	}

	while (true) {
		if (LeapPollConnection(connection, 100, &message) == eLeapRS_Success) {
			if (UserRequestQuit()) {
				std::cout << "Exiting loop.\n";
				break;
			}
			if (message.type == eLeapEventType_Tracking) {
				const LEAP_TRACKING_EVENT* frame = message.tracking_event;
				std::vector<Letter> availableLetters = std::vector<Letter>();

				if (frame->nHands == 0) {
					continue;
				}

				for (int i = 0; i < LetterList::NUM_LETTERS; i++) {
					GestureType gestureOne = GestureTypeUtils::GetGestureForLeapHand(&frame->pHands[0]);
					GestureType gestureTwo;
					if (frame->nHands == 2) {
						gestureTwo = GestureTypeUtils::GetGestureForLeapHand(&frame->pHands[1]);
					}
					else {
						gestureTwo = GestureType::NONE;
					}
					if (LetterList::arr[i].CheckGesturesCondition(gestureOne, gestureTwo)) {
						availableLetters.push_back(LetterList::arr[i]);
					}
				}

				std::cout << "\rAvailable Letters: ";
				for (int i = 0; i < availableLetters.size(); i++) {
					std::cout << availableLetters[i].GetChar();
					if (i < availableLetters.size() - 1) {
						std::cout << ", ";
					}
				}
				std::cout << "                                                           ";
			}
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}

	// Clean up
	LeapCloseConnection(connection);
	LeapDestroyConnection(connection);

	return 0;
}

bool InitializeLeapDevice(LEAP_CONNECTION* connection, LEAP_CONNECTION_MESSAGE* message) {
	eLeapRS result = LeapCreateConnection(nullptr, connection);

	if (result != eLeapRS_Success) {
		std::cerr << "Failed to connect to Leap device." << std::endl;
		return false;
	}

	result = LeapOpenConnection(*connection);
	if (result != eLeapRS_Success) {
		std::cerr << "Failed to connect to Leap device." << std::endl;
		return false;
	}

	std::cout << "Waiting for connection..." << std::endl;

	while (true) {
		if (LeapPollConnection(*connection, 1000, message) == eLeapRS_Success) {
			if (message->type == eLeapEventType_Connection) {
				std::cout << "Connected to Leap Motion!" << std::endl;
				break;
			}
		}
	}

	return result == eLeapRS_Success;
}

bool UserRequestQuit() {
	if (_kbhit()) {
		char c = _getch();  // Read character without waiting for Enter
		if (c == 'q') {
			return true;
		}
	}
	return false;
}

const char* GetLetterFromPose(const LEAP_TRACKING_EVENT* frame) {
	return "-";
}