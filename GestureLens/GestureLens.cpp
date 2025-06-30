#include <iostream>
#include <conio.h>

#include "LeapC.h"
#include "GestureUtils.h"
#include "LetterList.h"

bool InitializeLeapDevice(LEAP_CONNECTION* connection, LEAP_CONNECTION_MESSAGE* message);
bool UserInput();

int main()
{
	LEAP_CONNECTION connection;
	LEAP_CONNECTION_MESSAGE message;

	if (!InitializeLeapDevice(&connection, &message)) {
		return -1;
	}

	const Letter* prevLetter = &LetterList::None;
	const Letter* foundLetter = &LetterList::None;

	const int letterPrintTimeoutFrames = 30;
	int frameCounter = 0;

	while (true) {
		if (LeapPollConnection(connection, 100, &message) == eLeapRS_Success) {
			if (UserInput()) {
				std::cout << "Exiting loop.\n";
				break;
			}
			if (message.type == eLeapEventType_Tracking) {
				foundLetter = &LetterList::None;
				const LEAP_TRACKING_EVENT* frame = message.tracking_event;
				HistoryManager::AddFrameDataToHistory(frame);
				if (frame->nHands == 0) {
					continue;
				}
				if (frameCounter < letterPrintTimeoutFrames) {
					frameCounter++;
					continue;
				}

				GestureType gestureOne = GestureTypeUtils::GetGestureForLeapHand(&frame->pHands[0]);
				GestureType gestureTwo = frame->nHands == 2 ? GestureTypeUtils::GetGestureForLeapHand(&frame->pHands[1]) : GestureType::NONE;

				LEAP_HAND* hOne = &frame->pHands[0];
				LEAP_HAND* hTwo = frame->nHands == 2 ? &frame->pHands[1] : nullptr;

				for (int i = 0; i < LetterList::NUM_LETTERS; i++) {
					if (LetterList::arr[i].CheckGesturesCondition(gestureOne, gestureTwo)) {
						if (LetterList::arr[i].CheckCustomCondition(hOne, hTwo)) {
							foundLetter = &LetterList::arr[i];
							break;
						}
					}
				}

				if(foundLetter->GetChar() != '-') {
					std::cout << foundLetter->GetChar();
					prevLetter = foundLetter;
					frameCounter = 0;
				}
			}
		}
		else {
			//cout a message that basically says "yo there's a problem..."
		}
	}

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

bool UserInput() {
	if (_kbhit()) {
		char c = _getch();  // Read character without waiting for Enter
		if (c == 'c') {
			std::cout << "\x1b[2K"; // Delete current line
			std::cout << "\r";
		}
		if (c == ' ') {
			std::cout << " ";
		}
		if (c == 'q') {
			return true;
		}
	}
	return false;
}