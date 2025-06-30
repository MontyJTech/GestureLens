# GestureLens: Leap Motion BSL Alphabet Recognition (C++17)

This project is a real-time British Sign Language (BSL) alphabet recognizer built with C++17 and the Leap Motion Controller (v1, Orion SDK). It detects static hand gestures representing letters and outputs them live to the console.

The system is fully hand-agnostic — all gestures work with either hand in any orientation.

---

## Demos

**Full Alphabet Recognition**  
A demonstration of the full alphabet using the phrase:  
*"The quick brown fox jumps over the lazy dog"*

![Full Alphabet Demo](./Media/alphabet.gif)

**Hand Agnostic**  
Shows both hands performing vowel gestures (`aeiouaeiou`), verifying recognition consistency.

![Vowel Demo](./Media/vowels.gif)

---

## Controls

- `Spacebar` — Add a space to the output  
- `c` — Clear the output  
- `q` — Quit the application

---

## Features

- Real-time gesture recognition from Leap Motion data
- Static letter matching via a handcrafted classification loop
- Orientation-independent and left/right hand support
- Fully self-contained — no game engine or external libraries

---

## Technologies

- **C++17**
- **Leap Motion Controller v1**
- **Orion SDK**
- **No engine or framework dependencies**

---

## Known Issues

- Some letters occasionally produce false positives:
  - `'R'` may be misclassified as `'J'`
  - `'K'` may be misclassified as `'X'`
- No messaging is shown if:
  - The Leap Motion controller is disconnected
  - Hand tracking is lost

---

## Limitations & Future Improvements

The current implementation uses a simple linear matcher that compares input gestures to a list of hardcoded poses. This works for prototyping, but it doesn't scale well or handle gesture ambiguity.

### Potential improvements (not implemented):

- **Directed Graph Matcher**  
  More efficient and lenient, allowing flexible gesture transitions and better noise tolerance.

- **Finite State Machine (FSM)**  
  Time-sensitive modeling of gestures, enabling more complex gesture sequences and improved detection stability.

- **Neural Network**  
  A lightweight classifier could generalize better across different users, hand sizes, and gesture variation, simplifying further development and improving scalability.

