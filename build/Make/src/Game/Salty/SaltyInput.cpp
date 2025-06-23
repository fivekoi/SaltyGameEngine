#include "Game/Salty/SaltyInput.h"

// Initialize input arrays
bool Input::KeyDown[NUM_KEYS] = {0};
bool Input::KeyHeld[NUM_KEYS] = {0};
bool Input::KeyUp[NUM_KEYS] = {0};
bool Input::MouseDown[NUM_M] = {0};
bool Input::MouseHeld[NUM_M] = {0};
bool Input::MouseUp[NUM_M] = {0};
int Input::MouseX = 0;
int Input::MouseY = 0;
